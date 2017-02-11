#include <iostream>
#include <memory>
#include <string>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "WPILib.h"
#include "CANTalon.h"
#include "timer.h"


class Robot: public frc::IterativeRobot {
public:

//-------------------------------------------------------//
//    Other Decerations                                  //
//-------------------------------------------------------//
	bool shifter_varable = false;
	bool gear_enabled = false;
//-------------------------------------------------------//
//   Deceration of Objects                               //
//-------------------------------------------------------//

	//WIP
	//Timer::Timer();


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

		drive_right_a = new CANTalon(1);
		drive_right_b = new CANTalon(2);
		drive_left_a = new CANTalon(8);
		drive_left_b = new CANTalon(9);

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

		gear = new DoubleSolenoid(4, 5);
		shifter = new DoubleSolenoid(1, 3);
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
	void AutonomousInit() override {}

	void AutonomousPeriodic()
	{
		drive_right_a->Set(1.0);
	}

	void TeleopInit() {}

	void TeleopPeriodic()
	{

		// drive train; (left joystick; y axis; left drive) (right joystick: y axis; right drive)
		drive_base->TankDrive(
				driver->GetRawAxis(1),
				driver->GetRawAxis(5)
							 );
//-------------------------------------------------------//
//                 Drive Remote                          //
//-------------------------------------------------------//

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
					!shifter_varable
				)
			{
				shifter_varable = true;
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
				shifter_varable = false;
			     }
		 }

		//Gear open close; "B" button
		if (
				driver->GetRawButton(1)
			)
		{

			if (
					!gear_enabled
				)
			{
				gear_enabled = true;
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
				gear_enabled = false;
			 	   }
		 }

//-------------------------------------------------------//
//  		       Operator Remote                       //
//-------------------------------------------------------//
		//climber up; right bumper; o
		if (
			op->GetRawAxis(1)
			)
		{
			climber->Set(1.0);
		 }
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
