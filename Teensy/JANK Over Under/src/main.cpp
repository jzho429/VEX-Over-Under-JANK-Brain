#include <Arduino.h>

#include <main.hpp>

SerialHandler serialHandler(115200);
Bno08x gyro;
V5Data v5Data;
TeensyData teensyData;

const bool debug = false;

// Teensy thread to update gyro
void updateGyro() {
    while (true) {
        gyro.updateGyro();
        teensyData.gyroHeading =
            gyro.getEuler().yaw;  // Change depending on orientation of board
        threads.delay(1);
    }
}

// Teensy thread to send serial data to V5
void sendSerial() {
    while (true) {
        serialHandler.send(&teensyData);
        threads.delay(1);
    }
}

// Teensy thread to receive serial data from V5
void receiveSerial() {
    while (true) {
        serialHandler.receive();
        v5Data = serialHandler.getV5Data();
        threads.delay(5);
    }
}

// Initialize the teensy
void setup() {
    Serial.begin(115200);
    if (debug) {
        // Waits for serial monitor then runs
        while (!Serial) {
            if (CrashReport) {
                Serial.print(CrashReport);
                delay(5000);
            }
        }
    }
    serialHandler.flush();
    setupPneumatics();

    threads.addThread(updateGyro);
    threads.addThread(updatePneumatics);
    threads.addThread(sendSerial);
    threads.addThread(receiveSerial);
}

// Main loop, debug information
void loop() {
    if (debug) {
        Serial.print("Disabled: ");
        Serial.print(v5Data.disabled);
        Serial.print("\tPistons:");
        Serial.print(" ");
        Serial.print(v5Data.pistons0);
        Serial.print(v5Data.pistons1);
        Serial.print(v5Data.pistons2);
        Serial.print(v5Data.pistons3);
        Serial.print(v5Data.pistons4);
        Serial.print(v5Data.pistons5);
        Serial.print(v5Data.pistons6);
        Serial.print(v5Data.pistons7);
        // Serial.print("\tX,Y: ");
        // Serial.printf("%i  %i \r\n", teensyData.x, teensyData.y);
    }
    delay(100);
}