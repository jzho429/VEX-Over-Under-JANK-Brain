#pragma once
#include "main.h"

// Ignore the linting errors for the packed attribute
COBS_DEFINE_STRUCT(TeensyData, {
    // int32_t x;
    // int32_t y;
    float gyroHeading;
});

COBS_DEFINE_STRUCT(V5Data, {
    bool disabled;
    unsigned char pistons0 : 1;
    unsigned char pistons1 : 1;
    unsigned char pistons2 : 1;
    unsigned char pistons3 : 1;
    unsigned char pistons4 : 1;
    unsigned char pistons5 : 1;
    unsigned char pistons6 : 1;
    unsigned char pistons7 : 1;
});

extern TeensyData teensyData;
extern V5Data v5Data;

class SerialHandler {
   public:
    SerialHandler(int sendPort, int receivePort, int baudRate);
    void send(V5Data *data);
    void receive();
    pros::Serial *getSendSerial();
    pros::Serial *getReceiveSerial();
    TeensyData getTeensyData();
    int32_t setBaudRate(int baudRate);
    int32_t flush();

   private:
    pros::Serial *serialS = nullptr;
    pros::Serial *serialR = nullptr;
    COBS<TeensyData> cobsReceiver;
    COBS<V5Data> cobsSender;
    TeensyData teensyData = {0};
};
