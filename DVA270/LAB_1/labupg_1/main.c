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
#define LED1 28
#define LED2 29
#define LED3 30
#define LED4 31
#define ARRLENGTH 4
#define LEDON 0
#define LEDOFF 1
#define charArrLength 10

//Skapar en driver instance för UARTE:
nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0);

//skapar en buffer att ta emot tecken vi läser över UARTE
char sprintfBuffer[100];
int rtcTime = 0;
int LEDArr[4] = {LED1, LED2, LED3, LED4};
char uarte_buffer;


const nrfx_rtc_t rtc_instance = NRFX_RTC_INSTANCE(0);

void rng(int amount, int delay)
{
    int rngNum;
    //rtcTime = nrfx_rtc_counter_get(&rtc_instance);
    //srand(rtcTime);
    for(int i = 0; i < amount; i++)
    {
        rngNum = rand() % 4;
        nrf_gpio_pin_write(LEDArr[rngNum], LEDON);
        nrfx_systick_delay_ms(delay);
        nrf_gpio_pin_write(LEDArr[rngNum], LEDOFF);
    }
}

int read_int()
{
    char charArr[charArrLength];
    int length = charArrLength;
    for(int i = 0; i < length; i++)
    {
        nrfx_uarte_rx (&instance, &uarte_buffer, sizeof(uarte_buffer));
        if (uarte_buffer != '\r')
        {
            charArr[i] = uarte_buffer;
        }
        else
        {
            charArr[i] = '\0';
            length = i;
        }
    }
    return atoi(charArr);
}

int main(void)
{ 
    int amount, delay;


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
    //config fram tills hit


    nrf_gpio_cfg_input(BUTTON1, NRF_GPIO_PIN_PULLUP);

    for(int i = 0; i < ARRLENGTH; i++)
    {
        nrf_gpio_cfg_output(LEDArr[i]);
        
            nrf_gpio_pin_write(LEDArr[i], LEDOFF);
    }

    int whileloop = 1;
    while(whileloop)
    {
        if(!nrf_gpio_pin_read(BUTTON1))
        {
            rtcTime = nrfx_rtc_counter_get(&rtc_instance);
            srand(rtcTime);
            while(!nrf_gpio_pin_read(BUTTON1))
            {
                nrfx_systick_delay_ms(50);
                whileloop = 0;
            }
        }
        nrfx_systick_delay_ms(50);
    }
        sprintf(sprintfBuffer, "\n\r Skriv in amount \n\r");
        nrfx_uarte_tx(&instance, sprintfBuffer, strlen(sprintfBuffer), 0);
        amount = read_int();
        sprintf(sprintfBuffer, "\n\r Skriv in delay \n\r");
        nrfx_uarte_tx(&instance, sprintfBuffer, strlen(sprintfBuffer), 0);
        delay = read_int();

        rng(amount, delay);

        sprintf(sprintfBuffer, "\n\r Vi har väntat i %d ms", amount*delay);
        nrfx_uarte_tx(&instance, sprintfBuffer, strlen(sprintfBuffer), 0);
}