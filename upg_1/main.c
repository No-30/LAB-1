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

    BSTree tree = create_empty_tree();
    int to_insert = 0;

    for (int i = 0; i < 5; i++)
    {
        to_insert = rand() % 101;
        //sprintf(sprintfBuffer, "\n\rtest %d", to_insert);
        //uarte_write(sprintfBuffer);
        if(find_BST(tree, to_insert) == 0)
        {
            //sprintf(sprintfBuffer, "\n\rno dum dum");
            //uarte_write(sprintfBuffer);
            insert_sorted_BST(&tree, to_insert);
        }
        else
        {
            //uarte_write("\n\r you dum dum \n\r");
        }
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
    
    sprintf(sprintfBuffer, "\n\rnumber of nodes: %d", number_of_nodes_BST(tree));
    uarte_write(sprintfBuffer);

    sprintf(sprintfBuffer, "\n\rdepth: %d", depth(tree));
    uarte_write(sprintfBuffer);

    sprintf(sprintfBuffer, "\n\rmin depth: %d", min_depth(tree));
    uarte_write(sprintfBuffer);

    balance_tree(&tree);

    sprintf(sprintfBuffer, "\n\rbalanced tree:");
    uarte_write(sprintfBuffer);

    sprintf(sprintfBuffer, "\n\rpreorder");
    uarte_write(sprintfBuffer);
    print_preorder(tree);

    sprintf(sprintfBuffer, "\n\rinorder");
    uarte_write(sprintfBuffer);
    print_inorder(tree);

    sprintf(sprintfBuffer, "\n\rpostorder");
    uarte_write(sprintfBuffer);
    print_postorder(tree);

    sprintf(sprintfBuffer, "\n\rdepth: %d", depth(tree));
    uarte_write(sprintfBuffer);

    sprintf(sprintfBuffer, "\n\rmin depth: %d", min_depth(tree));
    uarte_write(sprintfBuffer);

    free_tree(&tree);
    sprintf(sprintfBuffer, "\n\rTree freed");
    uarte_write(sprintfBuffer);
}