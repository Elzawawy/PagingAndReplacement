#include <stdio.h>
#include "mem_manager.h"
#include "LinkedList.h"

int stringCompare( char *s1, char *s2 );

void main(void)
{
    int numOfPages;
    int numOfPageFaults=0;
    char policy[5];
    ReplacementPolicy repPolicy;
    int pageRef = 0;
    Node * runningPointer;
    LinkedList requestsList;
    intializeList(&requestsList);

    scanf("%d",&numOfPages);
    scanf("%s",policy);
    if(stringCompare(policy,"FIFO") == 0)
        repPolicy = FIFO;
    else if(stringCompare(policy,"LRU") == 0)
        repPolicy = LRU;
    else if (stringCompare(policy,"CLOCK") == 0)
        repPolicy = CLOCK;
    else 
        return;

    pageReplacer_init(numOfPages,repPolicy);
    while(1)
    {
        scanf("%d",&pageRef);
        if(pageRef == -1)
            break;
        addNode(&requestsList, pageRef);
    }
    runningPointer = requestsList.head;
    printf("Replacement Policy = %s\n",policy);
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");
    while(runningPointer != NULL)
    {
        numOfPageFaults += requestPage(runningPointer->value);
        runningPointer = runningPointer->next;
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d",numOfPageFaults);

}

int stringCompare( char *s1, char *s2 )
{
    unsigned char *p1 = ( unsigned char * )s1;
    unsigned char *p2 = ( unsigned char * )s2;

    while ( *p1 && *p1 == *p2 ) ++p1, ++p2;

    return ( *p1 > *p2 ) - ( *p2  > *p1 );
}