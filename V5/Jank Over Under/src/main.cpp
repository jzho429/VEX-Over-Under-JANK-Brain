#include "main.h"

SerialHandler serialHandler(1, 2, 115200);
TeensyData teensyData;
V5Data v5Data;

char pistonStatus = 0b00000000;

// Receive data from the Teensy
void receiveTeensy()
{
    while (true)
    {
        serialHandler.receive();
        teensyData = serialHandler.getTeensyData();
        offsetGyro = atan2(sin((teensyData.gyroHeading - gyroOffset)*pi/180), cos((teensyData.gyroHeading - gyroOffset)*pi/180)) * 180/pi;
        pros::delay(1);
    }
}

// Send data to Teensy
void sendTeensy()
{
    while (true)
    {
        serialHandler.send(&v5Data);
        pros::delay(5);
    }
}

void initialize()
{
    pros::lcd::initialize();
    pros::Task receiveTeensyTask(receiveTeensy);
    pros::Task sendTeensyTask(sendTeensy);
    pros::Task updatePneumaticsTask(updatePneumatics);
}

void disabled() { v5Data.disabled = true; }

void competition_initialize() {}

void autonomous() { v5Data.disabled = false; }

void opcontrol()
{
    v5Data.disabled = false;
    Controller controller;
    while (true)
    {
        pros::lcd::print(0, "Gyro Yaw: %f", teensyData.gyroHeading);
        pros::lcd::print(1, "Disabled: %d", v5Data.disabled);
        pros::lcd::print(2, "Gyro Yaw Offset: %f", offsetGyro);
        pros::lcd::print(3, "Pistons: %d %d %d %d %d %d %d %d", v5Data.pistons0,
                         v5Data.pistons1, v5Data.pistons2, v5Data.pistons3,
                         v5Data.pistons4, v5Data.pistons5, v5Data.pistons6,
                         v5Data.pistons7);

        if (controller.getDigital(ControllerDigital::A))
        {
            setPneumatics(0, 1);
        }
        else
        {
            setPneumatics(0, 0);
        }

        if (controller.getDigital(ControllerDigital::B))
        {
            zeroGyro();
        }

        pros::delay(20);
    }
}
