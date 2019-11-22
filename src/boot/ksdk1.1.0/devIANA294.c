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

extern volatile WarpI2CDeviceState      deviceIANA219State;
extern volatile uint32_t                gWarpI2cBaudRateKbps;
extern volatile uint32_t                gWarpI2cTimeoutMilliseconds;
extern volatile uint32_t                gWarpSupplySettlingDelayMilliseconds;

WarpStatus
writeIANA219Register(uint8_t reg, uint16_t value)
{
	uint8_t         payloadByte[2], commandByte[1];
	i2c_status_t    status;

	i2c_device_t slave =
	{
		.address = deviceIANA219State.i2cAddress,
		.baudRate_kbps = gWarpI2cBaudRateKbps
	};

	commandByte[0] = reg;
	payloadByte[0] = (uint8_t)((value >> 8) & 0xFF);
	payloadByte[1] = (uint8_t)(value & 0xFF);
        status = I2C_DRV_MasterSendDataBlocking(
                                                        0 /* I2C instance */,
                                                        &slave,
                                                        commandByte,
                                                        1,
                                                        payloadByte,
                                                        2,
                                                        gWarpI2cTimeoutMilliseconds);
        if (status != kStatus_I2C_Success)
        {
                return kWarpStatusDeviceCommunicationFailed;
        }

        return kWarpStatusOK;
}

WarpStatus
readIANA219Register(uint8_t reg)
{
        uint8_t         cmdBuf[1] = {0xFF};
        i2c_status_t    status;
	
	//USED(numberOfBytes);
        i2c_device_t slave =
        {
                .address = deviceIANA219State.i2cAddress,
                .baudRate_kbps = gWarpI2cBaudRateKbps
        };
	cmdBuf[0] = reg;
        status = I2C_DRV_MasterReceiveDataBlocking(
                                                        0 /* I2C peripheral instance */,
                                                        &slave,
                                                        cmdBuf,
                                                        1,
                                                        (uint8_t *)deviceIANA219State.i2cBuffer,
                                                        2,
                                                        gWarpI2cTimeoutMilliseconds);

        if (status != kStatus_I2C_Success)
        {
                return kWarpStatusDeviceCommunicationFailed;
        }

        return kWarpStatusOK;

}

void
initIANA219(const uint8_t i2cAddress, WarpI2CDeviceState volatile *  deviceStatePointer)
{
	deviceStatePointer->i2cAddress  = i2cAddress;
	deviceStatePointer->signalType  = ( 0xffffffff );

        return;
}

WarpStatus
calibrateIANA219()
{
	WarpStatus      i2cWriteStatus1;
	i2cWriteStatus1 = writeIANA219Register(0x05, (uint16_t)8192);
	return i2cWriteStatus1;
}

WarpStatus
configureSensorIANA219()
{
	WarpStatus      i2cWriteStatus1, i2cWriteStatus2;
	/*
	16V, 400mA
	ina219_calValue = 8192;
	ina219_currentDivider_mA = 20;
	ina219_powerMultiplier_mW = 1.0f;
	*/
	i2cWriteStatus1 = writeIANA219Register(0x05, (uint16_t)8192);
	i2cWriteStatus2 = writeIANA219Register(0x00, 0x019f);
	return (i2cWriteStatus1 | i2cWriteStatus2);
}

WarpStatus
readCurrentRegisterIANA219()
{
	WarpStatus      i2cWriteStatus1, i2cWriteStatus2;
	i2cWriteStatus1 = calibrateIANA219();
	i2cWriteStatus2 = readIANA219Register(0x04);
	return (i2cWriteStatus1 | i2cWriteStatus2);
}

