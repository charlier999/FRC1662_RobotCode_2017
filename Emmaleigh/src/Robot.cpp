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
	bool	shift_enabled;
	int		shooter_setting;
	int		auto_stop;

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
CitrusButton *r2r;

CANTalon *drive_right_a, *drive_right_b, *drive_left_a, *drive_left_b;
CANTalon *intake;
CANTalon *ball_mover;
CANTalon *shooter;
CANTalon *climber;
CANTalon *extra;


RobotDrive *drive_base;

Compressor *compressor;

DoubleSolenoid *gear;
DoubleSolenoid *shifter;

Solenoid *shifterLight;

Robot() {
//-------------------------------------------------------//
//    Assigning Objects to Components and Electronics    //
//-------------------------------------------------------//

driver = new Joystick(0);
op = new Joystick(1);

shift_enabled  = new bool;
shooter_setting= 0;
auto_stop = 0;

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
gear_button    = new CitrusButton(driver, 1);
intake_in      = new CitrusButton(driver, 5);

intake_out     = new CitrusButton(driver, 2);
shooter_button = new CitrusButton(op, 1);
climber_up     = new CitrusButton(op, 5);
r2r			   = new CitrusButton(op, 3);

drive_right_a  = new CANTalon(8);
drive_right_b  = new CANTalon(9);
drive_left_a   = new CANTalon(1);
drive_left_b   = new CANTalon(2);

intake 		   = new CANTalon(4);
shooter 	   = new CANTalon(7);
climber        = new CANTalon(6);
ball_mover     = new CANTalon(3);
extra		   = new CANTalon(5);

drive_base     = new RobotDrive
	(
	drive_right_a,
	drive_right_b,
	drive_left_a,
	drive_left_b
	);

compressor     = new Compressor();

gear           = new DoubleSolenoid(4, 5);
shifter        = new DoubleSolenoid(1, 3);

shifterLight   = new Solenoid(6);

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
//                   Auto Chooser                        //
//-------------------------------------------------------//

chooser.AddDefault (GearM, GearM);
chooser.AddObject  (GearL, GearL);
chooser.AddObject  (GearR, GearR);
chooser.AddObject  (Strait, Strait);
chooser.AddObject  (Check, Check);
frc::SmartDashboard::PutData("Auto Modes", &chooser);

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

drive_right_a->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Brake);
drive_right_b->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Brake);
drive_left_a ->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Brake);
drive_left_b ->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Brake);
}

if
(
	autoSelected == GearR
)
{

drive_right_a->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Brake);
drive_right_b->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Brake);
drive_left_a ->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Brake);
drive_left_b ->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Brake);

}

if
(
	autoSelected == GearL
)
{

drive_right_a->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Brake);
drive_right_b->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Brake);
drive_left_a ->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Brake);
drive_left_b ->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Brake);

}

if
(
	autoSelected == Strait
)
{

drive_right_a->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Brake);
drive_right_b->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Brake);
drive_left_a ->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Brake);
drive_left_b ->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Brake);

}
if
(
	autoSelected == Check
)
{

drive_right_a->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Brake);
drive_right_b->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Brake);
drive_left_a ->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Brake);
drive_left_b ->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Brake);

}
}

	void AutonomousPeriodic()
{
if
(
	auto_stop == 0
)
{

//-------------------------------------------//
//               Systems Check               //
//-------------------------------------------//

if
(
	autoSelected == Check
)
{
	drive_base->SetSafetyEnabled(false);
	shifter->Set
	(
		DoubleSolenoid::Value::kReverse  			//Sets shifters to low
	);
frc::Wait(.1);
	drive_base->TankDrive(1, 1, false);
frc::Wait(.4);
	drive_base->TankDrive(0.0, 0.0, false);
frc::Wait(.1);
	drive_base->TankDrive(-1, -1, false);
	intake->Set(1);
frc::Wait(.4);
	intake->Set(0);
	drive_base->TankDrive(0.0, 0.0, false);
frc::Wait(.1);
	shooter->Set(1);
	ball_mover->Set(1);
	intake->Set(-1);
frc::Wait(.4);
	gear->Set
	(
		DoubleSolenoid::Value::kReverse			//Gear Open
	);
	shooter->Set(0.0);
	ball_mover->Set(0.0	);
frc::Wait(.1);
	intake->Set(0.0);
	gear->Set
	(
		DoubleSolenoid::Value::kForward
	);
	shifter->Set
	(
		DoubleSolenoid::Value::kForward  			//Sets shifters to high/low
	);
frc::Wait(.4);
	drive_base->TankDrive(1, 1, false);
frc::Wait(.1);
	drive_base->TankDrive(0.0, 0.0, false);
frc::Wait(.1);
	drive_base->TankDrive(-1, -1, false);
frc::Wait(.4);
	drive_base->TankDrive(0.0, 0.0, false);
	climber->Set(1);
frc::Wait(1.5);
	climber->Set(0.0);
auto_stop = auto_stop + 1;
}
//-------------------------------------------//
//                 Gear Right                //
//-------------------------------------------//

if
(
	autoSelected == GearR
)
{

	drive_base->SetSafetyEnabled(false);
	shifter->Set
(
	DoubleSolenoid::Value::kReverse  			//Sets shifters to high/low
);

frc::Wait(0.1);									//Wait for .1 sec

	drive_base->TankDrive(1, 1, false);			//Drive @ full speed 		->

frc::Wait(1.1);									//Wait 1.1 sec

	drive_base->TankDrive(0.0, 0.0, false);		//Drive Stops 				[]

frc::Wait(0.2);									//Wait .2 sec

	drive_base->TankDrive(1, 0.0, false);		//Left Drive @ full

frc::Wait(0.42);								//Wait .42 sec

	drive_base->TankDrive(0.0, 0.0, false);		//Drive Stop 				[]

frc::Wait(0.3);									//Wait .3 sec

	drive_base->TankDrive(1, 1, false);			//Drive @ full 				->

frc::Wait(0.3);									//Wait .3 sec

	drive_base->TankDrive(0.0, 0.0, false);		//Drive Stop 				[]

frc::Wait(0.2);									//Wait .2 sec

	gear->Set
	(
		DoubleSolenoid::Value::kReverse			//Gear Open
	);

frc::Wait(1);									//Wait 1 sec

	drive_base->TankDrive(-1, -1, false);		//Drive Reverse @ full 		<-

frc::Wait(.3);									//Wait .3

	drive_base->TankDrive(0.0, 0.0, false);		//Drive Stop 				[]

	gear->Set
	(
		DoubleSolenoid::Value::kForward			//Gear Close
	);

auto_stop = auto_stop +1;						//Stop Auto

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
		DoubleSolenoid::Value::kReverse  		//Sets shifters to high
	);

frc::Wait(0.5); 								//Waits .5 secs

	drive_base->TankDrive(1.0, 1.0, false); 	//Drive @ full 				->

frc::Wait(1.8);									//Wait .3 secs

	drive_base->TankDrive(0.0, 0.0, false);		//Drive Stops 				[]

frc::Wait(0.1);									//Wait .1 secs

	gear->Set
		(
			DoubleSolenoid::Value::kReverse		//Opens gear
		);

frc::Wait(2.0);									//Wait 2 sec

	drive_base->TankDrive(-1.0, -1.0, false);	//Drive @ full 				<-

frc::Wait(0.25);								//Wait for .2 secs

	gear->Set
	(
		DoubleSolenoid::Value::kForward			//Gear Close
	);
	drive_base->TankDrive(0.0, 0.0, false);		//Drive Stop 				[]

frc::Wait(3.0);									//Wait 3 sec

	drive_base->TankDrive(0.0, 0.0, false);		//Nothing					X

frc::Wait(0.40);								//Wait .4 sec

	drive_base->TankDrive(0.0, 0.0, false);		//Nothing					X

	auto_stop = auto_stop + 1;					//Auto Stops

}

	//-------------------------------------------//
	//                Gear Left                  //
	//-------------------------------------------//
if
(
	autoSelected == GearL
)
{

	drive_base->SetSafetyEnabled(false);
	shifter->Set
(
	DoubleSolenoid::Value::kReverse  			//Sets shifters to low
);

frc::Wait(0.1);									//Wait .1 sec

	drive_base->TankDrive(1, 1, false);			//Drive @ full					->

frc::Wait(1.15);								//Wait 1.1 sec

	drive_base->TankDrive(0.0, 0.0, false);		//Drive Stop					[]

frc::Wait(0.2);									//Wait .2 sec

	drive_base->TankDrive(0.0, 1.0, false);		//Left Drive @ full

frc::Wait(0.43);								//Wait .42 sec

	drive_base->TankDrive(0.0, 0.0, false);		//Drive Stop					[]

frc::Wait(0.3);									//Wait .3 sec

	drive_base->TankDrive(50, 50, false);		//Drive @ full					->

frc::Wait(0.3);									//Wait .3 sec

	drive_base->TankDrive(0.0, 0.0, false);		//Drive Stop					[]

frc::Wait(0.2);									//Wait .2 sec

/*	gear->Set
	(
		DoubleSolenoid::Value::kReverse			//Gear Open
	);

frc::Wait(1);									//Wait 1 sec

	drive_base->TankDrive(-50, -50, false);		//Drive Reverse @ Full			<-

frc::Wait(.3);									//Wait .3 sec

	drive_base->TankDrive(0.0, 0.0, false);		//Drive Stop					[]

	gear->Set
	(
		DoubleSolenoid::Value::kForward			//Gear Closes
	);
*/
auto_stop = auto_stop +1;						//Auto Stops
}
if
(
	autoSelected == Strait
)
{

shifter->Set
(
	DoubleSolenoid::Value::kReverse				//Shifter set low
);
frc::Wait(1);									//Wait 1 sec

	drive_base->TankDrive(0.75, 0.75, false);	//Drive 75% speed				->

frc::Wait(1.7);									//Wait 1.7 sec

	drive_base->TankDrive(0.0, 0.0, false);		//Drive Stop					[]

	auto_stop = auto_stop + 1;					//Auto Stop
}
}
}
void TeleopInit()
{
	auto_stop = 0;
	drive_right_a  ->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Coast);
	drive_right_b  ->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Coast);
	drive_left_a   ->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Coast);
	drive_left_b   ->ConfigNeutralMode (CANSpeedController::NeutralMode::kNeutralMode_Coast);

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
	//	shiftCount = shiftCount +1;
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

//Robot To Robot ball moving
if
(
	r2r->ButtonClicked()
)
{
	shooter_setting = shooter_setting + 1;

}

		shifter_button->Update();
		gear_button->Update();
		r2r->Update();
}

private:

frc::LiveWindow* lw = LiveWindow::GetInstance();
frc::SendableChooser<std::string> chooser;
const std::string GearM		= "GearM";
const std::string GearL		= "GearL";
const std::string GearR		= "GearR";
const std::string Strait	= "Strait" ;
const std::string Check     = "Check";
std::string autoSelected;

};
START_ROBOT_CLASS(Robot);
/* stick->SetRumble(GenericHID::RumbleType::kLeftRumble, 1);
 *
DoubleSolenoid exampleDouble = new DoubleSolenoid(1, 2);

exampleDouble->Set(DoubleSolenoid::Value::kOff);
exampleDouble->Set(DoubleSolenoid::Value::kForward);
exampleDouble->Set(DoubleSolenoid::Value::kReverse);

 */
