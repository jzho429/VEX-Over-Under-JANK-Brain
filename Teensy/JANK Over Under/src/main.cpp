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
        threads.delay(50);
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
    for (int i = 0; i < 6; i++) {
        Serial.print(v5Data.pistons[i]);
        Serial.print(", ");
    }
    Serial.println(" ");

    // digitalWrite(S1C, HIGH);
    // digitalWrite(S2C, HIGH);
    // digitalWrite(S3C, HIGH);
    // digitalWrite(S4C, HIGH);
    // digitalWrite(S5C, HIGH);
    // digitalWrite(S6C, HIGH);
    // digitalWrite(S7C, HIGH);
    // digitalWrite(S8C, HIGH);
    // delay(500);
    // digitalWrite(S1C, LOW);
    // digitalWrite(S2C, LOW);
    // digitalWrite(S3C, LOW);
    // digitalWrite(S4C, LOW);
    // digitalWrite(S5C, LOW);
    // digitalWrite(S6C, LOW);
    // digitalWrite(S7C, LOW);
    // digitalWrite(S8C, LOW);
    delay(500);
}
