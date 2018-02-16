#include "WPILib.h"
#include "Spark.h"
#include "CANTalon.h"
#include <IterativeRobot.h>
#include <thread>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>

class RobotTest : public SampleRobot {

	Spark *spark1;
	Spark *spark2;
	CANTalon arm1;
	CANTalon arm2;
	CANTalon lf; /*left front */
	CANTalon lr;/*left rear */
	CANTalon rf; /*right front */
	CANTalon rr; /*right rear */



public:

	Joystick *m_intakestick;
 	Joystick *m_driveStick;
	RobotDrive *m_robotDrive;

	RobotTest(void): arm1(2), arm2(3), lf(6), lr(8), rf(10), rr(12)
	{
		m_robotDrive = new RobotDrive(lf, lr, rf, rr);
		m_robotDrive->SetExpiration(0.1);
	 	m_robotDrive->SetSafetyEnabled(false);
		spark1 = new Spark (0);
		spark2 = new Spark (1);
		arm1.Set(0);
	 	arm2.Set(0);
		m_intakestick = new Joystick(1);
		m_driveStick = new Joystick(0);
	}

	void AutonomousInit()
  {
  
	}

	void TeleopInit()
	{

	}

	void OperatorControl(void)
  {

		while (IsOperatorControl())
		{
			m_robotDrive->MecanumDrive_Cartesian(	(0.85*-m_driveStick->GetY()),
			 					(0.85*-m_driveStick->GetZWQ()),
			 					(0.85*-m_driveStick->GetX()));
			/* my right side motors need to drive negative to move robot forward */
			 m_robotDrive->SetInvertedMotor(RobotDrive::kFrontRightMotor,true);
			 m_robotDrive->SetInvertedMotor(RobotDrive::kFrontLeftMotor,false);
			 m_robotDrive->SetInvertedMotor(RobotDrive::kRearRightMotor,true);
			 m_robotDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor,false);

			if(m_intakestick->GetRawButton(1))
      {
				spark1->Set(8);
				spark2->Set(8);
			}
			else if(m_intakestick->GetRawButton(2))
      {
				spark1->Set(-10);
				spark2->Set(-10);
			}
			else{
				spark1->Set(0);
				spark2->Set(0);
			}

			//down
			if(m_intakestick->GetRawButton(5))
      {
			 		arm1.Set(0.50);
			 		arm2.Set(0.50);
			 }
			//up
			else if(m_intakestick->GetRawButton(6))
      {
			 		arm1.Set(-10);
			 		arm2.Set(-10);
			 	}
			else
      {
			arm1.Set(0);
			arm2.Set(0);
			}
		
      }
		}
};

START_ROBOT_CLASS(RobotTest);
