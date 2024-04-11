#include "main.h"

SerialHandler serialHandler(1, 2, 115200);
TeensyData teensyData;
V5Data v5Data;

double gyroOffset = 0;

void receiveTeensy() {
    while (true) {
        serialHandler.receive();
        teensyData = serialHandler.getTeensyData();
        pros::delay(1);
    }
}

void sendTeensy() {
    while (true) {
        serialHandler.send(&v5Data);
        pros::delay(200);
    }
}

void initialize() {
    pros::lcd::initialize();
    pros::Task receiveTeensyTask(receiveTeensy);
    pros::Task sendTeensyTask(sendTeensy);
}

void disabled() { v5Data.disabled = true; }

void competition_initialize() {}

void autonomous() { v5Data.disabled = false; }

void opcontrol() {
    v5Data.disabled = false;
    while (true) {
        pros::delay(20);
        pros::lcd::print(0, "Gyro Yaw: %f", teensyData.gyroHeading);
        setPneumatics(0, true);
        setPneumatics(1, true);
        setPneumatics(2, true);
        setPneumatics(3, true);
        setPneumatics(4, true);
        setPneumatics(5, true);
        setPneumatics(6, true);
        setPneumatics(7, true);
        pros::delay(1000);
        setPneumatics(0, false);
        setPneumatics(1, false);
        setPneumatics(2, false);
        setPneumatics(3, false);
        setPneumatics(4, false);
        setPneumatics(5, false);
        setPneumatics(6, false);
        setPneumatics(7, false);
        pros::delay(1000);
    }
}
