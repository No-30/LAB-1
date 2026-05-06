#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrfx_uarte.h>
#include <stdlib.h>
#include <nrfx_rtc.h>
#include <nrfx_systick.h>
#include <nrf_gpio.h>
// #include <stdHeader.h>
#include "list.h"

#define BUTTON1 23
#define BUTTON2 24
#define BUTTON3 8
#define BUTTON4 9
#define UART_TX 20
#define UART_RX 22
#define BUTTON_ARR_LENGTH 4
#define STRING_LENGTH 100

nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0);
const nrfx_rtc_t rtc_instance = NRFX_RTC_INSTANCE(0);
int ButtonArr[BUTTON_ARR_LENGTH] = {BUTTON1, BUTTON2, BUTTON3, BUTTON4};
char uarteBuffer;
char sprintfBuffer[STRING_LENGTH];
char string[STRING_LENGTH];
int rtcTime = 0;

void uarte_write(char *data)
{
    nrfx_uarte_tx(&instance, data, strlen(data), 0);
}
void initSystick()
{
    nrfx_systick_init();
}

void initRTC()
{
    nrfx_rtc_config_t configc = NRFX_RTC_DEFAULT_CONFIG;
    nrfx_err_t errc = nrfx_rtc_init(&rtc_instance, &configc, NULL);
    nrfx_rtc_enable(&rtc_instance);
    rtcTime = nrfx_rtc_counter_get(&rtc_instance);
    srand(rtcTime);
}

void initUART()
{
    const nrfx_uarte_config_t configu = NRFX_UARTE_DEFAULT_CONFIG(UART_TX, UART_RX);
    nrfx_err_t erru = nrfx_uarte_init(&instance, &configu, NULL);
    if (erru != 0)
    {
        // Här kan vi implementera felhantering, men för stunden håller vi tummarna att allt funkar
    }
}

void confButtons()
{
    for (int i = 0; i < BUTTON_ARR_LENGTH; i++)
    {
        nrf_gpio_cfg_input(ButtonArr[i], NRF_GPIO_PIN_PULLUP);
    }
}

void delay(int time, char unit) // case för ms s
{
    switch (unit)
    {
    case 's': // second
        time *= 1000;
        break;

    case 't': // tenth second
        time *= 100;
        break;

    case 'm': // millisecond
        time *= 1;
        break;

    default:
        break;
    }
    nrfx_systick_delay_ms(time);
}

void waitForButton(int button)
{
    int whileloop = 1;
    while (whileloop)
    {
        if (!nrf_gpio_pin_read(button))
        {
            while (!nrf_gpio_pin_read(button))
            {
                nrfx_systick_delay_ms(50);
                whileloop = 0;
            }
        }
        nrfx_systick_delay_ms(50);
    }
}

int buttonPressed()
{
    int whileloop = 1;
    while (whileloop)
    {
        for (int i = 0; i < BUTTON_ARR_LENGTH; i++)
        {
            if (!nrf_gpio_pin_read(ButtonArr[i]))
            {
                while (!nrf_gpio_pin_read(ButtonArr[i]))
                {
                    nrfx_systick_delay_ms(50);
                    whileloop = 0;
                    return i;
                }
                nrfx_systick_delay_ms(50);
            }
        }
    }
}

int main(void)
{
    confButtons();
    initSystick();
    initUART();
    sprintf(sprintfBuffer, "\n\rPress Button 1 to start RTC\n\r");
    uarte_write(sprintfBuffer);
    waitForButton(BUTTON1);

    initRTC();

    List stack = create_empty_list();
    List queue = create_empty_list();
    // nu är initialisering klar

    int pressedButton = 0;
    int rngNum;

    while (1)
    {
        sprintf(sprintfBuffer, "\n\rTryck en knapp\n\r");
        uarte_write(sprintfBuffer);
        pressedButton = buttonPressed();
        /*sprintf(sprintfBuffer, "\n\r%d", pressedButton);
        uarte_write(sprintfBuffer);*/
        if (pressedButton == 0)
        {
            /*sprintf(sprintfBuffer, "1");
            uarte_write(sprintfBuffer);*/
            rngNum = rand() % 10 + 1;

            /*sprintf(sprintfBuffer, "\n\rrngNum: %d", rngNum);
            uarte_write(sprintfBuffer);*/
            if (rngNum % 2)
            {
                // enqueue
                add_last(&queue, rngNum);
            }
            else
            {
                // push
                add_last(&stack, rngNum);
            }
        }
        else if (pressedButton == 1)
        {
            /*sprintf(sprintfBuffer, "2");
            uarte_write(sprintfBuffer);*/
            if (number_of_nodes(stack))
            {
                remove_last(&stack);
            }
        }
        else if (pressedButton == 2)
        {
            /*sprintf(sprintfBuffer, "3");
            uarte_write(sprintfBuffer);*/
            if (number_of_nodes(queue))
            {
                remove_first(&queue);
            }
        }
        else
        {
            sprintf(sprintfBuffer, "\n\rfel");
            uarte_write(sprintfBuffer);
        }

        /*sprintf(sprintfBuffer, "\n\r%d", pressedButton);
        uarte_write(sprintfBuffer);*/

        // front and peek
        int front = 0;
        if (number_of_nodes(queue))
        {
            front = get_first_element(queue);
        }
        int peek = 0;
        if (number_of_nodes(stack))
        {
            peek = get_last_element(stack);
        }
        sprintf(sprintfBuffer, "\n\r Front: %d\n\r Peek: %d \n\r", front, peek);

        uarte_write(sprintfBuffer);
        delay(1, 's');
    }
}