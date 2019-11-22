#ifndef WAROP_BUILD_ENABLE_DEVIANA219
#define WAROP_BUILD_ENABLE_DEVIANA219
#endif /* WAROP_BUILD_ENABLE_DEVIANA219 */

void initIANA219(const uint8_t i2cAddress, WarpI2CDeviceState volatile *  deviceStatePointer);
WarpStatus	configureSensorIANA219();
WarpStatus      readCurrentRegisterIANA219();
WarpStatus      calibrateIANA219();
WarpStatus      readCurrentSignalIANA219(WarpTypeMask signal,
                                        WarpSignalPrecision precision,
                                        WarpSignalAccuracy accuracy,
                                        WarpSignalReliability reliability,
                                        WarpSignalNoise noise);

