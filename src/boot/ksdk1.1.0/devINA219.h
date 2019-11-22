#ifndef WARP_BUILD_ENABLE_DEVINA219
#define WARP_BUILD_ENABLE_DEVINA219
#endif /* WARP_BUILD_ENABLE_DEVINA219 */

void 		initINA219(const uint8_t i2cAddress, WarpI2CDeviceState volatile *  deviceStatePointer);
WarpStatus	configureSensorINA219();
WarpStatus      readCurrentRegisterINA219();
WarpStatus      calibrateINA219();
WarpStatus      readCurrentSignalINA219(WarpTypeMask signal,
                                        WarpSignalPrecision precision,
                                        WarpSignalAccuracy accuracy,
                                        WarpSignalReliability reliability,
                                        WarpSignalNoise noise);
void		printCurrentiINA219();
