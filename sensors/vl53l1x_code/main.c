// Sensor Reading
// Read from Sparkfun distance sensor

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "app_error.h"
#include "app_util.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_serial.h"

#include "buckler.h"
#include "nrf_twi_mngr.h"
#include "vl53l1_api.h"

// I2C manager
NRF_TWI_MNGR_DEF(twi_mngr_instance, 5, 0);

int main(void)
{
    ret_code_t error_code = NRF_SUCCESS;

    // initialize RTT library
    error_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(error_code);
    NRF_LOG_DEFAULT_BACKENDS_INIT();
    printf("Log initialized!\n");

    // initialize the TWIM
    // nrf_drv_twi_config_t i2c_config = NRF_DRV_TWI_DEFAULT_CONFIG;
    // i2c_config.scl = BUCKLER_SENSORS_SCL;
    // i2c_config.sda = BUCKLER_SENSORS_SDA;
    // i2c_config.frequency = NRF_TWIM_FREQ_100K;
    // error_code = nrf_twi_mngr_init(&twi_mngr_instance, &i2c_config);
    // printf("error code is %x\n", error_code);
    // APP_ERROR_CHECK(error_code);
    // printf("going to initialize!\n");

    // // initialize tsl2561 driver
    // tsl2561_init(&twi_mngr_instance);
    // error_code = tsl2561_config();
    // printf("initialized!\n");
    // APP_ERROR_CHECK(error_code);

    // initialize vl53l1x driver
    VL53L1_DEV deviceHandle;
    deviceHandle->i2c_slave_address = 0x52;
    deviceHandle->comms_type = VL53L1_I2C;
    deviceHandle->comms_speed_khz = 400;
    VL53L1_Error error = VL53L1_DataInit(deviceHandle);
    printf(error);

    error = VL53L1_StartMeasurement(deviceHandle);

    // loop forever
    while (1)
    {
        printf("In the loop\n");
        printf("Debug reading: %x\n", print_debug());
        uint8_t dataReady;
        error = VL53L1_GetMeasurementDataReady(deviceHandle, &dataReading);
        while (dataReady == 0)
        {
            nrf_delay_ms(500);
        }
        error = VL53L1_RangingMeasurementData_t measurementData;
        VL53L1_GetRangingMeasurementData(deviceHandle, &measurementData);
        printf("Current reading of distance sensor: %d\n", measurementData->RangeMilliMeter);

        nrf_delay_ms(500);
    }
}
