#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include "list.h"
#include "file.h"
#include "manage.h"
#include "print.h"
#include "navigation.h"

//Global variable for random ID transmission
char idTmp[LENGTH_ID];

/*
*   GESTION DE LA DATE/HEURE
*/

DATE today(void){

    struct tm *info;
	DATE today;
	time_t now;

	time(&now);
	info = localtime(&now);

	today.day = info->tm_mday;
	today.month = 1 + (info->tm_mon);
	today.year = 1900 + info->tm_year;

	return today;
}

int age(BIRTHDATE birth) {
    int tmp;
    tmp = today().year - birth.BirthYear;
    if ( (birth.BirthMonth*31 + birth.BirthDay) > (today().month*31 + today().day) ) {
        tmp = tmp - 1;
    }
    return tmp;
}

/*
*   Name : birthVerif
*   Usage : Format verification of birthdate
*   Parameters : structure PARTICIPANT
*   Return : value 1 : ok; value 0 : not ok
*/
int birthVerif(PARTICIPANT Participant) { //Retourne 1 si date correct sinon 0

    if (Participant.Birth.BirthYear > 1950 && Participant.Birth.BirthYear <= 2021) {
        if (Participant.Birth.BirthMonth > 0 && Participant.Birth.BirthMonth <= 12) {
            if (Participant.Birth.BirthDay > 0 && Participant.Birth.BirthDay <= 31) {
                    return 1;
            }
        }
    }
    return 0;
}

/*
*   Name : genderVerif
*   Usage : Format verification of gender
*   Parameters : structure PARTICIPANT -> Gender is necessary
*   Return : value 1 : ok; value 0 : not ok
*/
int genderVerif(PARTICIPANT Participant) { // Si le genre est bon alors 1 sinon 0

    if (strcmp(Participant.Gender, "M") == 0 || strcmp(Participant.Gender, "F") == 0) {
        return 1;
    }
    return 0;
}

/*
*   Name : resultVerif
*   Usage : Format verification of result (time format)
*   Parameters : structure PARTICIPANT -> Result is necessary
*   Return : value 1 : ok; value 0 : not ok
*/
int resultVerif(PARTICIPANT Participant) { //retourne 1  si resultat correct sinon 0

    if (Participant.Result.hours >= 0 && Participant.Result.hours <= 60) {
        if (Participant.Result.minutes >= 0 && Participant.Result.minutes <= 60) {
            if (Participant.Result.seconds >= 0 && Participant.Result.seconds <= 60) {
                return 1;
            }
        }
    }
    return 0;
}


/*
*   Name : idVerif
*   Usage : Test if an id is available
*   Parameters : ptr of char id
*   Return : value 1 : id received is already use; value 0 : any identical id is use
*/
int idVerif(char *id){ //0 : aucun id trouvé, 1 : id déjà utilisé
    struct Node* temp = head;
    while(temp != NULL) {
		if(strcmp(temp->Participant.ID, id) == 0) {
            return 1;
		}
		temp = temp->next;
	}
	return 0;
}

void idAttribution(void) {
    time_t t;

    unsigned idrand;
    srand((unsigned) time(&t));

    idrand = rand();
    sprintf(idTmp, "%d", idrand);
}

/*
*   Name : modifyParticipant
*   Usage : Modification of a participant. With ID parameter, the function search
*           the participant and suggest to modify a field
*   Parameters : char *ID
*   Return : value 1 : id received is already use; value 0 : any identical id is use
*/
void modifyParticipant(char *id, struct Node* head){
    struct Node* tmp = head;
    PARTICIPANT partTmp;
    strcpy(partTmp.ID, id);
    printf("Modifier l'utilisateur avec ID : %s\n", partTmp.ID);


    int found = 0;
    int choice = 0;

    while(tmp != NULL){
        if (strcmp(tmp->Participant.ID, id) == 0) {
            found = 1;
            partTmp = tmp->Participant;
        }
        tmp = tmp->next;
    }

	if (found == 0) {
        printf("ID du participant non trouve\n");
	} else {
	    printf("Voici l'utilisateur que vous allez modifier : \n");
	    participantPrint(partTmp);
	    printf("\n");

	    printf("Que souhaitez-vous modifier ?\n1. Nom\t2. Prenom\t3. Genre \n4. Date de naissance\t 5.temps\n Choix :");
	    scanf("%d", &choice);

	    switch (choice) {
            case 1: //Nom
                printf("%s -> ", partTmp.Lastname);
                scanf("%s", partTmp.Lastname);
                break;
            case 2: //Prenom
                printf("%s -> ", partTmp.Firstname);
                scanf("%s", partTmp.Firstname);
                break;
            case 3: //Genre
                printf("%s -> ", partTmp.Gender);
                printf("Genre (M ou F) :");
                scanf("%1s", partTmp.Gender);
                if (genderVerif(partTmp) == 0) {
                    while(genderVerif(partTmp) != 1) {
                        printf("Genre non reconnu\n Entrer entrer un genre (M ou F): ");
                        scanf("%1s", partTmp.Gender);
                    }
                }
                break;
            case 4: //Date Naissance
                printf("%02d/%02d/%02d -> ", partTmp.Birth.BirthDay,
                                             partTmp.Birth.BirthMonth,
                                             partTmp.Birth.BirthYear);
                scanf("%d/%d/%d", &partTmp.Birth.BirthDay, &partTmp.Birth.BirthMonth, &partTmp.Birth.BirthYear);

                while (birthVerif(partTmp) == 0) {
                    printf("Date de naissance non conforme !\n");
                    printf("%02d/%02d/%02d -> ", partTmp.Birth.BirthDay,
                                             partTmp.Birth.BirthMonth,
                                             partTmp.Birth.BirthYear);
                    scanf("%d/%d/%d", &partTmp.Birth.BirthDay, &partTmp.Birth.BirthMonth, &partTmp.Birth.BirthYear);
                }
                break;
            case 5: //Date Naissance
                printf("%02d:%02d:%02d -> ", partTmp.Result.hours,
                                              partTmp.Result.minutes,
                                              partTmp.Result.seconds);
                scanf("%2d:%2d:%2d", &partTmp.Result.hours, &partTmp.Result.minutes, &partTmp.Result.seconds);

                while (resultVerif(partTmp) == 0) {
                    printf("Le temps n'est pas conforme\n");
                    printf("%02d:%02d:%02d -> ", partTmp.Result.hours,
                                              partTmp.Result.minutes,
                                              partTmp.Result.seconds);
                    scanf("%2d:%2d:%2d", &partTmp.Result.hours, &partTmp.Result.minutes, &partTmp.Result.seconds);
                }

                break;
            default:
                break;

	    }
	    printf("Apercu de la modification : \n");
        participantPrint(partTmp);

        while(head != NULL){

            if ( strcmp(head->Participant.ID, partTmp.ID) == 0 ){
                head->Participant = partTmp;
            }

            head = head->next;
        }
        printf("Modification ok\n");
	}

}

/*
*   Name : searchParticipant
*   Usage : Search of participant with his ID or Lastname : print of the participant if found
*   Parameters : int searchType : 1 ID, 2. Lastname
*                structure Participant -> ID or Lastname is necessary
*   Return : void
*/
int searchParticipant(int searchType, char *field){
    struct Node* temp = head;
    PARTICIPANT Target;
    int numParticipant = 0;

    switch(searchType){
        case 1:
            strcpy(Target.ID, field);
            printf("Recherche par ID = %s\n", Target.ID);
            while(temp != NULL) {
                if(strcmp(temp->Participant.ID, Target.ID) == 0) {
                    participantPrint(temp->Participant);
                    return numParticipant;
                }
                numParticipant += 1;
                temp = temp->next;
            }
            break;
        case 2:
            strcpy(Target.Lastname, field);
            printf("Recherche par nom : %s\n", Target.Lastname);
            while(temp != NULL) {
                if(strcmp(temp->Participant.Lastname, Target.Lastname) == 0) {
                    participantPrint(temp->Participant);
                    return numParticipant;
                }
                numParticipant += 1;
                temp = temp->next;
            }
            break;
        default:
            break;
    }

    return numParticipant;
}

/*
*   Name : addParticipant
*   Usage : Create a new participant
*   Parameters : non
*   Return : void
*/
void addParticipant(){
    PARTICIPANT newParticipant;
    clearCmd();
    linePrint();
    printf("\n ENREGISTREMENT D'UN NOUVEL UTILISATEUR");
    linePrint();

    idAttribution();
    strcpy(newParticipant.ID, idTmp);
    while(idVerif(newParticipant.ID) != 0) {
        idAttribution();
    }
    printf("ID OK ! ID ENREGISTRE : %s\n", newParticipant.ID);

    printf("Nom :"); scanf("%s", newParticipant.Lastname);

    printf("Prenom :"); scanf("%s", newParticipant.Firstname);

    printf("Genre (M ou F) :"); scanf("%1s", newParticipant.Gender);
    if (genderVerif(newParticipant) == 0) {
        while(genderVerif(newParticipant) != 1) {
            printf("Genre non reconnu\n Entrer entrer un genre (M ou F): ");
            scanf("%1s", newParticipant.Gender);
        }
    }

    printf("Date de naissance (format JJ/MM/AAAA) :");
    scanf("%d/%d/%d", &newParticipant.Birth.BirthDay, &newParticipant.Birth.BirthMonth,
                      &newParticipant.Birth.BirthYear);


    while(birthVerif(newParticipant) != 1) {
             printf("Date non reconnue \n Entrer entrer une date (format JJ/MM/AAAA): ");
             scanf("%d/%d/%d", &newParticipant.Birth.BirthDay, &newParticipant.Birth.BirthMonth,
                               &newParticipant.Birth.BirthYear);
    }

    newParticipant.Result.hours = 0;
    newParticipant.Result.minutes = 0;
    newParticipant.Result.seconds = 0;

    InsertAtHead(newParticipant);
    printf("Participant ajoute !\n");

}


void deleteParticipant(char *id, struct Node *head)
  {
      struct Node *temp = head;
      int found = 0;
      PARTICIPANT tmpPart;
      strcpy(tmpPart.ID, id);

      while(temp != NULL)
      {
          if(strcmp(temp->Participant.ID, tmpPart.ID) == 0)
          {
              found = 1;
              break;
          }
          else
              temp = temp->next;
      }
      if(found == 0)
          printf("NOT FOUND Cant delete\n");
      //To delete first element
      else if (temp->prev == NULL)
      {
          head = temp->next;
          (temp->next)->prev = NULL;
          //free(temp);
          printf("Deleted\n");
      }
      //To delete last element
      else if (temp->next == NULL)
      {
          (temp->prev)->next = NULL;
          printf("Deleted\n");
          //free(temp);
      }
      //To delete any other element
      else
      {
          (temp->prev)->next = temp->next;
          (temp->next)->prev = temp->prev;
          printf("Deleted\n");
          //free(temp);
      }
  }

int resultComputed(struct Node* head){
    int number = 1;
    while(head != NULL) {
        head->Participant.Result.resultComputed =  head->Participant.Result.hours*60*60
                                                 + head->Participant.Result.minutes*60
                                                 + head->Participant.Result.seconds;

        head = head->next;
        number += 1;
    }
    return number;
}

void bubbleSort(struct Node *start)
{

    resultComputed(head);
    int swapp;
    PARTICIPANT partTmp;
    struct Node *ptr1;
    struct Node *lptr = NULL;
    if (start == NULL)
        return;
    do
    {
        swapp = 0;
        ptr1 = start;
        while (ptr1->next != lptr)
        {
            if (ptr1->Participant.Result.resultComputed > ptr1->next->Participant.Result.resultComputed)
            {
                partTmp = ptr1->Participant;
                ptr1->Participant = ptr1->next->Participant;
                ptr1->next->Participant = partTmp;
                swapp = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapp);
}


void resultEnter(struct Node* head){

    PARTICIPANT partTmp;
    partTmp.Result.hours = 0;
    partTmp.Result.minutes= 0;
    partTmp.Result.seconds = 0;

    while(head != NULL) {

        if(head->Participant.Result.resultComputed == 0){
            printf("\n%s %s %s %u \nEntrer temps (format hh:mm:ss) -> ", head->Participant.ID,
                                                                    head->Participant.Lastname,
                                                                    head->Participant.Firstname,
                                                                    head->Participant.Result.resultComputed);
            scanf("%d:%d:%d", &partTmp.Result.hours, &partTmp.Result.minutes, &partTmp.Result.seconds);
            while ( resultVerif(partTmp) == 0 ){
                printf("TEMPS ERRONEE\n Verifier le format ou les valeurs\n");
                printf("\n%s %s %s : entrer temps (format hh:mm:ss) -> ", head->Participant.ID,
                                                                    head->Participant.Lastname,
                                                                    head->Participant.Firstname);
                scanf("\n%d:%d:%d", &partTmp.Result.hours, &partTmp.Result.minutes, &partTmp.Result.seconds);
            }
        }

        head->Participant.Result = partTmp.Result;
        head = head->next;

    }

}
