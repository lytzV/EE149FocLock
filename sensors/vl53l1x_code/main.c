#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "app_uart.h"
#include "nrf_uarte.h"
#include "nrf_power.h"

// Pin configurations
#define LED NRF_GPIO_PIN_MAP(0, 17)
#define UART_RX NRF_GPIO_PIN_MAP(0, 8)
#define UART_TX NRF_GPIO_PIN_MAP(0, 6)
#define UART_TX_BUF_SIZE 256
#define UART_RX_BUF_SIZE 256

uint8_t r_data = 0;
uint32_t r_error = 0;

// error handler for UART
void uart_error_handle(app_uart_evt_t *p_event)
{
    if (p_event->evt_type == APP_UART_DATA_READY)
    {
        r_error = app_uart_get(&r_data);
        if (r_error > 0)
        {
            printf("Reading %d\n", r_data);
        }
        else
        {
            printf("Reading error!");
        }
    }
    // just call app error handler
    else if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR)
    {
        //APP_ERROR_HANDLER(p_event->data.error_communication);
    }
    else if (p_event->evt_type == APP_UART_FIFO_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_code);
    }
}

// initialization of UART
void uart_init(void)
{
    uint32_t err_code;

    // configure RX and TX pins
    // no RTS or CTS pins with flow control disabled
    // no parity
    // baudrate 115200
    const app_uart_comm_params_t comm_params = {
        UART_RX,
        UART_TX,
        0,
        0,
        APP_UART_FLOW_CONTROL_DISABLED,
        false,
        NRF_UARTE_BAUDRATE_115200};

    // actually initialize UART
    APP_UART_FIFO_INIT(&comm_params, UART_RX_BUF_SIZE, UART_TX_BUF_SIZE,
                       uart_error_handle, APP_IRQ_PRIORITY_LOW, err_code);
    APP_ERROR_CHECK(err_code);

    printf("ERROR: %d\n", err_code);
}

int main(void)
{
    // init led
    nrf_gpio_cfg_output(LED);
    nrf_gpio_pin_set(LED);

    // init uart
    uart_init();

    int val = 0;
    uint8_t data_sent = 1;
    int i = 0;

    while (i < 10)
    {
        r_error = app_uart_put(data_sent);
        if (r_error == NRF_SUCCESS)
        {
            printf("Writing %u\n", r_data);
        }
        else
        {
            printf("Writing error!");
        }
        i++;
        nrf_delay_ms(20);
    }

    nrf_delay_ms(1000);

    while (i < 20)
    {
        r_error = app_uart_get(&r_data);
        if (r_error == NRF_SUCCESS)
        {
            printf("Reading %u\n", r_data);
        }
        else
        {
            printf("Reading error!");
        }
        i++;
        nrf_delay_ms(20);
    }

    while (1)
    {
        //printf("Loop Count %d\n", val++);
        nrf_gpio_pin_toggle(LED);
        nrf_delay_ms(20);
    }
}
