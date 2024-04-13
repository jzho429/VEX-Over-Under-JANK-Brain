#include <Arduino.h>

#include <main.hpp>

#define S1C 30
#define S2C 29
#define S3C 32
#define S4C 31
#define S5C 26
#define S6C 25
#define S7C 28
#define S8C 27

SerialHandler serialHandler(115200);
Bno08x gyro;
V5Data v5Data;
TeensyData teensyData;

void updateGyro() {
    while (true) {
        gyro.updateGyro();
        teensyData.gyroHeading = gyro.getEuler().yaw;
        threads.delay(1);
    }
}

void sendSerial() {
    while (true) {
        serialHandler.send(&teensyData);
        threads.delay(1);
    }
}

void receiveSerial() {
    while (true) {
        serialHandler.receive();
        v5Data = serialHandler.getV5Data();
        threads.delay(5);
    }
}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    while (!Serial) {
        if (CrashReport) {
            Serial.print(CrashReport);
            delay(5000);
        }
    }

    serialHandler.flush();
    setupPneumatics();

    threads.addThread(updateGyro);
    threads.addThread(updatePneumatics);
    threads.addThread(sendSerial);
    threads.addThread(receiveSerial);
}

void loop() {
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
    Serial.println(" ");
    teensyData.x += 1;
    teensyData.y += 2;

    delay(500);
}
