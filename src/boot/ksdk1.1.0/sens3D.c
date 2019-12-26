#include <stdlib.h>

#include "fsl_misc_utilities.h"
#include "fsl_device_registers.h"
#include "fsl_i2c_master_driver.h"
#include "fsl_spi_master_driver.h"
#include "fsl_rtc_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_power_manager.h"
#include "fsl_mcglite_hal.h"
#include "fsl_port_hal.h"

#include "gpio_pins.h"
#include "SEGGER_RTT.h"
#include "warp.h"
#include "sens3D.h"


extern volatile WarpI2CDeviceState	deviceTCA9548AState;
extern volatile uint32_t		gWarpI2cBaudRateKbps;


void
initSens3D(const uint8_t i2cAddress, WarpI2CDeviceState volatile *TCA9548AdeviceState)
{
	SEGGER_RTT_WriteString(0, "\rinitializing 3D sensor\n");
	initTCA9548A(i2cAddress, TCA9548AdeviceState);
	return;
}

WarpStatus
readDistanceSens3D(uint8_t tofSens)
{
	selectTCA9548Asens(
}

WarpStatus
detectSurf(struct surf3D *scanRes)
{
}

