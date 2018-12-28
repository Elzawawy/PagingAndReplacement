#include <stdio.h>
#include <stdlib.h>
#include "mem_manager.h"
#include "LinkedList.h"

int Global_numOfPages;
ReplacementPolicy Global_replacementPolicy;
LinkedList Global_linkedList;

void pageReplacer_init(int numOfPages, ReplacementPolicy policy)
{
    Global_numOfPages = numOfPages;
    Global_replacementPolicy = policy;
    intializeList(&Global_linkedList);
}

int requestPage(int pageReference)
{
    int Local_pageFaultIndicator=0;
    switch (Global_replacementPolicy)
    {
    case FIFO:
        if (searchForNode(&Global_linkedList, pageReference) == 1)
        {
            printf("%02d     ", pageReference);
            Node *runningPointer = Global_linkedList.head;
            while (runningPointer != NULL)
            {
                printf("%02d ", runningPointer->value);
                runningPointer = runningPointer->next;
            }
            printf("\n");
        }
        else if (Global_linkedList.numOfNodes < Global_numOfPages)
        {
            addNode(&Global_linkedList, pageReference);
            printf("%02d     ", pageReference);
            Node *runningPointer = Global_linkedList.head;
            while (runningPointer != NULL)
            {
                printf("%02d ", runningPointer->value);
                runningPointer = runningPointer->next;
            }
            printf("\n");
        }
        else
        {
            findandReplaceFIFO(&Global_linkedList, pageReference);
            printf("%02d F   ", pageReference);
            Node *runningPointer = Global_linkedList.head;
            while (runningPointer != NULL)
            {
                printf("%02d ", runningPointer->value);
                runningPointer = runningPointer->next;
            }
            printf("\n");
            Local_pageFaultIndicator=1;
        }
        break;

    case LRU:
        if (searchForNode(&Global_linkedList, pageReference) == 1)
        {
            printf("%02d     ", pageReference);
            Node *runningPointer = Global_linkedList.head;
            while (runningPointer != NULL)
            {
                printf("%02d ", runningPointer->value);
                runningPointer = runningPointer->next;
            }
            printf("\n");
        }
        else if (Global_linkedList.numOfNodes < Global_numOfPages)
        {
            addNode(&Global_linkedList, pageReference);
            printf("%02d     ", pageReference);
            Node *runningPointer = Global_linkedList.head;
            while (runningPointer != NULL)
            {
                printf("%02d ", runningPointer->value);
                runningPointer = runningPointer->next;
            }
            printf("\n");
        }

        else
        {
            findandReplaceLRU(&Global_linkedList, pageReference);
            printf("%02d F   ", pageReference);
            Node *runningPointer = Global_linkedList.head;
            while (runningPointer != NULL)
            {
                printf("%02d ", runningPointer->value);
                runningPointer = runningPointer->next;
            }
            printf("\n");
            Local_pageFaultIndicator=1;
        }
        break;

    case CLOCK:
        if (searchForNode(&Global_linkedList, pageReference) == 1)
        {
            printf("%02d     ", pageReference);
            Node *runningPointer = Global_linkedList.head;
            while (runningPointer != NULL)
            {
                printf("%02d ", runningPointer->value);
                runningPointer = runningPointer->next;
            }
            printf("\n");
        }
        else if (Global_linkedList.numOfNodes < Global_numOfPages)
        {
            addNode(&Global_linkedList, pageReference);
            printf("%02d     ", pageReference);
            Node *runningPointer = Global_linkedList.head;
            while (runningPointer != NULL)
            {
                printf("%02d ", runningPointer->value);
                runningPointer = runningPointer->next;
            }
            printf("\n");
        }
        else
        {
            MoveAndReplaceClock(&Global_linkedList, pageReference);
            printf("%02d F   ", pageReference);
            Node *runningPointer = Global_linkedList.head;
            while (runningPointer != NULL)
            {
                printf("%02d ", runningPointer->value);
                runningPointer = runningPointer->next;
            }
            printf("\n");
            Local_pageFaultIndicator=1;
        }
        break;
    }
    return Local_pageFaultIndicator;
}