#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include "list.h"
#include "file.h"
#include "manage.h"
#include "print.h"
#include "navigation.h"


/*
*   Name : GetNewNode
*   Usage : Creates a new Node
*   Parameters : Structure PARTICIPANT
*   Return : returns pointer of the new node
*/
struct Node* GetNewNode(PARTICIPANT Participant) {

	struct Node* newNode
		= (struct Node*)malloc(sizeof(struct Node));

	newNode->Participant = Participant;

	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}


/*
*   Name : InsertAtHead
*   Usage : Inserts a Node at head of doubly linked list
*   Parameters : Structure PARTICIPANT
*   Return : void
*/
void InsertAtHead(PARTICIPANT Participant) {
	struct Node* newNode = GetNewNode(Participant);
	if(head == NULL) {
		head = newNode;
		return;
	}
	head->prev = newNode;
	newNode->next = head;
	head = newNode;
}

