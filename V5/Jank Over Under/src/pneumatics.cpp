#include "main.h"

void updatePneumatics() {
    while (true) {
        v5Data.pistons0 = bool(0b00000001 & pistonStatus);
        v5Data.pistons1 = bool(0b00000010 & pistonStatus);
        v5Data.pistons2 = bool(0b00000100 & pistonStatus);
        v5Data.pistons3 = bool(0b00001000 & pistonStatus);
        v5Data.pistons4 = bool(0b00010000 & pistonStatus);
        v5Data.pistons5 = bool(0b00100000 & pistonStatus);
        v5Data.pistons6 = bool(0b01000000 & pistonStatus);
        v5Data.pistons7 = bool(0b10000000 & pistonStatus);
        pros::delay(20);
    }
}

void setPneumatics(int piston, bool value) {
    pistonStatus = value ? pistonStatus | (0b00000001 << piston)
                         : pistonStatus & ~(0b00000001 << piston);
}