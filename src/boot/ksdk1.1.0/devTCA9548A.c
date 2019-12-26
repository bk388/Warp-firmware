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

extern volatile WarpI2CDeviceState	deviceTCA9548AState;
extern volatile uint32_t		gWarpI2cBaudRateKbps;



void
initTCA9548A(const uint8_t i2cAddress, WarpI2CDeviceState volatile *  deviceStatePointer)
{
	SEGGER_RTT_WriteString(0, "\rinitTCA9548A function start\n");
	deviceStatePointer->i2cAddress	= i2cAddress;

	return;
}

WarpStatus
selectTCA9548Asens(uint8_t tcaSel)
{
	uint8_t commandByte[1] = {1 << tcaSel};
	i2c_status_t status;

	i2c_device_t slave =
	{
		.address = deviceTCA9548AState.i2cAddress,
		.baudRate_kbps = gWarpI2cBaudRateKbps
	};

	status = I2C_DRV_MasterSendDataBlocking(
						0,
						&slave,
						commandByte,
						1,
						NULL,
						0,
						100);
	if (status != kStatus_I2C_Success)
	{
		return kWarpStatusDeviceCommunicationFailed;
	}

	return kWarpStatusOK;
}

WarpStatus
writeSensorRegisterTCA9548A(uint8_t deviceRegister, uint8_t *payloadBuf, uint8_t numberOfBytes)
{
	uint8_t commandByte[1]	= {0xFF};
	i2c_status_t	status;

	i2c_device_t slave =
	{
		.address = deviceTCA9548AState.i2cAddress,
		.baudRate_kbps = gWarpI2cBaudRateKbps
	};

	commandByte[0] = deviceRegister;

	status = I2C_DRV_MasterSendDataBlocking(
						0,
						&slave,
						commandByte,
						1,
						payloadBuf,
						numberOfBytes,
						100);
	if (status != kStatus_I2C_Success)
	{
		return kWarpStatusDeviceCommunicationFailed;
	}

	return kWarpStatusOK;
}



WarpStatus
readSensorRegisterTCA9548A(uint8_t deviceRegister, int numberOfBytes)
{
	uint8_t		cmdBuf[1] = {0xFF};
	i2c_status_t	status;
	USED(numberOfBytes);

	i2c_device_t slave =
	{
		.address = deviceTCA9548AState.i2cAddress,
		.baudRate_kbps = gWarpI2cBaudRateKbps
	};

	cmdBuf[0] = deviceRegister;

	status = I2C_DRV_MasterReceiveDataBlocking(
							0,
							&slave,
							cmdBuf,
							1,
							(uint8_t *)deviceTCA9548AState.i2cBuffer,
							numberOfBytes,
							500);
	if (status != kStatus_I2C_Success)
	{
		return kWarpStatusDeviceCommunicationFailed;
	}

	return kWarpStatusOK;
}
