#include "WPILib.h"
#include "Spark.h"
#include "ctre/Phoenix.h"
#include <CameraServer.h>
#include <IterativeRobot.h>
#include <thread>
#include <chrono>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>


class MecanumDefaultCode : public TimedRobot {

	Spark *spark1;
	Spark *spark2;
	WPI_TalonSRX *lf = new WPI_TalonSRX(6);
	WPI_TalonSRX *lr = new WPI_TalonSRX(8);
	WPI_TalonSRX *rf = new WPI_TalonSRX(10);
	WPI_TalonSRX *rr = new WPI_TalonSRX(12);
	WPI_TalonSRX *arm1 = new WPI_TalonSRX(2);
	WPI_TalonSRX *arm2 = new WPI_TalonSRX(3);
	Timer *autoTimer = new Timer();

public:

	Joystick *m_intakestick;
 	Joystick *m_driveStick;
	MecanumDrive *m_robotDrive;
	std::string gameData;
	int retries;


	MecanumDefaultCode (void)
	{
  
		CameraServer::GetInstance()->StartAutomaticCapture();
		lf->Set(ControlMode::PercentOutput, 0);
		lr->Set(ControlMode::PercentOutput, 0);
		rf->Set(ControlMode::PercentOutput, 0);
		rr->Set(ControlMode::PercentOutput, 0);
		arm1->Set(ControlMode::PercentOutput, 0);
		arm2->Set(ControlMode::PercentOutput, 0);
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
		autoTimer->Start();
		retries=200;
    
	}
  
  
	void RobotInit(){
		CameraServer::GetInstance()->StartAutomaticCapture();
	}
  

	void AutonomousInit () {
  
		gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
		bool buttonValue = SmartDashboard::GetBoolean("DB/Button 1", false);
		autoTimer->Reset();
		SmartDashboard::PutString("DB/String 2", gameData);
		SmartDashboard::PutString("DB/String 1", "Going");

		if(buttonValue == false)
		{
			SmartDashboard::PutString("DB/String 0", "Going Straight");
			lf->Set(0.5);
			lr->Set(0.5);
			rf->Set(-0.5);
			rr->Set(-0.5);
		}
		else
		{
			SmartDashboard::PutString("DB/String 0", "Going Switch");
			gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
			while(gameData.length() != 3 && retries > 0)
			{
				Wait(0.005);
				gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
				retries = retries - 1;
			}
			SmartDashboard::PutString("DB/String 2", gameData);

			if(gameData.length() > 2)
			{
				if(gameData[0] == 'L')
				{
					lf->Set(0.5);
					lr->Set(0.5);
					rf->Set(-0.5);
					rr->Set(-0.5);
					Wait(0.5);
					lf->Set(-0.5);
					lr->Set(0.5);
					rf->Set(-0.5);
					rr->Set(0.5);
					Wait(4);
					lf->Set(0);
					lr->Set(0);
					rf->Set(0);
					rr->Set(0);
					Wait(0.1);
					arm1->Set(-10);
					arm2->Set(-10);
					Wait(0.75);
					arm1->Set(0);
					arm2->Set(0);
					Wait(0.1);
					lf->Set(0.5);
					lr->Set(0.5);
					rf->Set(-0.5);
					rr->Set(-0.5);
					Wait(1);
					lf->Set(0);
					lr->Set(0);
					rf->Set(0);
					rr->Set(0);
					Wait(0.1);
					spark1->Set(10);
					spark2->Set(10);
					Wait(2);
					spark1->Set(0);
					spark2->Set(0);
				}
				else if(gameData[0] == 'R')
				{
					lf->Set(0.5);
					lr->Set(0.5);
					rf->Set(-0.5);
					rr->Set(-0.5);
					Wait(0.5);
					lf->Set(0);
					lr->Set(0);
					rf->Set(0);
					rr->Set(0);
					Wait(0.1);
					lf->Set(0.5);
					lr->Set(-0.5);
					rf->Set(0.5);
					rr->Set(-0.5);
					Wait(1.25);
					lf->Set(0);
					lr->Set(0);
					rf->Set(0);
					rr->Set(0);
					Wait(0.1);
					arm1->Set(-10);
					arm2->Set(-10);
					Wait(0.75);
					arm1->Set(0);
					arm2->Set(0);
					Wait(0.1);
					lf->Set(0.5);
					lr->Set(0.5);
					rf->Set(-0.5);
					rr->Set(-0.5);
					Wait(1);
					lf->Set(0);
					lr->Set(0);
					rf->Set(0);
					rr->Set(0);
					Wait(0.1);
					spark1->Set(10);
					spark2->Set(10);
					Wait(2);
					spark1->Set(0);
					spark2->Set(0);
				}
				else
				{
					lf->Set(0.5);
					lr->Set(0.5);
					rf->Set(-0.5);
					rr->Set(-0.5);

				}
			}
			else
				{
					lf->Set(0.5);
					lr->Set(0.5);
					rf->Set(-0.5);
					rr->Set(-0.5);
				}
			}
		}



	void AutonomousPeriodic() {
		if(autoTimer->HasPeriodPassed(3))
		{
			lf->Set(0);
			lr->Set(0);
			rf->Set(0);
			rr->Set(0);
			arm1->Set(0);
			arm2->Set(0);
			spark1->Set(0);
			spark2->Set(0);
		}
	}

	void TeleopInit()
	{

	}


	void TeleopPeriodic(void){
		CameraServer::GetInstance()->StartAutomaticCapture();

		while (IsOperatorControl())
		{
			m_robotDrive->DriveCartesian(	        (0.85*m_driveStick->GetX()),
			 										(0.85*-m_driveStick->GetY()),
			 										(0.85*m_driveStick->GetZ()));
			/* my right side motors need to drive negative to move robot forward */

			if(m_intakestick->GetRawButton(1)){
				spark1->Set(8);
				spark2->Set(8);
			}
			else if(m_intakestick->GetRawButton(2)){
				spark1->Set(-10);
				spark2->Set(-10);
			}
			else{
				spark1->Set(0);
				spark2->Set(0);
			}

			//down
			if(m_intakestick->GetRawButton(5)){
			 		arm1->Set(0.50);
			 		arm2->Set(0.50);
			 }
			//up
			else if(m_intakestick->GetRawButton(6)){
			 		arm1->Set(-10);
			 		arm2->Set(-10);
			}
			else {
				arm1->Set(0);
				arm2->Set(0);
			}
		}
	}

};

START_ROBOT_CLASS(MecanumDefaultCode);
