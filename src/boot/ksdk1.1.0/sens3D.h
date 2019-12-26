#ifndef _SENSOR_3D_H
#define _SENSOR_3D_H

#include "devTCA9548A.h"

#define VL53L0XADDR 0x29

#define SENS0ADDR	0
#define SENS0X		0
#define SENS0Y		0

#define SENS1ADDR	1
#define SENS1X		0
#define SENS1Y		33

#define SENS2ADDR	7
#define SENS2X		(-30)
#define SENS2Y		(-21)

#define SENS3ADDR	6
#define SENS3X		30
#define SENS3Y		(-21)

struct surf3D {
	int curvature;
	int angle_z;
	int angle_x;
};

void initSens3D(const uint8_t i2cAddress, WarpI2CDeviceState volatile *TCA9548AdeviceState);
WarpStatus readDistanceSens3D(uint8_t tofSens);
WarpStatus detectSurf(struct surf3D *scanRes);

#endif /* _SENSOR_3D_H */
