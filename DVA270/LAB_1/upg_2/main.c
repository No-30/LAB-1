#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrfx_systick.h>
#include <nrf_gpio.h>

#define LED1 28
#define LED2 29
#define LED3 30
#define LED4 31
#define BUTTON1 23
#define BUTTON2 24
#define BUTTON3 8
#define BUTTON4 9
#define ARRLENGTH 4

int LEDArr[4] = {LED1, LED2, LED3, LED4};
int ButtonArr[4] = {BUTTON1, BUTTON2, BUTTON3, BUTTON4};
int LEDState[4] = {1, 1, 1, 1};

void buttonLEDToggle()
{
    for(int i = 0; i < ARRLENGTH; i++){
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

int main(void)
{ 
    nrfx_systick_init();

    for(int i = 0; i < ARRLENGTH; i++)
    {
        nrf_gpio_cfg_output(LEDArr[i]);
        nrf_gpio_pin_write(LEDArr[i], LEDState[i]);

        nrf_gpio_cfg_input(ButtonArr[i], NRF_GPIO_PIN_PULLUP);
    }

    while(1)
    {
        buttonLEDToggle();
        nrfx_systick_delay_ms(50);
    }
}