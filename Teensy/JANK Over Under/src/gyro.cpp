#include "main.hpp"

// constructer
Bno08x::Bno08x() {
    bno08x = Adafruit_BNO08x();
    setupGyro();
}

bool Bno08x::setupGyro() {
    // Try to initialize!
    if (!bno08x.begin_I2C(BNO08x_I2CADDR_DEFAULT, &Wire1)) {
        // if (!bno08x.begin_UART(&Serial1)) {  // Requires a device with > 300
        // byte UART buffer! if (!bno08x.begin_SPI(BNO08X_CS, BNO08X_INT)) {
        Serial.println("Failed to find BNO08x chip");
        return false;
        while (true) {
            delay(10);
        }
    }
    Serial.println("BNO08x Found!");
    setReports(reportType, reportIntervalUs);
    delay(100);  // Let the Gyro settle
    return true;
}
void Bno08x::updateGyro() {
    if (bno08x.wasReset()) {
        Serial.println("Sensor was reset");
        setReports(reportType, reportIntervalUs);
    }
    if (bno08x.getSensorEvent(&sensorValue)) {
        quaternionToEulerRV(&sensorValue.un.arvrStabilizedRV, &ypr, true);
    }
}

void Bno08x::setReports(sh2_SensorId_t reportType, long report_interval) {
    Serial.println("Setting desired reports");
    if (!bno08x.enableReport(reportType, report_interval)) {
        Serial.println("Could not enable stabilized remote vector");
    }
}

void Bno08x::quaternionToEuler(float qr, float qi, float qj, float qk,
                               euler_t* ypr, bool degrees) {
    float sqr = sq(qr);
    float sqi = sq(qi);
    float sqj = sq(qj);
    float sqk = sq(qk);

    ypr->yaw = atan2(2.0 * (qi * qj + qk * qr), (sqi - sqj - sqk + sqr));
    ypr->pitch = asin(-2.0 * (qi * qk - qj * qr) / (sqi + sqj + sqk + sqr));
    ypr->roll = atan2(2.0 * (qj * qk + qi * qr), (-sqi - sqj + sqk + sqr));

    if (degrees) {
        ypr->yaw *= RAD_TO_DEG;
        ypr->pitch *= RAD_TO_DEG;
        ypr->roll *= RAD_TO_DEG;
    }
}

void Bno08x::quaternionToEulerRV(sh2_RotationVectorWAcc_t* rotational_vector,
                                 euler_t* ypr, bool degrees) {
    quaternionToEuler(rotational_vector->real, rotational_vector->i,
                      rotational_vector->j, rotational_vector->k, ypr, degrees);
}

euler_t Bno08x::getEuler() { return ypr; }
