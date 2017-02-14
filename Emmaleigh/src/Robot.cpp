#include <iostream>
#include <memory>
#include <string>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "WPILib.h"
#include "CANTalon.h"
#include "Timer.h"


class Robot: public frc::IterativeRobot
{
public:

//-------------------------------------------------------//
//                 Other Decorations                     //
//-------------------------------------------------------//

	double a_timenow = a_timer->Get();
	double s_timenow = s_timer->Get();
	double g_timenow = g_timer->Get();

//-------------------------------------------------------//
//              Decoration of Objects                    //
//-------------------------------------------------------//

	//WIP
	frc::Timer *s_timer;
	frc::Timer *g_timer;
	frc::Timer *a_timer;

	Joystick *driver;
	Joystick *driverV2;
	Joystick *op;

	CANTalon *drive_right_a, *drive_right_b, *drive_left_a, *drive_left_b;
	CANTalon *intake;
	CANTalon *aggitater;
	CANTalon *shooter;
	CANTalon *climber;
	CANTalon *hood;
	CANTalon *extra;

	RobotDrive *drive_base;

	Compressor *compressor;

	DoubleSolenoid *gear;
	DoubleSolenoid *shifter;

	//WIP  \/
	//Encoder *shooter_encoder;

	Robot() {
//-------------------------------------------------------//
//    Assigning Objects to Components and Electronics    //
//-------------------------------------------------------//
		driver = new Joystick(0);
		op = new Joystick(1);
		driverV2 = new Joystick(2);

		drive_right_a = new CANTalon(8);
		drive_right_b = new CANTalon(9);
		drive_left_a = new CANTalon(1);
		drive_left_b = new CANTalon(2);

		intake = new CANTalon(4);
		shooter = new CANTalon(7);
		climber = new CANTalon(6);
		aggitater = new CANTalon(3);
		hood = new CANTalon(9);

		extra = new CANTalon(5);

		drive_base = new RobotDrive
			(
			drive_right_a,
			drive_right_b,
			drive_left_a,
			drive_left_b
			);

		compressor = new Compressor(0);

		gear = new DoubleSolenoid(0, 2);
		shifter = new DoubleSolenoid(1, 3);

		s_timer = new frc::Timer();
		g_timer = new frc::Timer();
		a_timer = new frc::Timer();
	}
	void RobotInit() {
//-------------------------------------------------------//
//                Robot vision Code                      //
//-------------------------------------------------------//

		auto cam = frc::CameraServer::GetInstance();
		cam->StartAutomaticCapture();

//-------------------------------------------------------//
//                Robot Compressor                       //
//-------------------------------------------------------//

		compressor->SetClosedLoopControl(true);

//-------------------------------------------------------//
//               Robot Encoder Code                      //
//-------------------------------------------------------//

	//Quadrature Encoder CPR=1024
		hood->SetFeedbackDevice
		(
		   CANTalon::QuadEncoder
		 );
		hood->ConfigEncoderCodesPerRev(1024);

	}
	void AutonomousInit() override
	{
		a_timer->Reset();
		a_timer->Start();
	}

	void AutonomousPeriodic()
	{
		if
		(
			a_timenow == 0
		)
		{
			drive_base->SetSafetyEnabled(false);
			drive_base->TankDrive(0.5, 0.5, false);
		}

		if
		(
			a_timenow == 3.4	//3.4 second delay until next command
		)
		{

		gear->Set(
				gear->Get() ==
				DoubleSolenoid::Value::kReverse ?
				DoubleSolenoid::Value::kForward :
				DoubleSolenoid::Value::kReverse
				  );
		}

		if
		(
			a_timenow == 4.1 //0.5 second delay until next command
		)
		{

		drive_base->TankDrive(-0.5, -0.5, false);

		}

		if
		(
			a_timenow == 6.1 //2.0 second delay until next command
		)
		{
		gear->Set(
				gear->Get() ==
				DoubleSolenoid::Value::kReverse ?
				DoubleSolenoid::Value::kForward :
				DoubleSolenoid::Value::kReverse
				  );
		}

		if
		(
			a_timenow == 9	//3.0 second delay until next command
		)
		{
		drive_base->TankDrive(0.0, 0.0, false);
		}

		if
		(
			a_timenow == 10 //1.0 second delay until next command
		)
		{
		}

		if
		(
			a_timenow == 15	//end of auto
		)
		{
			a_timer->Stop(); // Stops auto timer
		}
	}
	void TeleopInit()
	{
		//starting shifter's timer
		s_timer->Reset();
		s_timer->Start();

		//starting gear timer
		g_timer->Reset();
		g_timer->Start();
	}

	void TeleopPeriodic()
	{

		// drive train; (left joystick; y axis; left drive) (right joystick: y axis; right drive)
		drive_base->TankDrive(
				-driver->GetRawAxis(1),
				-driver->GetRawAxis(5)
							 );
//-------------------------------------------------------//
//                 Drive Remote                          //
//-------------------------------------------------------//

		//hood forwards; back button
		if (
			driver->GetRawButton(7)
		    )
		{
			hood->Set(1.0);
		}else{
			hood->Set(0.0);
		}

		//hood backwords; start button
		if (
			driver->GetRawButton(8)
		    )
		{
			hood->Set(-1.0);
		}else{
			hood->Set(0.0);
		}

		//shooter; left bumper
		if(
				driver->GetRawButton(5)
		  )
		{
			shooter->Set(0.60);
		}else{
			shooter->Set(0.0);
		     }

		//intake in; right trigger
		if (
			driver->GetRawAxis(2)
		   )
		{
			intake->Set(-1.0);
		}else{
			intake->Set(0.0);
			  }

		//aggitator; "B" button
		if (
			driver->GetRawButton(3)
		    )
		{
			aggitater->Set(1.0);
		}else{
			aggitater->Set(0.0);
		      }
		//shifters; "A" button
		if (
			driver->GetRawButton(2)
			)
		{
			if (
					s_timenow < .2
				)
			{
				s_timer->Reset();
				shifter->Set(
					shifter->Get() ==
					DoubleSolenoid::Value::kReverse ?
					DoubleSolenoid::Value::kForward :
					DoubleSolenoid::Value::kReverse
							 );
				driver->SetRumble
				(
				 GenericHID::RumbleType::kLeftRumble, 1
				 );
			}else{
				s_timer->Reset();
			     }
		 }

		//Gear open close; "B" button
		if (
				driver->GetRawButton(1)
			)
		{

			if (
					g_timenow < .2
				)
			{
				g_timer->Reset();
				gear->Set(
					gear->Get() ==
					DoubleSolenoid::Value::kReverse ?
					DoubleSolenoid::Value::kForward :
					DoubleSolenoid::Value::kReverse
						  );
				driver->SetRumble
				(
						GenericHID::RumbleType::kLeftRumble, 1
				 );
			 }else{
				g_timer->Start();
			 	   }
		 }

	//	climber up; POV UP
	//	if (
	//		driver->GetPOV(2)
	//		)
	//	{
	//		climber->Set(1.0);
	//	 }else{
	//		climber->Set(0.0);
	//	 }

	//	//climber down; POV DOWN
	//	if(
	//		driver->GetPOV(6)
	//	   )
	//	{
	//		climber->Set(-1.0);
	//	}else{
	//		climber->Set(0.0);
	//	      }

//-------------------------------------------------------//
//                 Operator Remote                       //
//-------------------------------------------------------//
		//noting here; yeah!!!!!
	}
private:
};
START_ROBOT_CLASS(Robot);
/*
 *  Rumbles the controller.
 * stick->SetRumble(GenericHID::RumbleType::kLeftRumble, 1);
 *
DoubleSolenoid exampleDouble = new DoubleSolenoid(1, 2);

exampleDouble->Set(DoubleSolenoid::Value::kOff);
exampleDouble->Set(DoubleSolenoid::Value::kForward);
exampleDouble->Set(DoubleSolenoid::Value::kReverse);
 */
