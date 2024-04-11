#pragma once
#include <Adafruit_BNO08x.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <Encoder.h>
#include <math.h>

#include <iostream>

#include "TeensyThreads.h"
#include "cobs.hpp"
#include "gyro.hpp"
#include "pneumatics.hpp"
#include "serialHandler.hpp"

extern V5Data v5Data;
