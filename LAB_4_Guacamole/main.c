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
#include <Guacamole.h>
#include <stdio.h>

void on_input(char c)
{
    handle_input(c);
}

int main(void)
{ 
    initAll_Mod();

    int alive = 1;
    game(alive);

    sprintf(sprintfBuffer, "\n\rGame Over :(");
    uarte_write(sprintfBuffer);
}