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
#include "list.h"

int main(void)
{ 
    List head = create_empty_list();  //Kom ihåg att head alltid ska peka på det första elementet i lista
    initUART();
}