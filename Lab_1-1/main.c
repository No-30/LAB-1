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

int main(void)
{
    char echoBuffer[2];

    initAll();
    sprintf(sprintfBuffer, "\n\rEcho test\n\r");
    uarte_write(sprintfBuffer, 0);
    uarte_write(sprintfBuffer, 1);

    while (1)
    {
        if (uarte0ByteReady)
        {
            uarte0ByteReady = false;
            echoBuffer[0] = uarte0Byte;
            echoBuffer[1] = '\0';
            uarte_write(echoBuffer, 1);
            while (nrfx_uarte_tx_in_progress(&instance1)) {}
        }

        if (uarte1ByteReady)
        {
            uarte1ByteReady = false;
            echoBuffer[0] = uarte1Byte;
            echoBuffer[1] = '\0';
            uarte_write(echoBuffer, 0);
            while (nrfx_uarte_tx_in_progress(&instance0)) {}
        }
    }
}