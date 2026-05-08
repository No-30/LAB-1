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
    initAll();

    HashTable ht;
    initTable(&ht);

    int to_insert_key = 0;
    char value_buffer[20];

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        to_insert_key = i;
        sprintf(value_buffer, "val%d", to_insert_key);  // Enkelt värde baserat på nyckel
        insert(&ht, to_insert_key, value_buffer);
    }

    int getNumber[] = {2, 5, 9};
    int pretime, posttime;

    for (int i = 0; i < 3; i++)
    {
        nrf_systick_val_clear();
        pretime = nrf_systick_val_get();
        char* val = get(&ht, getNumber[i]);
        posttime = nrf_systick_val_get();
        posttime = pretime - posttime;
        if (val) {
            sprintf(sprintfBuffer, "Get key %d: %s, time: %d ticks\n\r", getNumber[i], val, posttime);
            uarte_write(sprintfBuffer);
        } else {
            sprintf(sprintfBuffer, "Get key %d: NULL (not found), time: %d ticks\n\r", getNumber[i], posttime);
            uarte_write(sprintfBuffer);
        }
    }
    printTable(&ht);
}