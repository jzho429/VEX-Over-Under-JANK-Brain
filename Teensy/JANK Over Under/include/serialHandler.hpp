#pragma once
#include "cobs.hpp"

// Data struct Teensy Send to V5
COBS_DEFINE_STRUCT(TeensyData, {
    // int32_t x;
    // int32_t y;
    float gyroHeading;
});

// Data struct Teensy Receive from V5
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

// Serial Handler Class
class SerialHandler {
   public:
    SerialHandler(int baudRate);
    void send(TeensyData *data);
    void receive();
    V5Data getV5Data();
    void flush();

   private:
    COBS<TeensyData> cobsSender;
    COBS<V5Data> cobsReceiver;
    V5Data v5Data;
};