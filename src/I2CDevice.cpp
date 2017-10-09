#include <wiringPiI2C.h>
#include <unistd.h>
#include "I2CDevice.hpp"

I2CDevice::I2CDevice() {
}

void I2CDevice::init(int id) {
    this->id = id;
    this->handle = wiringPiI2CSetup(this->id);
}

int I2CDevice::send(const void *data, size_t size) {
    return (int) write(this->handle, data, size);
}

int I2CDevice::writeReg8(int reg, int data) {
    return wiringPiI2CWriteReg8(this->handle, reg, data);
}

int I2CDevice::readReg8(int reg) {
    return wiringPiI2CReadReg8(this->handle, reg);
}

int I2CDevice::readReg16(int reg) {
    return wiringPiI2CReadReg16(this->handle, reg);
}
