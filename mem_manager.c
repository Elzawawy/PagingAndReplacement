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

void requestPage(int pageReference)
{
    switch (Global_replacementPolicy)
    {
    case FIFO:
        if(Global_linkedList.numOfNodes < Global_numOfPages)
        {
            addNode(&Global_linkedList,pageReference);
        }
        else if( searchForNode(&Global_linkedList, pageReference) == 1)
        {
            //do nothing. 
        }
        else 
        {
            addNode_queue(&Global_linkedList, pageReference);
        }
        break;

    case LRU:
        
        break;

    case CLOCK:
        break;
    }
}