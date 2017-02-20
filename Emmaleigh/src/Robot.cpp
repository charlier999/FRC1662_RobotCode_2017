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
#include <C:\Users\jmattox\Downloads\Programing Recorses 2017\robot-2014\CitrusButton.h>


class Robot: public frc::IterativeRobot
{
public:

//-------------------------------------------------------//
//                 Other Decorations                     //
//-------------------------------------------------------//
	double  a_timenow;
	double  shoot_timenow;
	bool 	bottom_enabled;
	bool 	top_enabled;

//-------------------------------------------------------//
//              Decoration of Objects                    //
//-------------------------------------------------------//



	Joystick *driver;
	Joystick *op;

	AnalogTrigger *top_a;
	AnalogInput   *top_in;
	AnalogTrigger *top_b;

	AnalogTrigger *bottom_a;
	AnalogInput   *bottom_in;
	AnalogTrigger *bottom_b;

	CitrusButton *shifter_button;
	CitrusButton *gear_button;
	CitrusButton *shooter_button;
	CitrusButton *intake_in;
	CitrusButton *intake_out;
	CitrusButton *climber_up;
	//CitrusButton *climber_down;
	CitrusButton *ball_mover_b;
	CitrusButton *other;
	CitrusButton *hood_up;
	CitrusButton *hood_down;

	CANTalon *drive_right_a, *drive_right_b, *drive_left_a, *drive_left_b;
	CANTalon *intake;
	CANTalon *ball_mover;
	CANTalon *shooter;
	CANTalon *climber;
	CANTalon *hood;
	CANTalon *extra;

	RobotDrive *drive_base;

	frc::Timer *a_timer;
	frc::Timer *shoot_timer;

	Compressor *compressor;

	DoubleSolenoid *gear;
	DoubleSolenoid *shifter;

	//Encoder *shooter_encoder;

	Robot() {
//-------------------------------------------------------//
//    Assigning Objects to Components and Electronics    //
//-------------------------------------------------------//

		driver = new Joystick(0);
		op = new Joystick(1);

		top_a 		   = new AnalogTrigger(0);
		top_in 		   = new AnalogInput(1);
		top_b		   = new AnalogTrigger(top_in);

		bottom_a	   = new AnalogTrigger(2);
		bottom_in  	   = new AnalogInput(3);
		bottom_b	   = new AnalogTrigger(bottom_in);

		top_enabled    = top_a->GetInWindow();
		top_enabled    = top_b->GetTriggerState();

		bottom_enabled = bottom_a->GetInWindow();
		bottom_enabled = bottom_b->GetTriggerState();

		shifter_button = new CitrusButton(driver, 1);
		gear_button    = new CitrusButton(driver, 3);
		intake_in      = new CitrusButton(driver, 5);
		intake_out     = new CitrusButton(driver, 6);
		other          = new CitrusButton(driver, 7);


		shooter_button = new CitrusButton(op, 1);
		hood_down      = new CitrusButton(op, 2);
		ball_mover_b   = new CitrusButton(op, 3);
		hood_up        = new CitrusButton(op, 4);
		climber_up     = new CitrusButton(op, 5);
		//climber_down   = new CitrusButton(op, 6);

		drive_right_a = new CANTalon(8);
		drive_right_b = new CANTalon(9);
		drive_left_a  = new CANTalon(1);
		drive_left_b  = new CANTalon(2);

		intake 		  = new CANTalon(4);
		shooter 	  = new CANTalon(7);
		climber       = new CANTalon(6);
		ball_mover    = new CANTalon(3);
		hood          = new CANTalon(5);

		extra         = new CANTalon(9);

		drive_base    = new RobotDrive
			(
			drive_right_a,
			drive_right_b,
			drive_left_a,
			drive_left_b
			);

		compressor    = new Compressor();

		gear          = new DoubleSolenoid(4, 5);
		shifter       = new DoubleSolenoid(1, 3);

		a_timer       = new frc::Timer;
		shoot_timer   = new frc::Timer;
		a_timenow     = a_timer->Get();
		shoot_timenow = shoot_timer->Get();

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
//		hood->SetFeedbackDevice
//		(
//		   CANTalon::QuadEncoder
//		 );
//		hood->ConfigEncoderCodesPerRev(1024);

//-------------------------------------------------------//
//                   Auto Chooser                        //
//-------------------------------------------------------//
			// W.I.P.

//-------------------------------------------------------//
//                  Analog Triggers                       //
//-------------------------------------------------------//
		if
		(
			top_enabled == true
		)
		{
			printf ("Top button enabled");
		}else{
			printf ("Top button not enabled");
		}

		if
		(
			top_enabled == true
		)
		{
			printf ("Bottom button Enabled");
		}else{
			printf ("Bottom button not Enabled");
		}


	}
	void AutonomousInit() override {}

	void AutonomousPeriodic()
{
		drive_base->SetSafetyEnabled(false);
		shifter->Set
		(
			DoubleSolenoid::Value::kReverse
		);
	frc::Wait(0.1);

		drive_base->TankDrive(0.5, 0.5, false);

	frc::Wait(2.5); //3.4 second delay until next command

		drive_base->TankDrive(1.0, 0.0, false);

	frc::Wait(0.8);

		drive_base->TankDrive(0.75, 0.75, false);

	frc::Wait(0.2);

		drive_base->TankDrive(0.0, 0.0, false);

	frc::Wait(0.2);

		gear->Set
			(
				DoubleSolenoid::Value::kForward
			);

	frc::Wait(1.0); //0.5 second delay until next command

		drive_base->TankDrive(-0.5, -0.5, false);

	frc::Wait(0.5); //2.0 second delay until next command

		gear->Set
		(
			DoubleSolenoid::Value::kReverse
		);

	frc::Wait(0.5);	//3.0 second delay until next command

		drive_base->TankDrive(0.0, 0.0, false);

	frc::Wait(1.0); //1.0 second delay until next command

		frc::Wait(5.0);//end of auto

//-------------------------------------------//
//             Auto 2                        //
//-------------------------------------------//
}
	void TeleopInit()
	{
		shoot_timer->Reset();
		shoot_timer->Start();
	}

	void TeleopPeriodic()
	{
//-------------------------------------------------------//
//                 Drive Remote                          //
//-------------------------------------------------------//

		// drive train; (left joystick; y axis; left drive) (right joystick: y axis; right drive)
		drive_base->TankDrive
		(
				-driver->GetRawAxis(5),
				-driver->GetRawAxis(1)
		);


		//Intake in; right trigger
		if
		(
			intake_in->ButtonPressed()
		)
		{
			intake->Set(-1.0);
		}else{
			if
			(
					intake_out->ButtonPressed()
			)
			{
			intake->Set(1.0);
			}else{
				intake->Set(0.0);
			}


		//shifters
		if
			(
					shifter_button->ButtonClicked()
			)
			{
					shifter->Set
					(
						shifter->Get() ==
						DoubleSolenoid::Value::kReverse ?
						DoubleSolenoid::Value::kForward :
						DoubleSolenoid::Value::kReverse
					);
				}

		//Gear open close; "B" button
		if (
				gear_button->ButtonClicked()
			)
		{
			gear->Set
			(
				gear->Get() ==
					DoubleSolenoid::Value::kReverse ?
					DoubleSolenoid::Value::kForward :
					DoubleSolenoid::Value::kReverse
			);
			 }
//-------------------------------------------------------//
//                 Operator Remote                       //
//-------------------------------------------------------//
		//shooter; left bumper
		if
		(
			shooter_button->ButtonPressed()
		)
		{
			shoot_timer->Reset();
			shooter->Set(-1.0);
			ball_mover->Set(1.0);
		}else{
			shooter->Set(0.0);
			ball_mover->Set(0.0);
		     }


		//climber up; right bumper; o
			if
			(
				climber_up->ButtonPressed()
			)
			{
				climber->Set(1.0);
			 }else{
				climber->Set(0.0);
			 }

			//climber down;
			//if
		//	(
		//		climber_down->ButtonPressed()
		//	)
		//	{
		//		climber->Set(-1.0);
		//	}

			//hood forwards;
			if
			(
				hood_up->ButtonPressed()
			)
			{
				hood->Set(1.0);
			}else{
				hood->Set(0.0);
			}

			//hood backwards;
			if
			(
				hood_down->ButtonPressed()
			)
			{
				hood->Set(1.0);
			}else{
				hood->Set(0.0);
			}
	}
		shifter_button->Update();
		gear_button->Update();
}

private:

	frc::LiveWindow* lw = LiveWindow::GetInstance();

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
	if
		(
			driver->GetRawButton(2)
		)
		{
			if (
					s_timenow > 1.0
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
				 GenericHID::RumbleType::kRightRumble, 0
				 );
			}else{

			}
		 }

		 //shifters; "A" button
		if
		(
			driver->GetRawButton(2)
		)
		{
			if (
					s_count % 2 == 0
				)
			{
				s_count = s_count + 1;
				shifter->Set
				(
					DoubleSolenoid::Value::kReverse
				 );
			}else{
				shifter->Set
				(
					DoubleSolenoid::Value::kForward
				);
				s_count = s_count + 1;
			}
		 }


		 //Agitator;
		if
		(
			agitator_button->ButtonPressed()
		)
		{
			aggitater->Set(1.0);
		}else{
			aggitater->Set(0.0);
		}
 */
