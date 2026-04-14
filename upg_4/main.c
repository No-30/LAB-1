#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrfx_uarte.h>
#include <stdlib.h>
#include <nrfx_rtc.h>
#include <nrfx_systick.h>
#include <nrf_gpio.h>

//definierar vilka pinnar som ska användas för att skicka och ta emot data:
#define PIN_TXD 20
#define PIN_RXD 22
#define BUTTON1 23

//Skapar en driver instance för UARTE:
nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0);

//skapar en buffer att ta emot tecken vi läser över UARTE
char sprintfBuffer[100];
int rtcTime = 0;
int rngNum;

const nrfx_rtc_t rtc_instance = NRFX_RTC_INSTANCE(0);

void rng()
{
    if(!nrf_gpio_pin_read(BUTTON1))
    {
        rtcTime = nrfx_rtc_counter_get(&rtc_instance);
        srand(rtcTime);
        rngNum = rand() % 42 + 1;
        sprintf(sprintfBuffer, "\n\r%d", rngNum);
        nrfx_uarte_tx(&instance, sprintfBuffer, strlen(sprintfBuffer), 0);
        while(!nrf_gpio_pin_read(BUTTON1))
        {
            nrfx_systick_delay_ms(50);
        }
    }
}

int main(void)
{ 
    nrfx_systick_init();
    //Vi kör med default settings och anger våra TX- och RX-pinnar:
    const nrfx_uarte_config_t configu = NRFX_UARTE_DEFAULT_CONFIG(PIN_TXD, PIN_RXD);

    //Initierar UARTE:
    nrfx_err_t erru = nrfx_uarte_init(&instance, &configu, NULL);
    if (erru != 0){
        //Här kan vi implementera felhantering, men för stunden håller vi tummarna att allt funkar
    }

    nrfx_rtc_config_t configc = NRFX_RTC_DEFAULT_CONFIG;
    nrfx_err_t errc = nrfx_rtc_init(&rtc_instance, &configc, NULL);
    nrfx_rtc_enable(&rtc_instance);

    nrf_gpio_cfg_input(BUTTON1, NRF_GPIO_PIN_PULLUP);

    

    while(1)
    {
        rng();
        nrfx_systick_delay_ms(50);
    }
    
}