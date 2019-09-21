/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/Timer.h>
#include <frc/smartdashboard/SmartDashboard.h>

Robot::Robot() 
{
  // Note SmartDashboard is not initialized here, wait until RobotInit() to make
  // SmartDashboard calls
  m_robotDrive.SetExpiration(0.1);
}

void Robot::RobotInit() 
{
  m_leftMotor.SetInverted(true);
  m_rightMotor.SetInverted(false);

  m_pickUp.SetInverted(false);

  m_shooter.SetInverted(true);
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::Autonomous() 
{
  
}

/**
 * Runs the motors with arcade steering.
 */
void Robot::OperatorControl() 
{
  m_robotDrive.SetSafetyEnabled(true);
  while (IsOperatorControl() && IsEnabled()) 
  {
    //double gryoAngle = m_gyro.GetAngle();

    //SmartDashboard::PutNumber("Gyro Angle", gryoAngle);

    double leftY = m_xbox.GetY(GenericHID::kLeftHand);
    double leftX = m_xbox.GetX(GenericHID::kLeftHand);

    // Drive with arcade style (use right stick)
    m_robotDrive.ArcadeDrive(-leftX, leftY);

    //PickUp
    bool leftBumper = m_xbox.GetBumper(GenericHID::kLeftHand);
    bool rightBumper = m_xbox.GetBumper(GenericHID::kRightHand);

    if (((leftBumper == true) && (rightBumper == true)) || ((leftBumper == false) && (rightBumper == false)))
    {
      m_pickUp.Set(0);
    }
    else
    {
      if (leftBumper == true)
      {
        m_pickUp.Set(1);
      }
      if (rightBumper == true)
      {
        m_pickUp.Set(-1);
      }
    }

    //Turret
    double rightX = m_xbox.GetX(GenericHID::kRightHand);

    m_turret.Set(rightX);
    
    //Shooter
    double leftTrigger = m_xbox.GetTriggerAxis(GenericHID::kLeftHand);

    m_shooter.Set(leftTrigger);

    // The motors will be updated every 5ms
    frc::Wait(0.005);
  }
}

/**
 * Runs during test mode
 */
void Robot::Test() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
