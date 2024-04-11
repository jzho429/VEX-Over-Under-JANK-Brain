#pragma once
#include "main.hpp"

struct euler_t {
    float yaw;
    float pitch;
    float roll;
};

class Bno08x {
   private:
    euler_t ypr;
    sh2_SensorValue_t sensorValue;
    sh2_SensorId_t reportType = SH2_ARVR_STABILIZED_RV;
    long reportIntervalUs = 5000;
    Adafruit_BNO08x bno08x;

    void setReports(sh2_SensorId_t reportType, long report_interval);
    void quaternionToEuler(float qr, float qi, float qj, float qk, euler_t* ypr,
                           bool degrees = true);
    void quaternionToEulerRV(sh2_RotationVectorWAcc_t* rotational_vector,
                             euler_t* ypr, bool degrees);

   public:
    Bno08x(/* args */);
    bool setupGyro();
    void updateGyro();
    euler_t getEuler();
};
