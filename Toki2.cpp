/*
 * Last Updated 
 * April 9, 2018
 * Lauren Williams
 */
#include "WPILib.h"
#include "Spark.h"
#include "ctre/Phoenix.h"
#include <CameraServer.h>
#include <IterativeRobot.h>
#include <thread>
#include <chrono>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <DoubleSolenoid.h>
#include <Solenoid.h>
#include <opencv2/core/types.hpp>
#include <Compressor.h>


class MecanumDefaultCode : public TimedRobot
{
	Spark *spark1; // Intake
	Spark *spark2; // Intake
	WPI_VictorSPX *lf = new WPI_VictorSPX(6); // Left Front Motor
	WPI_VictorSPX *lr = new WPI_VictorSPX(8); // Left Rear Motor
	WPI_VictorSPX *rf = new WPI_VictorSPX(10); //Right Front Motor
	WPI_VictorSPX *rr = new WPI_VictorSPX(1); // Right Rear Motor
	//WPI_VictorSPX *arm1 = new WPI_VictorSPX(2); // Window Motor 1
	//WPI_TalonSRX *arm2 = new WPI_TalonSRX(3); // Window Motor 2
	Compressor *c = new Compressor(0); // Compressor
	Timer *autoTimer = new Timer;


public:

	Joystick *m_intakestick; // Operator Control
 	Joystick *m_driveStick; // Driver Control
	MecanumDrive *m_robotDrive;
	std::string gameData;
	int retries;
	bool hasRun;
	bool pressureSwitch = c->GetPressureSwitchValue();


	MecanumDefaultCode (void)
	{
		lf->Set(ControlMode::PercentOutput, 0);
		lr->Set(ControlMode::PercentOutput, 0);
		rf->Set(ControlMode::PercentOutput, 0);
		rr->Set(ControlMode::PercentOutput, 0);
		//arm1->Set(ControlMode::PercentOutput, 0);
		//arm2->Set(ControlMode::PercentOutput, 0);
		m_robotDrive = new MecanumDrive(*lf, *lr, *rf, *rr);
		m_robotDrive->SetExpiration(0.5);
		m_robotDrive->SetSafetyEnabled(false);
		rf->SetInverted(true);
		rr->SetInverted(true);
		lf->SetInverted(true);
		lr->SetInverted(true);
		spark1 = new Spark (0);
		spark2 = new Spark (1);
		m_intakestick = new Joystick(1);
		m_driveStick = new Joystick(0);
		autoTimer->Start(); // Autonomous Timer
		retries = 200;
		hasRun = false;
	}
	void RobotInit()
	{
		SmartDashboard::PutString("DB/String 0", " "); // Clear String 0
		SmartDashboard::PutString("DB/String 1", " "); // Clear String 1
		SmartDashboard::PutString("DB/String 2", " "); // Clear String 2
		SmartDashboard::PutString("DB/String 3", " "); // Clear String 3
		SmartDashboard::PutString("DB/String 5", " "); // Clear String 5
		SmartDashboard::PutString("DB/String 5", "Good Luck"); // If "Good Luck" appears in String 5 then the dashboard is working if it doesn't restart the dashboard
		CameraServer::GetInstance()->StartAutomaticCapture(); // Turns Camera on
	}

	/*
	 * Autonomous Programs for Mecanum Wheels
	 */

	void forwardAuto()
	{
		lf->Set(0.5);
		lr->Set(0.5);
		rf->Set(-0.5);
		rr->Set(-0.5);
	}

	void armUp()
	{
		//arm1->Set(-10);
		//arm2->Set(-10);
	}
	void armDown()
	{
		//arm1->Set(10);
		//arm1->Set(10);
	}
	void armStop()
	{
		//arm1->Set(0);
		//arm1->Set(0);
	}

	void intakeOut()
	{
		spark1->Set(10);
		spark2->Set(10);
	}
	void intakeStop()
	{
		spark1->Set(0);
		spark2->Set(0);
	}
	void reverseAuto()
	{
		lf->Set(-0.5);
		lr->Set(-0.5);
		rf->Set(0.5);
		rr->Set(0.5);
	}
	void strafeLeft()
	{
		lf->Set(-0.5);
		lr->Set(0.425);
		rf->Set(-0.5);
		rr->Set(0.5);
	}
	void strafeRight()
	{
		lf->Set(0.5);
		lr->Set(-0.5);
		rf->Set(0.5);
		rr->Set(-0.5);
	}
	void stopRobot()
	{
		lf->Set(0);
		lr->Set(0);
		rf->Set(0);
		rr->Set(0);
	}
	void leftAuto() // Left Switch Autonomous
	{
		forwardAuto();
		Wait(0.5);
		strafeLeft();
		Wait(3.3);
		stopRobot();
		Wait(0.1);
		armUp();
		Wait(0.75);
		armStop();
		Wait(0.1);
		forwardAuto();
		Wait(1.85);
		stopRobot();
		Wait(0.1);
		intakeOut();
		Wait(2);
		intakeStop();
		Wait(0.01);
		armUp();
		Wait(0.35);
		armStop();
		Wait(0.01);
		reverseAuto();
		Wait(0.75);
		stopRobot();
		hasRun = true;
		SmartDashboard::PutString("DB/String 3", "Going Left");
	}
	void rightAuto () // Right Switch Autonomous
	{
		forwardAuto();
		Wait(0.5);
		stopRobot();
		Wait(0.1);
		strafeRight();
		Wait(1.97);
		stopRobot();
		Wait(0.1);
		armUp();
		Wait(0.75);
		armStop();
		Wait(0.1);
		forwardAuto();
		Wait(1.85);
		stopRobot();
		Wait(0.1);
		intakeOut();
		Wait(2);
		intakeStop();
		Wait(0.01);
		armUp();
		Wait(0.35);
		armStop();
		Wait(0.01);
		reverseAuto();
		Wait(0.75);
		stopRobot();
		hasRun = true;
		SmartDashboard::PutString("DB/String 3", "Going Right");
	}
	void Auto() // Autonomous Program
	{
		gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
		bool buttonValue = SmartDashboard::GetBoolean("DB/Button 1", false);
		if(buttonValue == false && hasRun == false)
		{
			SmartDashboard::PutString("DB/String 0", "Going Straight");
			forwardAuto();
			Wait(3);
			stopRobot();
			hasRun = true;
		}
		else if (hasRun == false)
		{
			SmartDashboard::PutString("DB/String 0", "Going Switch");
			gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
			while(gameData.length() < 2 && retries > 0)
			{
				Wait(0.005);
				gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
				retries = retries - 1;
			}
			SmartDashboard::PutString("DB/String 2", gameData);

			if(gameData.length() > 2 && hasRun == false)
			{
				if(gameData[0] == 'L')
				{
					leftAuto();
				}
				else if (gameData[0] == 'R')
				{
					rightAuto();
				}
				else
				{
					// Commented Out March 22, 2018
					/*forwardAuto();
					Wait(3);
					stopRobot();*/

				}
			}
			else
				{
					// Commented Out March 22, 2018
					/*forwardAuto();
					Wait(3);
					stopRobot();*/
				}
			}
		else
		{
		}
	}

	void AutonomousInit () {
		SmartDashboard::PutString("DB/String 0", " ");
		SmartDashboard::PutString("DB/String 1", " ");
		SmartDashboard::PutString("DB/String 2", " ");
		hasRun = false;
		autoTimer->Reset();
		Auto();
	}



	void AutonomousPeriodic()
	{
		if(autoTimer->HasPeriodPassed(10) && hasRun == false)
		{
			forwardAuto();
			Wait(3);
			stopRobot();
			armStop();
			intakeStop();
		}
		Auto();
	}

	void TeleopInit()
	{
	}

	void TeleopPeriodic(void){
		CameraServer::GetInstance()->StartAutomaticCapture();
		while (IsOperatorControl())
		{
			m_robotDrive->DriveCartesian(	        (1*m_driveStick->GetX()),
			 										(1*-m_driveStick->GetY()),
			 										(1*m_driveStick->GetZ()));
			frc::DoubleSolenoid exampleDouble {1, 2};
			if(m_intakestick->GetRawButton(3)) // Pneumatics In
			{
				exampleDouble.Set(frc::DoubleSolenoid::Value::kForward);
			}
			else if(m_intakestick->GetRawButton(4)) // Pneumatics Out
			{
				exampleDouble.Set(frc::DoubleSolenoid::Value::kReverse);
			}
			else // Pneumatics Off
			{
				exampleDouble.Set(frc::DoubleSolenoid::Value::kOff);
			}
			if(m_intakestick->GetRawButton(1)) // Intake In
			{
				spark1->Set(8);
				spark2->Set(8);
			}
			else if(m_intakestick->GetRawButton(2)) // Intake Out
			{
				spark1->Set(-10);
				spark2->Set(-10);
			}
			else // Intake Stop
			{
				spark1->Set(0);
				spark2->Set(0);
			}
			if(m_intakestick->GetRawButton(5)) // Down
			{
			 		//arm1->Set(0.35);
			 		//arm2->Set(0.50);
			 }
			else if(m_intakestick->GetRawButton(6)) // Up
			{
			 		//arm1->Set(-0.6);
			 		//arm2->Set(-100);
			}
			else // Off
			{
				//arm1->Set(0);
				//arm2->Set(0);
			}
		}
	}
};
START_ROBOT_CLASS(MecanumDefaultCode);
