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

    // Testa HashTable-funktioner
    HashTable ht;
    initTable(&ht);

    // Testa infogning med slumpmässiga nycklar och värden (likt BST-testet)
    int to_insert_key = 0;
    char value_buffer[20];

    for (int i = 0; i < 10; i++)
    {
        to_insert_key = rand() % 101;  // Slumpmässig nyckel 0-100
        sprintf(value_buffer, "val%d", to_insert_key);  // Enkelt värde baserat på nyckel
        insert(&ht, to_insert_key, value_buffer);
    }

    // Testa get för några slumpmässiga nycklar
    for (int i = 0; i < 5; i++)
    {
        int test_key = rand() % 101;
        char* val = get(&ht, test_key);
        if (val) {
            sprintf(sprintfBuffer, "Get key %d: %s\n\r", test_key, val);
            uarte_write(sprintfBuffer);
        } else {
            sprintf(sprintfBuffer, "Get key %d: NULL (not found)\n\r", test_key);
            uarte_write(sprintfBuffer);
        }
    }

    // Testa remove för några slumpmässiga nycklar
    for (int i = 0; i < 3; i++)
    {
        int remove_key = rand() % 101;
        int removed = removeKey(&ht, remove_key);
        sprintf(sprintfBuffer, "Remove key %d: %s\n\r", remove_key, removed ? "success" : "failed");
        uarte_write(sprintfBuffer);
    }

    // Skriv ut hela tabellen
    printTable(&ht);
}