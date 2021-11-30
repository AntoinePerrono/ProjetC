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

void headerTabPrint(void){
    printf("\n");
	printf("Dossard    Nom                 Prenom               Genre Naissance Temps\n");
	printf("--------+---------------------+---------------------+---+----------+------------\n");
}

/*
*   Name : listPrint
*   Usage : Print the list of participants
*   Parameters : none
*   Return : void
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
*   Name : printParticipant
*   Usage : Print a participant
*   Parameters : structure PARTICPANT -> all stuctures are printed
*   Return : void
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


void agePartPrint(int min, int max, struct Node *head) {

	struct Node* temp = head;
	printf("TRI PAR TRANCHE D'AGE\nMIN : %d, MAX : %d\n", min, max);
	headerTabPrint();
	linePrint();
	while(temp != NULL) {

        if (age(temp->Participant.Birth) > min
            && age(temp->Participant.Birth) < max) {
                participantPrint(temp->Participant);
        }

        /*
		if ( ((2021 - temp->Participant.Birth.BirthYear) >= min)
            && ((2021 - temp->Participant.Birth.BirthYear) <= max)) {
                participantPrint(temp->Participant);
        }
        */
		temp = temp->next;
	}
	linePrint();
}
/*
*   Name : printLogo
*   Usage : Print best header logo
*   Parameters : none
*   Return : void
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
*   Name : printLine
*   Usage : Print a super line
*   Parameters : none
*   Return : void
*/
void linePrint(void){
    printf("\n--------------------------------------------------------------------------------\n");
};

/*
*   Name : clearCmd
*   Usage : Clean the cmd
*   Parameters : none
*   Return : void
*/
void clearCmd(void){
    system("cls");
}
