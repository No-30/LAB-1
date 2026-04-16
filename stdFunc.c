#include "stdHeader.h"
#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrfx_uarte.h>
#include <stdlib.h>
#include <nrfx_rtc.h>
#include <nrfx_systick.h>
#include <nrf_gpio.h>

extern nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0);

int read_int()
{
    char charArr[STRING_LENGTH];
    int length = STRING_LENGTH;
    for(int i = 0; i < length; i++)
    {
        nrfx_uarte_rx (&instance, &uarteBuffer, sizeof(uarteBuffer));
        if (uarteBuffer != '\r')
        {
            charArr[i] = uarteBuffer;
        }
        else
        {
            charArr[i] = '\0';
            length = i;
        }
    }
    return atoi(charArr);
}

void uarte_write(char* data)
{
    nrfx_uarte_tx(&instance, data, strlen(data), 0);
}


void toggleLED()
{
    for(int i = 0; i < LED_ARR_LENGTH; i++){
        if(!nrf_gpio_pin_read(ButtonArr[i]))
        {
            LEDState[i] = (LEDState[i] + 1) % 2;
            nrf_gpio_pin_write(LEDArr[i], LEDState[i]);
            while(!nrf_gpio_pin_read(ButtonArr[i]))
            {
                nrfx_systick_delay_ms(50);
            }
        }
    }
}