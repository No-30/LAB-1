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
#include <stdHeader.h>

#define BAUDRATE 115200
#define BBUART_TX 38 //P1.06 närmast skärmkontakten

int main(void)
{
    char echoBuffer[2];

    initAll();
    sprintf(sprintfBuffer, "\n\rEcho test\n\r");
    uarte_write(sprintfBuffer, 0);
    //uarte_write(sprintfBuffer, 1);
    //uart_bb_tx(BBUART_TX, '\r', BAUDRATE);
    //uart_bb_tx(BBUART_TX, '\n', BAUDRATE);

    while(1)
    {
        /*if (uarte0ByteReady)
        {
            uarte0ByteReady = false;
            echoBuffer[0] = uarte0Byte;
            echoBuffer[1] = '\0';
            uart_bb_tx(BBUART_TX, echoBuffer[0], BAUDRATE);
            //uarte_write(echoBuffer, 1);
            while (nrfx_uarte_tx_in_progress(&instance1)) {}
        }*/
        if (uarte1ByteReady)
        {
            uarte1ByteReady = false;
            echoBuffer[0] = uarte1Byte;
            echoBuffer[1] = '\0';
            int rxByte = (int)uarte1Byte;
            char rxString[10];
            for (int i = 0; i < 8; i++)
            {
                rxString[7 - i] = (rxByte & (1 << i)) ? '1' : '0'; //kort if else
            }
            rxString[8] = '\r';
            rxString[9] = '\n';
            for (int i = 0; i < 10; i++)
            {
                uart_bb_tx(BBUART_TX, rxString[i], BAUDRATE);
                while (nrfx_uarte_tx_in_progress(&instance0)) {}
            }
            //sprintf(sprintfBuffer, "\n\rReceived: %s\n\r", rxString);
            //uarte_write(sprintfBuffer, 0);
            //uarte_write(echoBuffer, 0);
            //while (nrfx_uarte_tx_in_progress(&instance0)) {}//01234567
        }
    }
}