/*
 * LinkedList.c
 *
 *  Created on: Aug 8, 2018
 *      Author: zawawy
 */
#include <stdlib.h>
#include "LinkedList.h"

int Tarrival =0; 
Node * clockPointer;

void intializeList(LinkedList * list)
{
    list->head = list->tail = NULL ;
    list->numOfNodes =0;
}

void addNode(LinkedList * list , Object value)
{
    
	Node * node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    node->pinCount = 1;
    node->arrivalTime = ++Tarrival;
    list->numOfNodes++;
    if(list->head==NULL)
        list->head = list->tail = node ;
    else {
        list->tail->next = node ;
        list->tail = node ;
    }
}

void addNode_queue(LinkedList * list, Object value)
{
    Node * temp = list->head;
    list->head = list->head->next;
    free(temp);
    list->numOfNodes--;
    addNode(&list,value);
}

int searchForNode(LinkedList * List ,Object value)
{
    Node * temp = List->head;
    while(temp != NULL)
    {
        if(temp->value == value) 
        {
            temp->pinCount++;
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void findandReplaceLRU(LinkedList * List, Object value)
{
    Node * temp = List->head;
    Node * LRU = List->head;
    while(temp != NULL)
    {
        if(temp->arrivalTime < LRU->arrivalTime && temp->pinCount < LRU->pinCount)
        {
            LRU = temp;
        }
        temp = temp->next;
    }
    LRU->value =value;
    LRU->arrivalTime= ++Tarrival;
    LRU->pinCount = 1;
}

void MoveAndReplaceClock(LinkedList * List, Object value)
{

}