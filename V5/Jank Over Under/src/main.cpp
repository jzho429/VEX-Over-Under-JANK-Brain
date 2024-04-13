#include "main.h"

SerialHandler serialHandler(1, 2, 115200);
TeensyData teensyData;
V5Data v5Data;

double gyroOffset = 0;
char pistonStatus = 0b00000000;

// Receive data from the Teensy
void receiveTeensy() {
    while (true) {
        serialHandler.receive();
        teensyData = serialHandler.getTeensyData();
        pros::delay(1);
    }
}

// Send data to Teensy
void sendTeensy() {
    while (true) {
        serialHandler.send(&v5Data);
        pros::delay(5);
    }
}

void initialize() {
    pros::lcd::initialize();
    pros::Task receiveTeensyTask(receiveTeensy);
    pros::Task sendTeensyTask(sendTeensy);
    pros::Task updatePneumaticsTask(updatePneumatics);
}

void disabled() { v5Data.disabled = true; }

void competition_initialize() {}

void autonomous() { v5Data.disabled = false; }

void opcontrol() {
    v5Data.disabled = false;
    while (true) {
        pros::lcd::print(0, "Gyro Yaw: %f", teensyData.gyroHeading);
        pros::lcd::print(1, "Disabled: %d", v5Data.disabled);
        // pros::lcd::print(2, "X=%d, Y=%d", teensyData.x, teensyData.y);
        pros::lcd::print(3, "Pistons: %d %d %d %d %d %d %d %d", v5Data.pistons0,
                         v5Data.pistons1, v5Data.pistons2, v5Data.pistons3,
                         v5Data.pistons4, v5Data.pistons5, v5Data.pistons6,
                         v5Data.pistons7);

        // setPneumatics(0, true);
        pros::delay(20);
    }
}
