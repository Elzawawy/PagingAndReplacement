/*
 * LinkedList.h
 *
 *  Created on: Aug 8, 2018
 *      Author: zawawy
 */
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
//Define NULL
#define NULL   ((void *) 0)
//Define Object for configurability.
typedef int Object;

//Define Node for the list.
typedef struct Node {
    Object value;
    struct Node* next;
	int pinCount;
	int arrivalTime;
}Node;

//Define List Structure itself.
typedef struct LinkedList {
    Node* head;
    Node* tail;
    int numOfNodes;
}LinkedList;

void intializeList(LinkedList * list);

void addNode(LinkedList * list , Object value);

int searchForNode(LinkedList * List ,Object value);

void addNode_queue(LinkedList * list, Object value);

void findandReplaceLRU(LinkedList * List, Object value)
#endif /* LINKEDLIST_H_ */
