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

    List stack = create_empty_list();
    List queue = create_empty_list();
    //nu är initialisering klar

    char sprintfBuffer[STRING_LENGTH];
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
                // enqueue
                add_last(&queue, rngNum);
            }
            else
            {
                // push
                add_last(&stack, rngNum);
            }
            break;

        case BUTTON2:
            // pop
            if (number_of_nodes)
            {
                remove_last(&stack, rngNum);
            }
            break;

        case BUTTON3:
            // deque
            if (number_of_nodes)
            {
                remove_first(&stack, rngNum);
            }
            break;

        default:
            break;
        }

        // front and peek
        int front = get_first_element(queue);
        int peek = get_last_element(stack);
        sprintf(sprintfBuffer, "\n\r Front: %d\n Peek: %d", front, peek);

        uarte_write(sprintfBuffer);
        delay(1, 's');
    }
}