#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<time.h>


#include "list.h"
#include "file.h"
#include "manage.h"
#include "print.h"
#include "navigation.h"


/*
*   Nom : headerTabPrint
*   Usage : En-tête du tableau des participants
*   Parametères : void
*   Retour : void
*/
void headerTabPrint(void){
    printf("\n");
	printf("Dossard    Nom                 Prenom               Genre Naissance Temps\n");
	printf("--------+---------------------+---------------------+---+----------+------------\n");
}

/*
*   Nom : listPrint
*   Usage : Ecriture de la liste dans un fichier txt
*   Parametères :
* 		paramètre 1 : liste à imprimer
*   Retour : void
*/
void listPrint(struct Node *head) {
	struct Node* temp = head;
	headerTabPrint();
	while(temp != NULL) {
		participantPrint(temp->Participant);
		temp = temp->next;
	}
	linePrint();
}

/*
*   Nom : printParticipant
*   Usage : Affichage d'un participant
*   Parametères : participant
*   Retour : void
*/
void participantPrint(PARTICIPANT Participant) {
    printf("%8s %20s %20s %5s %02d/%02d/%02d\t%02dh%02dm%02ds\n",
                Participant.ID,
                Participant.Lastname,
                Participant.Firstname,
                Participant.Gender,
                Participant.Birth.BirthDay,Participant.Birth.BirthMonth,Participant.Birth.BirthYear,
                Participant.Result.hours,Participant.Result.minutes,Participant.Result.seconds
                );
    printf("\n");
}

/*
*   Nom : agePartPrint
*   Usage : Affichage des participant dans une tranche d'âge choisie
*   Parametères : 
* 		paramètre 1 : entier âge min
* 		paramètre 2 : entier âge max
* 		paramètre 3 : liste dans laquelle faire la recherche 
*   Retour : void
*/
void agePartPrint(int min, int max, struct Node *head) {
	
	int ageMin, ageMax;
	ageMin = min;
	ageMax = max;
	
	if (min > max) {
		printf("ERREUR ! min : %d > max : %d, serieusement ?\n", min, max);
		ageMin = max;
		ageMax = min;
		prrintf("Je vous en veux pas, j'ai inverse les valeurs\n");
	}

	struct Node* temp = head;
	printf("TRI PAR TRANCHE D'AGE\nMIN : %d, MAX : %d\n", min, max);
	headerTabPrint();
	linePrint();
	while(temp != NULL) {

		if (age(temp->Participant.Birth) > ageMin
			&& age(temp->Participant.Birth) < ageMax) {
				participantPrint(temp->Participant);
			}

			temp = temp->next;
	}
	linePrint();
		
	
}

/*
*   Nom : printLogo
*   Usage : Affichage du logo
*   Parametères : void
*   Retour : void
*/

void logoPrint(void){
    printf("  ______    ____\n");
    printf(" %c      %c  |  o |\n",47, 92);
    printf("|        |%c ___%c%c     GESTIONNAIRE DES PARTICIPANTS DU MARATHON\n", 47,92,47);
    printf("|_________/\n");
    printf("%c_%c_%c %c_%c_%c\n",47,47,47,47,47,47);
    printf("\n");
}

/*
*   Nom : linePrint
*   Usage : Affichage d'une ligne
*   Parametères : void
*   Retour : void
*/
void linePrint(void){
    printf("\n--------------------------------------------------------------------------------\n");
};

/*
*   Nom : clearCmd
*   Usage : Nettoyage du terminal
*   Parametères : void
*   Retour : void
*/
void clearCmd(void){
    system("cls");
}
