#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrfx_uarte.h>
#include <stdlib.h>
#include <nrfx_rtc.h>
#include <nrfx_systick.h>
#include <nrf_gpio.h>
#include <stdHeader.h>

//#include "nrf.h"

#define PIN_IN 4   // P0.04
#define PIN_OUT  7   // P0.07 output

volatile uint8_t pin_triggered = 0;

void GPIOTE0_IRQHandler(void)
{
    if (NRF_GPIOTE0->EVENTS_IN[0]) {
        NRF_GPIOTE0->EVENTS_IN[0] = 0;   // Clear event

        pin_triggered = 1;              // Signal main loop
        // Your interrupt logic here
        // Example:
        // toggle LED, set flag, etc.
    }
}

void gpio_interrupt_init(void)
{
    // Configure P0.04 as input with pull-down
    NRF_P0->PIN_CNF[PIN_IN] =
        (GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos) |
        (GPIO_PIN_CNF_PULL_Pulldown << GPIO_PIN_CNF_PULL_Pos);

    // Configure P0.07 as output
    NRF_P0->PIN_CNF[PIN_OUT] =
        (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);

    // Configure GPIOTE channel 0 for rising-edge detection on P0.04
    NRF_GPIOTE0->CONFIG[0] =
        (GPIOTE_CONFIG_MODE_Event << GPIOTE_CONFIG_MODE_Pos) |
        (PIN_IN << GPIOTE_CONFIG_PSEL_Pos) |
        (GPIOTE_CONFIG_POLARITY_LoToHi << GPIOTE_CONFIG_POLARITY_Pos);

    NRF_GPIOTE0->EVENTS_IN[0] = 0;

    // Enable interrupt in NVIC
    NVIC_ClearPendingIRQ(GPIOTE0_IRQn);
    NVIC_SetPriority(GPIOTE0_IRQn, 3);
    NVIC_EnableIRQ(GPIOTE0_IRQn);

    // Enable interrupt for channel 0
    NRF_GPIOTE0->INTENSET = GPIOTE_INTENSET_IN0_Msk;
}

void main(void)
{
    // Initialize GPIO interrupt
    gpio_interrupt_init();

    while (1) {
        // Main loop can perform other tasks or enter low power mode
        nrfx_systick_delay_ms(100); // Wait for event (low power mode until an interrupt occurs)
    }
}