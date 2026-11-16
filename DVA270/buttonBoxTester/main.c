#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrfx_uarte.h>
#include <stdlib.h>
#include <math.h>
#include <nrfx_rtc.h>
#include <nrfx_systick.h>
#include <nrf_gpio.h>

#define STRING_LENGTH 100
#define BUTTON_PIN 4
#define LED1_PIN 36
#define LED2_PIN 37
#define LED3_PIN 38
#define LED4_PIN 39
#define LED5_PIN 40
#define LED6_PIN 41
#define LED7_PIN 42
#define LED8_PIN 43
#define LED9_PIN 44
#define LED_ARR_LENGTH 9
#define LED_ON 1
#define LED_OFF 0
#define UART_TX 20
#define UART_RX 22
#define UNO_TX 33
#define UNO_RX 32
#define BUTTON_ARR_LENGTH 9

int LEDState[LED_ARR_LENGTH] = { LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF };
int borderVal[9][2] = {{15, 19}, {89, 93}, {230, 235}, {508, 508}, {695, 702}, {927, 935}, {965, 975}, {995, 1005}, {1010, 1070}};
int LEDArr[LED_ARR_LENGTH] = { LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN, LED5_PIN, LED6_PIN, LED7_PIN, LED8_PIN, LED9_PIN };

char uarteBuffer;
char sprintfBuffer[STRING_LENGTH];

nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0);
const nrfx_rtc_t rtc_instance = NRFX_RTC_INSTANCE(0);

nrfx_uarte_t instance_u = NRFX_UARTE_INSTANCE(0);
const nrfx_rtc_t rtc_instance_u = NRFX_RTC_INSTANCE(0);

void uarte_write(char* data)
{
    nrfx_uarte_tx(&instance, data, strlen(data), 0);  // Skicka data via UART
}

void delay(int time, char unit)//case för ms s
{
    switch (unit)
    {
    case 's': //second
        time *= 1000;  // Konvertera sekunder till millisekunder
        break;
    
    case 't': //tenth second
        time *= 100;  // Konvertera tiondels sekunder till millisekunder
        break;
    
    
    case 'm': //millisecond
        time *= 1;  // Millisekunder som är
        break;
    
    default:
        break;
    }
    nrfx_systick_delay_ms(time);  // Fördröj med angiven tid
}

void initUART()
{
    const nrfx_uarte_config_t configu = NRFX_UARTE_DEFAULT_CONFIG(UART_TX, UART_RX);
    nrfx_err_t erru = nrfx_uarte_init(&instance, &configu, NULL);  // Initiera UART med standardkonfiguration
    if (erru != 0){
        //Här kan vi implementera felhantering, men för stunden håller vi tummarna att allt funkar
    }

    const nrfx_uarte_config_t config_u = NRFX_UARTE_DEFAULT_CONFIG(UNO_TX, UNO_RX);
    nrfx_err_t err_u = nrfx_uarte_init(&instance_u, &config_u, NULL);  // Initiera UART med standardkonfiguration
    if (err_u != 0){
        //Här kan vi implementera felhantering, men för stunden håller vi tummarna att allt funkar
    }
}

void confLEDs()
{
    for(int i = 0; i < LED_ARR_LENGTH; i++)
    {
        nrf_gpio_cfg_output(LEDArr[i]);  // Konfigurera LED som utgångar
        nrf_gpio_pin_write(LEDArr[i], LEDState[i]);  // Sätt initialt tillstånd
    }
}

void toggleLED(int led)
{
    LEDState[led] = (LEDState[led] + 1) % 2;  // Växla tillstånd för specifik LED
    nrf_gpio_pin_write(LEDArr[led], LEDState[led]);  // Uppdatera LED
}

void initSystick()
{
    nrfx_systick_init();  // Initiera systick för fördröjningar
}

int read_UNO()
{
    int read = 0;
    int length = STRING_LENGTH;

    sprintf(sprintfBuffer, "Hej");
    uarte_write(sprintfBuffer);
    
    for(int i = 0; i < length; i++)
    {
        nrfx_uarte_rx (&instance_u, &uarteBuffer, sizeof(uarteBuffer));  // Läs ett tecken från UART
        if (uarteBuffer != '\r')
        {
            sprintfBuffer[i] = uarteBuffer;  // Lägg till tecknet i arrayen
        }
        else
        {
            sprintfBuffer[i] = '\0';  // Avsluta strängen med null-terminator
            length = i;  // Uppdatera längden
        }
    }
    sprintf(sprintfBuffer, "Hej");
    uarte_write(sprintfBuffer);


    return atoi(sprintfBuffer);
}

void initAll()
{
    
    initSystick();  // Initiera systick
    initUART();  // Initiera UART

    confLEDs();  // Konfigurera LED
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < LED_ARR_LENGTH; j++)
        {
            toggleLED(j);  // Växla varje LED
            delay(50, 'm');  // Kort fördröjning
        }
    }

    sprintf(sprintfBuffer, "\n\rAll initiated\n\r");
    uarte_write(sprintfBuffer);  // Bekräfta att allt är initierat

}

int main(void)
{ 
    initAll();

    //nrf_gpio_cfg_input(BUTTON_PIN, NRF_GPIO_PIN_PULLUP);  // Konfigurera LED som utgångar

    int readVal;

    while(1)
    {
        readVal = read_UNO();
        sprintf(sprintfBuffer, "\n\r%d", readVal);
        uarte_write(sprintfBuffer);
        delay(100, 'm');
    }
}