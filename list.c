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
*   Nom : GetNewNode
*   Usage : Créer un nouveau noeud
*   Parametères :
* 		paramètre 1 : Participant à ajouter
*   Retour : noeud
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
*   Nom : InsertAtHead
*   Usage : Insérer un noeud en tête d'un liste doublement chaînée
*   Parametères :
* 		paramètre 1 : Participant à ajouter
*   Retour : noeud
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

