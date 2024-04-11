#pragma once
#include "cobs.hpp"

COBS_DEFINE_STRUCT(TeensyData, {
    int16_t x;
    int16_t y;
    float gyroHeading;
});

COBS_DEFINE_STRUCT(V5Data, {
    bool disabled;
    bool pistons[6];
});

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