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
	double a_timenow;
	double g_timenow;
	double s_timenow;
	int s_count;
	int g_count;
	bool g_timepassed;
	bool s_timepassed;

//-------------------------------------------------------//
//              Decoration of Objects                    //
//-------------------------------------------------------//

	CitrusButton *shifter_button;
	CitrusButton *gear_button;
	CitrusButton *shooter_button;
	CitrusButton *intake_in;
	CitrusButton *intake_out;
	CitrusButton *climber_up;
	CitrusButton *climber_down;
	CitrusButton *agitator_button;
	CitrusButton *other;
	CitrusButton *hood_up;
	CitrusButton *hood_down;


	frc::Timer *s_timer;
	frc::Timer *g_timer;
	frc::Timer *a_timer;

	Joystick *driver;
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

		drive_right_a = new CANTalon(8);
		drive_right_b = new CANTalon(9);
		drive_left_a = new CANTalon(1);
		drive_left_b = new CANTalon(2);

		intake = new CANTalon(4);
		shooter = new CANTalon(7);
		climber = new CANTalon(6);
		aggitater = new CANTalon(3);
		hood = new CANTalon(5);

		extra = new CANTalon(9);

		drive_base = new RobotDrive
			(
			drive_right_a,
			drive_right_b,
			drive_left_a,
			drive_left_b
			);

		compressor = new Compressor(0);

		gear = new DoubleSolenoid(1, 3);
		shifter = new DoubleSolenoid(4, 5);

		s_timer = new frc::Timer();
		g_timer = new frc::Timer();
		a_timer = new frc::Timer();

		a_timenow = a_timer->Get();
		s_timenow = s_timer->Get();
		g_timenow = g_timer->Get();

		g_count = 0;
		s_count = 0;

		s_timepassed = s_timer->HasPeriodPassed(5);
		g_timepassed = g_timer->HasPeriodPassed(5);

		shifter_button = new CitrusButton(driver, 1);
		gear_button    = new CitrusButton(driver, 3);
		shooter_button = new CitrusButton(driver, 8);
		intake_in      = new CitrusButton(driver, 5);
		intake_out     = new CitrusButton(driver, 6);
		agitator_button= new CitrusButton(driver, 2);
		other          = new CitrusButton(driver, 7);

		climber_up     = new CitrusButton(op, 5);
		climber_down   = new CitrusButton(op, 6);
		hood_up        = new CitrusButton(op, 4);
		hood_down      = new CitrusButton(op, 2);



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

//-------------------------------------------------------//
//                   Auto Chooser                        //
//-------------------------------------------------------//
			// W.I.P.



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

//-------------------------------------------//
//             Auto 2                        //
//-------------------------------------------//
		if
		(
			a_timenow == 0 //start of auto
		)
		{

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
		drive_base->TankDrive
		(
				-driver->GetRawAxis(5),
				-driver->GetRawAxis(1)
		);
//-------------------------------------------------------//
//                 Drive Remote                          //
//-------------------------------------------------------//


		//shooter; left bumper
		if
		(
			shooter_button->ButtonPressed()
		)
		{
			shooter->Set(1.0);
		}else{
			shooter->Set(0.0);
		     }

		//Intake in; right trigger
		if
		(
			intake_in->ButtonPressed()
		)
		{
			intake->Set(-1.0);
		}else{
			intake->Set(0.0);
		}

		//Intake out; Left Trigger
		if
		(
			intake_out->ButtonPressed()
		)
		{
			intake->Set(-1.0);
		}else{
			intake->Set(0.0);
		}

		//Agitator; "B" button
		if
		(
			agitator_button->ButtonPressed()
		)
		{
			aggitater->Set(1.0);
		}else{
			aggitater->Set(0.0);
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
					s_timer->Reset();
					driver->SetRumble
					(
					 GenericHID::RumbleType::kRightRumble, 99
					 );
				}else{

				}

		//Gear open close; "B" button
		if (
				gear_button->ButtonClicked()
			)
		{
			shifter->Set
			(
				shifter->Get() ==
					DoubleSolenoid::Value::kReverse ?
					DoubleSolenoid::Value::kForward :
					DoubleSolenoid::Value::kReverse
			);
				driver->SetRumble
				(
					GenericHID::RumbleType::kRightRumble, 99
				);


			 }




//-------------------------------------------------------//
//                 Operator Remote                       //
//-------------------------------------------------------//
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

			//climber down; left bumper
			if
			(
				climber_down->ButtonPressed()
			)
			{
				climber->Set(-1.0);
			}else{
				climber->Set(0.0);
			}
			//hood forwards; back button
			if
			(
				op->GetRawButton(3)
			)
			{
				hood->Set(1.0);
			}else{
				hood->Set(0.0);
			}

			//hood backwards; start button
			if
			(
				op->GetRawButton(4)
			)
			{
				hood->Set(1.0);
			}else{
				hood->Set(0.0);
			}

			shifter_button->Update();


	}

	void TestPeriodic()
	{
		lw->Run();

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
 */
