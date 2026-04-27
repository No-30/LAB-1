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
#include <list.h>

int main(void)
{ 
    confButtons();
    initSystick();
    initUART();
    
    waitForButton(BUTTON1);
    initRTC();

    //nu är initialisering klar

    int pressedButton = buttonPressed();
    int rngNum;

    while (1)
    {
        switch (pressedButton)
        {
        case BUTTON1:
            rngNum = rand() % 10 + 1;
            if (rngNum % 2)
            {
                // enque
            }
            else
            {
                // push
            }
            break;

        case BUTTON2:
            // pop
            break;

        case BUTTON3:
            // deque
            break;

        default:
            break;
        }

        // front and peek
        delay(1, 's');
    }
}