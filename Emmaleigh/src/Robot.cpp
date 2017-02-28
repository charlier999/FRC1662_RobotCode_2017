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


	RobotDrive *drive_base;

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

		shifter_button = new CitrusButton(driver, 6);
		gear_button    = new CitrusButton(driver, 5);
		intake_in      = new CitrusButton(driver, 1);
		intake_out     = new CitrusButton(driver, 3);
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

		chooser.AddDefault (GearM, GearM);
		chooser.AddObject  (GearL, GearL);
		chooser.AddObject  (GearR, GearR);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);

//-------------------------------------------------------//
//                  Analog Triggers                      //
//-------------------------------------------------------//

		//trigger->SetLimitsRaw(2048, 3200);
		//trigger->SetLimitsVoltage(0, 3.4);
		top_a->SetLimitsVoltage(0, 3.4);
		top_b->SetLimitsVoltage(0, 3.4);
		bottom_a->SetLimitsVoltage(0, 3.4);

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
	void AutonomousInit() override
{
	autoSelected = chooser.GetSelected();
	// std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
	std::cout << "Auto selected: " << autoSelected << std::endl;

	if
	(
		autoSelected == GearM
	)
	{
		// Auto Init goes here
	}
}

	void AutonomousPeriodic()
{
	//-------------------------------------------//
	//              Left Gear                    //
	//-------------------------------------------//

	if
	(
		autoSelected == GearL
	)
{
		drive_base->SetSafetyEnabled(false);
		shifter->Set
		(
			DoubleSolenoid::Value::kReverse  		//Sets shifters to high/low
		);

	frc::Wait(0.1);									//Wait for .1 sec

		drive_base->TankDrive(0.5, 0.5, false);		//Robot goes 12 O-Clock @ Half Speed

	frc::Wait(2.5); 								//Wait for 2.5 sec

		drive_base->TankDrive(0.0, 1.0, false);		//Robot turns Right w/ Left Drive @ Full Speed

	frc::Wait(0.8);									//Wait for .8 sec

		drive_base->TankDrive(0.75, 0.75, false);	//Robot goes 12 O-Clock @ 3/4 speed

	frc::Wait(0.2);									//Wait for .2 sec

		drive_base->TankDrive(0.0, 0.0, false);		//Robot Stops

	frc::Wait(0.2);									//Wait for .2 sec

		gear->Set
		(
					DoubleSolenoid::Value::kForward		//Robot Opens Gear Holder
		);

	frc::Wait(1.0);									//Wait for 1 sec

		drive_base->TankDrive(-0.5, -0.5, false);	//Robot goes 6 O-Clock @ Half Speed

	frc::Wait(0.5); 								//Wait for .5 sec

		gear->Set
		(
			DoubleSolenoid::Value::kReverse			//Robot Closes Gear Holder
		);

	frc::Wait(0.5);									//Wait for .5 sec

		drive_base->TankDrive(0.0, 0.0, false);		//Robot stops

}
	//-------------------------------------------//
	//             Middle Gear                   //
	//-------------------------------------------//

	if
	(
		autoSelected == GearM
	)
{
		drive_base->SetSafetyEnabled(false);
		shifter->Set
		(
			DoubleSolenoid::Value::kReverse  		//Sets shifters to high/low
		);

	frc::Wait(0.05); 								//Waits for .05 secs

		drive_base->TankDrive(0.5, 0.5, false); 	//Robot goes 12 O-clock @ half speed

	frc::Wait(0.0);									//Wait for ____ secs

		gear->Set
			(
				DoubleSolenoid::Value::kForward		//Opens gear holder
			);
	frc::Wait(0.3);									//Wait for .3 secs

		drive_base->TankDrive(-1.0, -1.0, false);	//Robot goes 6 O-Clock @ full speed

	frc::Wait(0.2);									//Wait for .2 secs

		//More code to be placed
}

	//-------------------------------------------//
	//                Gear Right                 //
	//-------------------------------------------//

	if
	(
		autoSelected == GearR
	)
{
		drive_base->SetSafetyEnabled(false);
		shifter->Set
			(
				DoubleSolenoid::Value::kReverse
			);
	frc::Wait(0.1);									//Wait for .1 sec

		drive_base->TankDrive(0.5, 0.5, false);		//Robot goes 12 O-Clock @ Half Speed

	frc::Wait(2.5); 								//Wait for 2.5 sec

		drive_base->TankDrive(1.0, 0.0, false);		//Robot turns left w/ Right Drive @ Full Speed

	frc::Wait(0.8);									//Wait for .8 sec

		drive_base->TankDrive(0.75, 0.75, false);	//Robot goes 12 O-Clock @ 3/4 speed

	frc::Wait(0.2);									//Wait for .2 sec

		drive_base->TankDrive(0.0, 0.0, false);		//Robot Stops

	frc::Wait(0.2);									//Wait for .2 sec

		gear->Set
			(
				DoubleSolenoid::Value::kForward		//Robot Opens Gear Holder
			);

	frc::Wait(1.0);									//Wait for 1 sec

		drive_base->TankDrive(-0.5, -0.5, false);	//Robot goes 6 O-Clock @ Half Speed

	frc::Wait(0.5); 								//Wait for .5 sec

		gear->Set
		(
			DoubleSolenoid::Value::kReverse			//Robot Closes Gear Holder
		);

	frc::Wait(0.5);									//Wait for .5 sec

		drive_base->TankDrive(0.0, 0.0, false);		//Robot stops

}



}
	void TeleopInit(){}

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
	frc::SendableChooser<std::string> chooser;
	const std::string GearM			  = "GearM";
	const std::string GearL			  = "GearL";
	const std::string GearR			  = "GearR";
	std::string autoSelected;

};
START_ROBOT_CLASS(Robot);
/*
 *  Rumbles the controller.
 * stick->SetRumble(GenericHID::RumbleType::kLeftRumble, 1);
 *
