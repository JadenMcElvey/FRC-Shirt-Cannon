/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <string>

#include <Drive\MecanumDrive.h>
#include <Joystick.h>
#include <XboxController.h>
#include <SampleRobot.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Talon.h>
#include <PWMSpeedController.h>
#include <Timer.h>
#include <Relay.h>
#include <Compressor.h>
#include <DigitalInput.h>

class Robot : public frc::SampleRobot {
public:
	Robot() {
		robotDrive.SetExpiration(0.1);		
	}

	void RobotInit() {
		compressor.Start();
		f_leftMotor.SetInverted(true);
		b_rightMotor.SetInverted(true);
	}

	void Autonomous() {
	}

	void OperatorControl() override {
		robotDrive.SetSafetyEnabled(true);
		while (IsOperatorControl() && IsEnabled())
		{
			// Drive
			robotDrive.DriveCartesian(controller.GetY(frc::GenericHID::kRightHand), -controller.GetX(frc::GenericHID::kLeftHand), controller.GetX(frc::GenericHID::kRightHand));
			// Fire
            bool n = frc::SmartDashboard::GetBoolean("Safety", false);
			if ((controller.GetTriggerAxis(frc::GenericHID::kLeftHand)>.5) && n)
			{
				relay.Set(frc::Relay::Value::kOn);
			}
            else
            {
                relay.Set(frc::Relay::Value::kOff);
            }
			// The motors will be updated every 5ms
			frc::Wait(0.005);
		}
	}

	/*
	 * Runs during test mode
	 */
	void Test() override {}

private:
	// ROBOT DRIVE SYSTEM
	frc::Talon f_leftMotor{2};
	frc::Talon b_leftMotor{0};
	frc::Talon f_rightMotor{1};
	frc::Talon b_rightMotor{3};

	frc::MecanumDrive robotDrive{f_leftMotor, b_leftMotor, f_rightMotor, b_rightMotor};

	frc::XboxController controller{0};
	
	// Compressor
	frc::Compressor compressor;

    // Relay
    frc::Relay relay{0, frc::Relay::kForwardOnly};
};

START_ROBOT_CLASS(Robot)