#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_uarte.h"
#include "nrf_power.h"
#include "nrf_drv_clock.h"
#include "nrf_serial.h"
#include "app_timer.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "buckler.h"
#include "display.h"
#include "kobukiActuator.h"
#include "kobukiUtilities.h"
#include "kobukiSensorPoll.h"
#include "kobukiSensorTypes.h"
#include "mpu9250.h"

// Config
#define BUCKLER_UART_RX 15
#define BUCKLER_UART_TX 16
#define SERIAL_FIFO_TX_SIZE 512
#define SERIAL_FIFO_RX_SIZE 512
#define serial_buff2_TX_SIZE 256
#define serial_buff2_RX_SIZE 256

// Config Definition
NRF_SERIAL_DRV_uart_config2_DEF(uart_config2,
                               BUCKLER_UART_RX, BUCKLER_UART_TX,
                               0, 0,
                               NRF_UART_HWFC_DISABLED, NRF_UART_PARITY_EXCLUDED,
                               NRF_UART_BAUDRATE_115200,
                               UART_DEFAULT_CONFIG_IRQ_PRIORITY);
NRF_serial_queue2S_DEF(serial_queue2, SERIAL_FIFO_TX_SIZE, SERIAL_FIFO_RX_SIZE);
NRF_serial_buff2ERS_DEF(serial_buff2, serial_buff2_TX_SIZE, serial_buff2_RX_SIZE);
static void ser_event_handler(nrf_serial_t const *p_serial, nrf_serial_event_t event);
NRF_serial_config2_DEF(serial_config2, NRF_SERIAL_MODE_DMA,
                      &serial_queue2, &serial_buff2, ser_event_handler, NULL);

NRF_serial_uart2_DEF(serial_uart2, 0);

float data;
uint8_t *data_array = (uint8_t *)&data;
uint32_t r_error = 0;

// Error Handler for UART
static void ser_event_handler(nrf_serial_t const *p_serial, nrf_serial_event_t event)
{
    switch (event)
    {
    case NRF_SERIAL_EVENT_TX_DONE:
    {
        break;
    }
    case NRF_SERIAL_EVENT_RX_DATA:
    {
        data = 0;
        size_t read;
        nrf_serial_read(&serial_uart2, data_array, sizeof(data_array), &read, 0);
        printf("Reading %f\n", data);
        break;
    }
    case NRF_SERIAL_EVENT_DRV_ERR:
    {
        nrf_serial_rx_drain(&serial_uart2);
        nrf_serial_uninit(&serial_uart2);
        nrf_serial_init(&serial_uart2, &uart_config2, &serial_config2);
        break;
    }
    case NRF_SERIAL_EVENT_FIFO_ERR:
    {
        break;
    }
    }
}

int main(void)
{
    ret_code_t error_code = NRF_SUCCESS;

    // initialize kobuki
    // kobukiInit();
    // printf("Kobuki initialized!\n");

    nrf_serial_init(&serial_uart2, &uart_config2, &serial_config2);
    printf("NRF initialized!\n");

    while (1)
    {
        nrf_delay_ms(1);
    }
}