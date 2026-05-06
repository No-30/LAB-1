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
    initRTC();
    srand(rtcTime);

    BSTree tree = create_empty_tree();
    int to_insert = 0;

    for (int i = 0; i < 20; i++)
    {
        to_insert = rand() % 101;
        sprintf(sprintfBuffer, "\n\rtest %d", to_insert);
        uarte_write(sprintfBuffer);
        delay(1000, 'm');
        if(!find_BST(&tree, to_insert))
        {
            sprintf(sprintfBuffer, "\n\rno dum dum");
            uarte_write(sprintfBuffer);
            insert_sorted_BST(&tree, to_insert);
        }
        else
            uarte_write("\n\r you dum dum \n\r");
    }

    sprintf(sprintfBuffer, "\n\rpreorder");
    uarte_write(sprintfBuffer);
    print_preorder(tree);

    sprintf(sprintfBuffer, "\n\rinorder");
    uarte_write(sprintfBuffer);
    print_inorder(tree);

    sprintf(sprintfBuffer, "\n\rpostorder");
    uarte_write(sprintfBuffer);
    print_postorder(tree);
    
}