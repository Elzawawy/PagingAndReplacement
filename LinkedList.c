/*
 * LinkedList.c
 *
 *  Created on: Aug 8, 2018
 *      Author: zawawy
 */
#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"

int Tarrival = 0;
Node *clockPointer;
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
    // Node * temp = clockPointer;
    // while (clockPointer != NULL)
    // {
    //     if (clockPointer->clockPin == 0)
    //         break;
    //     else
    //         clockPointer->clockPin = 0;
    //     clockPointer = clockPointer->next;
    // }

    // if (clockPointer == NULL)
    // {
    //     List->head->value = value;
    //     List->head->clockPin = 1;
    //     clockPointer = List->head->next;
    // }
    // else
    // {
    //     clockPointer->value = value;
    //     clockPointer->clockPin = 1;
    //     clockPointer = clockPointer->next;
    //     if (clockPointer == NULL)
    //         clockPointer = List->head;
    // }

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