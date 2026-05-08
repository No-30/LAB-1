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

#define TREESIZE 127

int main(void)
{ 
    initAll();

    BSTree tree = create_empty_tree();
    int to_insert = 0;

    for (int i = 0; i < TREESIZE; i++)
    {
        to_insert = i;
        if(find_BST(tree, to_insert) == 0)
        {
            insert_sorted_BST(&tree, to_insert);
        }
        else
        {
            uarte_write("\n\r did not work to insert \n\r");
        }
    }
    nrf_systick_val_clear();

    int pretime = nrf_systick_val_get();
    find_BST(tree, TREESIZE);
    //efter
    int posttime = nrf_systick_val_get();

    posttime = pretime - posttime;

    sprintf(sprintfBuffer, "\n\rTime to find element in tree of size %d: %d ticks", TREESIZE, posttime);
    uarte_write(sprintfBuffer);
}