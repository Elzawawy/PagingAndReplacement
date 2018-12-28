#include <stdio.h>
#include <stdlib.h>

/*********************** Datatype Definitions*****************/
//Define Object for configurability.
typedef int Object;

//Define Node for the list.
typedef struct Node {
    Object value;
    struct Node* next;
	int arrivalTime;
	int clockPin;
}Node;

//Define List Structure itself.
typedef struct LinkedList {
    Node* head;
    Node* tail;
    int numOfNodes;
}LinkedList;

typedef enum ReplacementPolicy
{
    FIFO=0,
    LRU,
    CLOCK
}ReplacementPolicy;

/***********************Fucntions Declaration****************************/

void pageReplacer_init(int numOfPages, ReplacementPolicy policy);
int requestPage(int pageReference);
void intializeList(LinkedList * list);

void addNode(LinkedList * list , Object value);

int searchForNode(LinkedList * List ,Object value);

void findandReplaceFIFO(LinkedList * list, Object value);

void findandReplaceLRU(LinkedList * List, Object value);

void MoveAndReplaceClock(LinkedList * List, Object value);

int stringCompare( char *s1, const char *s2 );

/******************* Varaibles *************************************/
int Tarrival = 0;
Node *clockPointer;
int Global_numOfPages;
ReplacementPolicy Global_replacementPolicy;
LinkedList Global_linkedList;

/************************Code ************************************/

int main(void)
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
        return 0;

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
    printf("Number of page faults = %d\n",numOfPageFaults);

return 0;

}

int stringCompare( char *s1, const char *s2 )
{
    unsigned char *p1 = ( unsigned char * )s1;
    unsigned char *p2 = ( unsigned char * )s2;

    while ( *p1 && *p1 == *p2 ) ++p1, ++p2;

    return ( *p1 > *p2 ) - ( *p2  > *p1 );
}


void intializeList(LinkedList *list)
{
    list->head = list->tail = clockPointer = NULL;
    list->numOfNodes = 0;
}

void addNode(LinkedList *list, Object value)
{

    Node *node = (Node *)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    node->arrivalTime = ++Tarrival;
    node->clockPin = 1;
    list->numOfNodes++;
    if (list->head == NULL)
    {
        list->head = list->tail = node;
        clockPointer = list->head;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
        clockPointer = node->next;
        if(clockPointer == NULL)
            clockPointer =list->head;      
    }
}

void findandReplaceFIFO(LinkedList *list, Object value)
{
    static Node *node = NULL;
    if (node == NULL)
        node = list->head;
    else
    {
        if (node == list->tail)
            node = list->head;
        else
            node = node->next;
    }
    node->value = value;
}

int searchForNode(LinkedList *List, Object value)
{
    Node *temp = List->head;
    while (temp != NULL)
    {
        if (temp->value == value)
        {
            temp->arrivalTime = ++Tarrival;
            temp->clockPin = 1;
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void findandReplaceLRU(LinkedList *List, Object value)
{
    Node *temp = List->head->next;
    Node *LRU = List->head;
    while (temp != NULL)
    {
        if (temp->arrivalTime < LRU->arrivalTime)
        {
            LRU = temp;
        }
        temp = temp->next;
    }
    LRU->value = value;
    LRU->arrivalTime = ++Tarrival;
}

void MoveAndReplaceClock(LinkedList *List, Object value)
{
    if (clockPointer->clockPin == 0)
    {
        clockPointer->value = value;
        clockPointer->clockPin = 1;
        clockPointer = clockPointer->next;
        if (clockPointer == NULL)
            clockPointer = List->head;
    }
    else
    {
        Node *temp = clockPointer->next;
        if (temp == NULL)
            temp = List->head;
        while (temp != clockPointer)
        {
            if(temp->clockPin == 0)
            {
                clockPointer=temp;
                break;
            }
            temp->clockPin = 0;
            temp = temp->next;
            if (temp == NULL)
                temp = List->head;
        }
        clockPointer->value = value;
        clockPointer->clockPin = 1;
        clockPointer = clockPointer->next;
        if (clockPointer == NULL)
            clockPointer = List->head;
    }
}



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
