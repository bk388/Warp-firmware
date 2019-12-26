#ifndef _DEV_TCA9548A_H
#define _DEV_TCA9548A_H

#define TCA9548Aaddr 0x70

void initTCA9548A(const uint8_t i2cAddress, WarpI2CDeviceState volatile *  deviceStatePointer);
WarpStatus selectTCA9548Asens(uint8_t tcaSel);
WarpStatus readSensorRegisterTCA9548A(uint8_t deviceRegister, int numberOfBytes);
WarpStatus writeSensorRegisterTCA9548A(uint8_t deviceRegister, uint8_t *payloadBuf, uint8_t numberOfBytes);

#endif /* _DEV_TCA9548A_H */
