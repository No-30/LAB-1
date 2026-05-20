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
#include <list_sort.h>
#include <array_sort.h>

#define ARRAY_SIZE1 7
#define ARRAY_SIZE2 15
#define ARRAY_SIZE3 31
#define ARRAY_SIZE4 63
#define KÖR 0

int main(void)
{ 
    initAll();
    int pretime, posttime;

    List list1 = create_empty_list();
    List list2 = create_empty_list();
    List list3 = create_empty_list();
    List list4 = create_empty_list();

    int data;
    for (int i = 0; i < ARRAY_SIZE1; i++)
    {
        data = rand() % 1001;
        add_last(&list1, data);
    }

    for (int i = 0; i < ARRAY_SIZE2; i++)
    {
        data = rand() % 1001;
        add_last(&list2, data);
    }

    for (int i = 0; i < ARRAY_SIZE3; i++)
    {
        data = rand() % 1001;
        add_last(&list3, data);
    }

    for (int i = 0; i < ARRAY_SIZE4; i++)
    {
        data = rand() % 1001;
        add_last(&list4, data);
    }

    sprintf(sprintfBuffer, "\r\n\nBubble Sort Results:\r\n");
    uarte_write(sprintfBuffer);
    print_list(list1);

    nrf_systick_val_clear();
    pretime = nrf_systick_val_get();
    list1 = bubble_sort_list(list1);
    posttime = nrf_systick_val_get();
    posttime = pretime - posttime;
    if(is_sorted_list(list1))
        sprintf(sprintfBuffer, "\r\nBubble sort 1 is sorted\r\n");
    else
        sprintf(sprintfBuffer, "\r\nBubble sort 1 is not sorted\r\n");
    uarte_write(sprintfBuffer);
    sprintf(sprintfBuffer, "Bubble sort 1 took %d ticks\r\n", posttime);
    uarte_write(sprintfBuffer);

    print_list(list1);

    if(KÖR)
    {
    nrf_systick_val_clear();
    pretime = nrf_systick_val_get();
    list2 = bubble_sort_list(list2);
    posttime = nrf_systick_val_get();
    posttime = pretime - posttime;
    if(is_sorted_list(list2))
        sprintf(sprintfBuffer, "\r\nBubble sort 2 is sorted\r\n");
    else
        sprintf(sprintfBuffer, "\r\nBubble sort 2 is not sorted\r\n");
    uarte_write(sprintfBuffer);
    sprintf(sprintfBuffer, "Bubble sort 2 took %d ticks\r\n", posttime);
    uarte_write(sprintfBuffer);

    nrf_systick_val_clear();
    pretime = nrf_systick_val_get();
    list3 = bubble_sort_list(list3);
    posttime = nrf_systick_val_get();
    posttime = pretime - posttime;
    if(is_sorted_list(list3))
        sprintf(sprintfBuffer, "\r\nBubble sort 3 is sorted\r\n");
    else
        sprintf(sprintfBuffer, "\r\nBubble sort 3 is not sorted\r\n");
    uarte_write(sprintfBuffer);
    sprintf(sprintfBuffer, "Bubble sort 3 took %d ticks\r\n", posttime);
    uarte_write(sprintfBuffer);

    nrf_systick_val_clear();
    pretime = nrf_systick_val_get();
    list4 = bubble_sort_list(list4);
    posttime = nrf_systick_val_get();
    posttime = pretime - posttime;
    if(is_sorted_list(list4))
        sprintf(sprintfBuffer, "\r\nBubble sort 4 is sorted\r\n");
    else
        sprintf(sprintfBuffer, "\r\nBubble sort 4 is not sorted\r\n");
    uarte_write(sprintfBuffer);
    sprintf(sprintfBuffer, "Bubble sort 4 took %d ticks\r\n", posttime);
    uarte_write(sprintfBuffer);
    }

    sprintf(sprintfBuffer, "\r\n\nMerge Sort Results:\r\n");
    uarte_write(sprintfBuffer);
    

    int array1[ARRAY_SIZE1], array2[ARRAY_SIZE2], array3[ARRAY_SIZE3], array4[ARRAY_SIZE4];

    //merge sort
    for (int i = 0; i < ARRAY_SIZE1; i++)
        array1[i] = rand() % 1001;
    for (int i = 0; i < ARRAY_SIZE2; i++)
        array2[i] = rand() % 1001;
    for (int i = 0; i < ARRAY_SIZE3; i++)
        array3[i] = rand() % 1001;
    for (int i = 0; i < ARRAY_SIZE4; i++)
        array4[i] = rand() % 1001;

    for (int i = 0; i < ARRAY_SIZE1; i++)
    {
        sprintf(sprintfBuffer, "\r\n%d", array1[i]);
        uarte_write(sprintfBuffer);
    }

    nrf_systick_val_clear();
    pretime = nrf_systick_val_get();
    merge_sort(array1, ARRAY_SIZE1);
    posttime = nrf_systick_val_get();
    posttime = pretime - posttime;
    if(is_sorted(array1, ARRAY_SIZE1))
        sprintf(sprintfBuffer, "\r\nMerge sort 1 is sorted\r\n");
    else
        sprintf(sprintfBuffer, "\r\nMerge sort 1 is not sorted\r\n");
    uarte_write(sprintfBuffer);
    sprintf(sprintfBuffer, "Merge sort 1 took %d ticks\r\n", posttime);
    uarte_write(sprintfBuffer);

    for (int i = 0; i < ARRAY_SIZE1; i++)
    {
        sprintf(sprintfBuffer, "\r\n%d", array1[i]);
        uarte_write(sprintfBuffer);
    }

    if(KÖR)
    {
    nrf_systick_val_clear();
    pretime = nrf_systick_val_get();
    merge_sort(array2, ARRAY_SIZE2);
    posttime = nrf_systick_val_get();
    posttime = pretime - posttime;
    if(is_sorted(array2, ARRAY_SIZE2))
        sprintf(sprintfBuffer, "\r\nMerge sort 2 is sorted\r\n");
    else
        sprintf(sprintfBuffer, "\r\nMerge sort 2 is not sorted\r\n");
    uarte_write(sprintfBuffer);
    sprintf(sprintfBuffer, "Merge sort 2 took %d ticks\r\n", posttime);
    uarte_write(sprintfBuffer);

    nrf_systick_val_clear();
    pretime = nrf_systick_val_get();
    merge_sort(array3, ARRAY_SIZE3);
    posttime = nrf_systick_val_get();
    posttime = pretime - posttime;
    if(is_sorted(array3, ARRAY_SIZE3))
        sprintf(sprintfBuffer, "\r\nMerge sort 3 is sorted\r\n");
    else
        sprintf(sprintfBuffer, "\r\nMerge sort 3 is not sorted\r\n");
    uarte_write(sprintfBuffer);
    sprintf(sprintfBuffer, "Merge sort 3 took %d ticks\r\n", posttime);
    uarte_write(sprintfBuffer);

    nrf_systick_val_clear();
    pretime = nrf_systick_val_get();
    merge_sort(array4, ARRAY_SIZE4);
    posttime = nrf_systick_val_get();
    posttime = pretime - posttime;
    if(is_sorted(array4, ARRAY_SIZE4))
        sprintf(sprintfBuffer, "\r\nMerge sort 4 is sorted\r\n");
    else
        sprintf(sprintfBuffer, "\r\nMerge sort 4 is not sorted\r\n");
    uarte_write(sprintfBuffer);
    sprintf(sprintfBuffer, "Merge sort 4 took %d ticks\r\n", posttime);
    uarte_write(sprintfBuffer);
    }
    //quick sort

    sprintf(sprintfBuffer, "\r\n\nQuick Sort Results:\r\n");
    uarte_write(sprintfBuffer);

    for (int i = 0; i < ARRAY_SIZE1; i++)
        array1[i] = rand() % 1001;
    for (int i = 0; i < ARRAY_SIZE2; i++)
        array2[i] = rand() % 1001;
    for (int i = 0; i < ARRAY_SIZE3; i++)
        array3[i] = rand() % 1001;
    for (int i = 0; i < ARRAY_SIZE4; i++)
        array4[i] = rand() % 1001;

    for (int i = 0; i < ARRAY_SIZE1; i++)
    {
        sprintf(sprintfBuffer, "\r\n%d", array1[i]);
        uarte_write(sprintfBuffer);
    }

    
    nrf_systick_val_clear();
    pretime = nrf_systick_val_get();
    quick_sort(array1, ARRAY_SIZE1);
    posttime = nrf_systick_val_get();
    posttime = pretime - posttime;
    if(is_sorted(array1, ARRAY_SIZE1))
        sprintf(sprintfBuffer, "\r\nQuick sort 1 is sorted\r\n");
    else
        sprintf(sprintfBuffer, "\r\nQuick sort 1 is not sorted\r\n");
    uarte_write(sprintfBuffer);
    sprintf(sprintfBuffer, "Quick sort 1 took %d ticks\r\n", posttime);
    uarte_write(sprintfBuffer);

    for (int i = 0; i < ARRAY_SIZE1; i++)
    {
        sprintf(sprintfBuffer, "\r\n%d", array1[i]);
        uarte_write(sprintfBuffer);
    }

    if(KÖR)
    {
    nrf_systick_val_clear();
    pretime = nrf_systick_val_get();
    quick_sort(array2, ARRAY_SIZE2);
    posttime = nrf_systick_val_get();
    posttime = pretime - posttime;
    if(is_sorted(array2, ARRAY_SIZE2))
        sprintf(sprintfBuffer, "\r\nQuick sort 2 is sorted\r\n");
    else
        sprintf(sprintfBuffer, "\r\nQuick sort 2 is not sorted\r\n");
    uarte_write(sprintfBuffer);
    sprintf(sprintfBuffer, "Quick sort 2 took %d ticks\r\n", posttime);
    uarte_write(sprintfBuffer);

    nrf_systick_val_clear();
    pretime = nrf_systick_val_get();
    quick_sort(array3, ARRAY_SIZE3);
    posttime = nrf_systick_val_get();
    posttime = pretime - posttime;
    if(is_sorted(array3, ARRAY_SIZE3))
        sprintf(sprintfBuffer, "\r\nQuick sort 3 is sorted\r\n");
    else
        sprintf(sprintfBuffer, "\r\nQuick sort 3 is not sorted\r\n");
    uarte_write(sprintfBuffer);
    sprintf(sprintfBuffer, "Quick sort 3 took %d ticks\r\n", posttime);
    uarte_write(sprintfBuffer);

    nrf_systick_val_clear();
    pretime = nrf_systick_val_get();
    quick_sort(array4, ARRAY_SIZE4);
    posttime = nrf_systick_val_get();
    posttime = pretime - posttime;
    if(is_sorted(array4, ARRAY_SIZE4))
        sprintf(sprintfBuffer, "\r\nQuick sort 4 is sorted\r\n");
    else
        sprintf(sprintfBuffer, "\r\nQuick sort 4 is not sorted\r\n");
    uarte_write(sprintfBuffer);
    sprintf(sprintfBuffer, "Quick sort 4 took %d ticks\r\n", posttime);
    uarte_write(sprintfBuffer);
    }
}