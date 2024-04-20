#include "main.h"

float gyroOffset = 0;
float offsetGyro = 0;

void zeroGyro () {
  gyroOffset = teensyData.gyroHeading;
}
