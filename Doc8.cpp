#include "WPILib.h"

#define IO (DriverStation::GetInstance()->GetEnhancedIO())

class Init : public SimpleRobot
{
	//declarations
	Joystick pilot, copilot;
	Jaguar lefty, righty, intake, lift, raiseA;/* , yaw, pitch //(if mobile top)*/;
	
public:
	Init(void):
		pilot(1),
		copilot(2),
		lefty(1),
		righty(2),
		intake(3),
		lift(4),
		raiseA(5)
		{
		}
	
	void Autonomous(void)
	{
		GetWatchdog().Kill();
	}
	void OperatorControl(void)
	{
		GetWatchdog().Kill();
		
		while (IsOperatorControl())
		{
			
			if (copilot.GetTop())//trigger top left - top tower
			{
				raiseA.Set(1);
			}
			else if (copilot.GetTrigger())
			{
				raiseA.Set(-1);
				
			}
			else {raiseA.Set(0);}
			
			intake.Set(copilot.GetTwist());
			lift.Set(copilot.GetY());//lift tower2
			
			
			/*idea bellow:lefty left wheels et all
		if y and twist return pitch and x and z return roll thumb->left & forward 
		increases one jag(by over hence the else) and decreases another to negatives:
		turns
		from left forward to back left, begins to do opposite
		*/
			if (pilot.GetY() - 2 * pilot.GetX() < 1)
			{
				lefty.Set(pilot.GetY() - 2 * pilot.GetX());//left thumb?
			}
			else {lefty.Set(1);}
			if (pilot.GetY() - 2 * pilot.GetX() < 1)
			{
				righty.Set(pilot.GetY() + 2 * pilot.GetX());//twist is w/z
			}
			else {righty.Set(1);}
				
			Wait(0.005);				// wait for a motor update time
		}
	}
};

START_ROBOT_CLASS(Init);

