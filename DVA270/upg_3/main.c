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

#define NUMBERS 10

void merge(int nums[], int firstIndex, int midIndex, int lastIndex)
{
    int leftSize = midIndex - firstIndex + 1;
    int rightSize = lastIndex - midIndex;

    int leftNums[leftSize];
    int rightNums[rightSize];

    for(int i = 0; i < leftSize; i++) //Börjar från början och lägg till t.o.m mitten
    {
        leftNums[i] = nums[firstIndex + i];
    }

    for(int i = 0; i < rightSize; i++) //Börjar från mitten, alltså en större än största till
    {
        rightNums[i] = nums[midIndex + 1 + i];
    }

    int i = 0;
    int j = 0;
    int indexTracker = firstIndex;

    while(i < leftSize && j < rightSize) //Sortera arrayen genom att lägga in den mindre från delarrayerna
    {
        if(leftNums[i] <= rightNums[j]) //Vänster är större
        {
            nums[indexTracker] = leftNums[i];
            i++;
        }
        else //Höger är större
        {
            nums[indexTracker] = rightNums[j];
            j++;
        }

        indexTracker++;
    }

    while(i < leftSize) //Om hela höger är tom kopiera in resten av vänster (detta funkar då hela delarrayen redan är sorterad pga rekursion)
    {
        nums[indexTracker] = leftNums[i];
        i++;
        indexTracker++;
    }

    while(j < rightSize) //Om hela vänster är tom kopiera in resten av höger
    {
        nums[indexTracker] = rightNums[j];
        j++;
        indexTracker++;
    }
}

void mergeSort(int nums[], int firstIndex, int lastIndex)
{
    if(firstIndex >= lastIndex)
    {
        return;
    }

    int midIndex = (firstIndex + lastIndex) / 2;

    mergeSort(nums, firstIndex, midIndex); //LEFT
    mergeSort(nums, midIndex + 1, lastIndex); //RIGHT
    
    merge(nums, firstIndex, midIndex, lastIndex);
}

int main(void)
{ 
    initAll();

    int nums[NUMBERS];

    for(int i = 0; i < NUMBERS; i++)
    {
        nums[i] = rand() % 100 + 1;

        sprintf(sprintfBuffer, "\n\r%d", nums[i]);
        uarte_write(sprintfBuffer);
    }

    int firstIndex = 0;
    int lastIndex = NUMBERS - 1;

    mergeSort(nums, firstIndex, lastIndex);

    sprintf(sprintfBuffer, "\n\r\n\rArray sorted!:)\n\r");
    uarte_write(sprintfBuffer);

    for(int i = 0; i < NUMBERS; i++)
    {
        sprintf(sprintfBuffer, "\n\r%d", nums[i]);
        uarte_write(sprintfBuffer);
    }
}