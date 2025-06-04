#include "mpu.h"
#include <math.h>
#include <Arduino.h>

namespace MPU {
    static int MPU_Addr;
    static int AcX, AcY, AcZ;
    constexpr int minVal = -17000;
    constexpr int maxVal = 17000;
    void setup(int addr) {
        Wire.begin(21, 22);
        Wire.beginTransmission(addr);
        Wire.write(0x6B);  // Power management register
        Wire.write(0);     // Wake up MPU6050
        Wire.endTransmission(true);
        MPU_Addr = addr;
    }

    void getAccel(float* ax, float* ay, float* az) {
        Wire.beginTransmission(MPU_Addr);
        Wire.write(0x3B);
        Wire.endTransmission(false);
        Wire.requestFrom(MPU_Addr, 14, true);

        AcX = Wire.read() << 8 | Wire.read();
        AcY = Wire.read() << 8 | Wire.read();
        AcZ = Wire.read() << 8 | Wire.read();

        *ax = (float)AcX/40.96;
        *ay = (float)AcY/40.96;
        *az = (float)AcZ/40.96;
    }

    void getAngle(float* ax, float* ay, float* az) {
        Wire.beginTransmission(MPU_Addr);
        Wire.write(0x3B);
        Wire.endTransmission(false);
        Wire.requestFrom(MPU_Addr, 14, true);

        AcX = Wire.read() << 8 | Wire.read();
        AcY = Wire.read() << 8 | Wire.read();
        AcZ = Wire.read() << 8 | Wire.read();

        int xAng = map(AcX, minVal, maxVal, -90, 90);
        int yAng = map(AcY, minVal, maxVal, -90, 90);
        int zAng = map(AcZ, minVal, maxVal, -90, 90);

        *ax = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
        *ay = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
        *az = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);
    }
}