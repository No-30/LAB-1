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
#include <list.h>
#include <BSTree.h>
#include <hashtable.h>

int main(void)
{
    char gridBuffer[512];
    nrfx_systick_state_t refreshTimer;

    initAll();
    interrupt_grid_reset();
    nrfx_systick_get(&refreshTimer);

    while (!interrupt_grid_is_finished())
    {
        if (uarteKeyReady)
        {
            uarteKeyReady = false;
            interrupt_grid_handle_key(uarteKey);
        }

        if (nrfx_systick_test(&refreshTimer, 250000))
        {
            nrfx_systick_get(&refreshTimer);
            if (interrupt_grid_render(gridBuffer, sizeof(gridBuffer)) > 0)
            {
                uarte_write(gridBuffer, 0);
                while (nrfx_uarte_tx_in_progress(&instance0)) {}
            }
        }
    }

    uarte_write("\r\nProgram finished.\r\n", 0);
    while (nrfx_uarte_tx_in_progress(&instance0)) {}
    return 0;
}