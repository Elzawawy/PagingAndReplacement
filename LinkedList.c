/*
 * LinkedList.c
 *
 *  Created on: Aug 8, 2018
 *      Author: zawawy
 */
#include <stdlib.h>
#include "LinkedList.h"

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
        if(temp->value == value) return 1;
    return 0;
}