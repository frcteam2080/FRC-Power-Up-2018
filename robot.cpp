#include "WPILib.h"
#include "Spark.h"

class RobotTest : public SampleRobot {

	DigitalInput limitSwitch;
	DigitalInput limitSwitch1;
	Spark *spark1;
	Spark *spark2;
	Joystick *m_intakestick;


public:

	RobotTest(void):

		limitSwitch(1){
		limitSwitch(2);
		spark1 = new Spark (0);
		spark2 = new Spark (1);
		m_intakestick = new Joystick(0);
	}



	void Autonomous(void) {

	}

	void OperatorControl(void){
		while (IsOperatorControl())
		{

		}
		while (m_intakestick->GetRawButton(7)){

			spark1->Set(7);
			spark2->Set(7);

			if(limitSwitch.Get() == 1 ()){
							spark1->Set(0);
							spark2->Set(0);
						}
						else{
							spark1->Set(7);
							spark2->Set(7);
						}
		}

		if(m_intakestick->GetRawButton(8)){
			spark1->Set(-7);
			spark2->Set(-7);

		}
		else{
			spark1->Set(0);
			spark2->Set(0);
		}

		}
};


START_ROBOT_CLASS(RobotTest);
