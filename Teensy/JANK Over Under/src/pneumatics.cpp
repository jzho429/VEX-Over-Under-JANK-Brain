#include "main.hpp"

// Teensy pins
#define S1C 30
#define S2C 29
#define S3C 32
#define S4C 31
#define S5C 26
#define S6C 25
#define S7C 28
#define S8C 27

// Setup pins to control pneumatics
void setupPneumatics() {
    pinMode(S1C, OUTPUT);
    pinMode(S2C, OUTPUT);
    pinMode(S3C, OUTPUT);
    pinMode(S4C, OUTPUT);
    pinMode(S5C, OUTPUT);
    pinMode(S6C, OUTPUT);
    pinMode(S7C, OUTPUT);
    pinMode(S8C, OUTPUT);
}

// Update the state of the pneumatics
void updatePneumatics() {
    while (true) {
        if (!v5Data.disabled) {
            digitalWrite(S1C, v5Data.pistons[0]);
            digitalWrite(S2C, v5Data.pistons[1]);
            digitalWrite(S3C, v5Data.pistons[2]);
            digitalWrite(S4C, v5Data.pistons[3]);
            digitalWrite(S5C, v5Data.pistons[4]);
            digitalWrite(S6C, v5Data.pistons[5]);
            // digitalWrite(S7C, v5Data.pistons[6]);
            // digitalWrite(S8C, v5Data.pistons[7]);
        }
        threads.delay(5);
    }
}