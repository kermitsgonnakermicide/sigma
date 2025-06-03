#pragma once
#include <Wire.h>
#include <Arduino.h>
namespace MPU {
    void setup(int addr);
    void getAccel(float* ax, float* ay, float* az);
    void getAngle(float* ax, float* ay, float* az);
}