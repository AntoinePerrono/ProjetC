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
*   Nom : birthVerif
*   Usage : Vérification de la date de naissance
*   Parametères : structure PARTICIPANT
*   Retour : valeur 1 : ok; valeur 0 : not ok
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
*   Nom : genderVerif
*   Usage : Vérification du genre
*   Parametères : structure PARTICIPANT
*   Retour : valeur 1 : ok; valeur 0 : not ok
*/
int genderVerif(PARTICIPANT Participant) { // Si le genre est bon alors 1 sinon 0

    if (strcmp(Participant.Gender, "M") == 0 || strcmp(Participant.Gender, "F") == 0) {
        return 1;
    }
    return 0;
}

/*
*   Nom : resultVerif
*   Usage : Vérification du résultat
*   Parametères : structure PARTICIPANT
*   Retour : valeur 1 : ok; valeur 0 : not ok
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
*   Nom : idVerif
*   Usage : Vérification de la présence d'un ID dans la liste doublement
* 			chainée
*   Parametères : structure PARTICIPANT
*   Retour :
* 			valeur 0 : aucun ID identique n'a été trouvé dans le liste
* 			valeur 1 : un ID identique a été trouvé dans la liste
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

/*
*   Nom : idAttribution
*   Usage : Génération d'un ID temporaire et stockage dans variable
* 			globale idTmp
*   Parametères : void
*   Retour : void
*/
void idAttribution(void) {
    time_t t;

    unsigned idrand;
    srand((unsigned) time(&t));

    idrand = rand();
    sprintf(idTmp, "%d", idrand);
}


/*
*   Nom : modifyParticipant
*   Usage : Modifier un participant
*   Parametères :
* 		paramètre 1 : char *ID (ID du participant)
* 		paramètre 2 : liste sur laquelle s'effectuera la modification
*   Retour : void
*/
void modifyParticipant(char *id, struct Node* head){
    struct Node* tmp = head;
    PARTICIPANT partTmp;
    strcpy(partTmp.ID, id);
    printf("Modifier l'utilisateur avec ID : %s\n", partTmp.ID);


    int found = 0;
    int choice = 0;

	//Recherche du participant à partir de son ID
    while(tmp != NULL){
        if (strcmp(tmp->Participant.ID, id) == 0) {
            found = 1;
            //Stockage des infos participant dans un participant temporaire
            partTmp = tmp->Participant;
        }
        tmp = tmp->next;
    }

	if (found == 0) {
        printf("ID du participant non trouve\n");
	} else {
		// Si l'ID a été trouvé
	    printf("Voici l'utilisateur que vous allez modifier : \n");
	    participantPrint(partTmp);
	    printf("\n");

		//Proposition de l'information à modifier + saisie
	    printf("Que souhaitez-vous modifier ?\n1. Nom\t2. Prenom\t3. Genre\n");
	    printf("4. Date de naissance\t 5.temps\n Choix :");
	    scanf("%d", &choice);

	    switch (choice) {
            case 1: //Nom
                printf("%s -> ", partTmp.Lastname);
                scanf("%s", partTmp.Lastname);
                break;
            case 2: //Prénom
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
                scanf("%d/%d/%d", &partTmp.Birth.BirthDay,
								  &partTmp.Birth.BirthMonth,
								  &partTmp.Birth.BirthYear);

                while (birthVerif(partTmp) == 0) {
                    printf("Date de naissance non conforme !\n");
                    printf("%02d/%02d/%02d -> ", partTmp.Birth.BirthDay,
                                             partTmp.Birth.BirthMonth,
                                             partTmp.Birth.BirthYear);
                    scanf("%d/%d/%d", &partTmp.Birth.BirthDay,
									  &partTmp.Birth.BirthMonth,
									  &partTmp.Birth.BirthYear);
                }
                break;
            case 5: //Date Naissance
                printf("%02d:%02d:%02d -> ", partTmp.Result.hours,
                                              partTmp.Result.minutes,
                                              partTmp.Result.seconds);
                scanf("%2d:%2d:%2d", &partTmp.Result.hours,
									 &partTmp.Result.minutes,
									 &partTmp.Result.seconds);

                while (resultVerif(partTmp) == 0) {
                    printf("Le temps n'est pas conforme\n");
                    printf("%02d:%02d:%02d -> ", partTmp.Result.hours,
                                              partTmp.Result.minutes,
                                              partTmp.Result.seconds);
                    scanf("%2d:%2d:%2d", &partTmp.Result.hours,
										 &partTmp.Result.minutes,
										 &partTmp.Result.seconds);
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
*   Nom : searchParticipant
*   Usage : Rechercher un participant avec son ID ou son nom de famille
* 			+ affichage des participants
*   Parametères :
* 		paramètre 1 : int searchType (1. ID, 2. Lastname)
* 		paramètre 2 : char *field
* 				Chaîne de caractère du champ à chercher (ID ou Lastname)
*   Retour : nombre de participant trouvés
*/
int searchParticipant(int searchType, char *field){
    struct Node* temp = head;
    PARTICIPANT Target;
    int numParticipant = 0;

    switch(searchType){
        case 1: // par ID
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
        case 2: //Nom de famille
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
*   Nom : addParticipant
*   Usage : Ajouter un participant
*   Parametères : void
*   Retour : void
*/
void addParticipant(){

	//Déclaration d'un participant temporaire pour stockage des données
    PARTICIPANT newParticipant;

    clearCmd();
    linePrint();
    printf("\n ENREGISTREMENT D'UN NOUVEL UTILISATEUR");
    linePrint();

	//Attribution automatique d'un ID
    idAttribution();
    strcpy(newParticipant.ID, idTmp);
    while(idVerif(newParticipant.ID) != 0) {
        idAttribution();
    }
    printf("ID OK ! ID ENREGISTRE : %s\n", newParticipant.ID);

	//Saisie du nom
    printf("Nom :"); scanf("%s", newParticipant.Lastname);

	//Saisie du prénom
    printf("Prenom :"); scanf("%s", newParticipant.Firstname);

	//Saisie du genre
    printf("Genre (M ou F) :"); scanf("%1s", newParticipant.Gender);
    if (genderVerif(newParticipant) == 0) {
        while(genderVerif(newParticipant) != 1) {
            printf("Genre non reconnu\n Entrer entrer un genre (M ou F): ");
            scanf("%1s", newParticipant.Gender);
        }
    }

	// Saisie de la date de naissance
    printf("Date de naissance (format JJ/MM/AAAA) :");
    scanf("%d/%d/%d", &newParticipant.Birth.BirthDay, &newParticipant.Birth.BirthMonth,
                      &newParticipant.Birth.BirthYear);


    while(birthVerif(newParticipant) != 1) {
             printf("Date non reconnue \n Entrer entrer une date (format JJ/MM/AAAA): ");
             scanf("%d/%d/%d", &newParticipant.Birth.BirthDay, &newParticipant.Birth.BirthMonth,
                               &newParticipant.Birth.BirthYear);
    }

	//Résultat par défaut 00:00:00
    newParticipant.Result.hours = 0;
    newParticipant.Result.minutes = 0;
    newParticipant.Result.seconds = 0;

	//Insertion du participant temporaire à la liste
    InsertAtHead(newParticipant);
    printf("Participant ajoute !\n");

}

/*
*   Nom : deleteParticipant
*   Usage : Suppression d'un participant
*   Parametères :
* 		paramètre 1 : char *ID (ID du participant)
* 		paramètre 2 : Chaîne dans laquel l'utilisateur sera supprimé
*   Retour : nombre de participant trouvés
*/
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
      //Supprimer premier élément
      else if (temp->prev == NULL)
      {
          head = temp->next;
          (temp->next)->prev = NULL;
          //free(temp);
          printf("Deleted\n");
      }
      //Supprimer le dernier élément
      else if (temp->next == NULL)
      {
          (temp->prev)->next = NULL;
          printf("Deleted\n");
          //free(temp);
      }
      //Supprimer un autre élément
      else
      {
          (temp->prev)->next = temp->next;
          (temp->next)->prev = temp->prev;
          printf("Deleted\n");
          //free(temp);
      }
      writeLinkedList("data.txt", head);
  }


/*
*   Nom : resultComputed
*   Usage : Calcul des résultat dans la variable resultComputed de la structure RESULT
* 			(heures, minutes, secondes) -> secondes
*   Parametères :
* 		paramètre 1 : liste dans laquelle sera effectuée les calculs
*   Retour : nombres de participants pour lesquels leur résultat a été calculé
*/
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

/*
*   Nom : bubbleSort
*   Usage : Tri à bulles des participant
*   Parametères :
* 		paramètre 1 : liste triée
*   Retour : void
*/
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

/*
*   Nom : resultEnter
*   Usage : Fonction qui va permettre d'ajouter les résultats aux
* 			participant qui n'ont pas encore de résultat renseigné
*   Parametères :
* 		paramètre 1 : liste dans laquelle sera entré les résultats
* 					  des participants
*   Retour : void
*/
void resultEnter(struct Node* head){

    PARTICIPANT partTmp;
    partTmp.Result.hours = 0;
    partTmp.Result.minutes= 0;
    partTmp.Result.seconds = 0;

    int nb = 0;

    while(head != NULL) {

        if(head->Participant.Result.resultComputed == 0){
            nb += 1;
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

            head->Participant.Result = partTmp.Result;
        }


        head = head->next;

    }

    if ( nb == 0 ) {
        printf("AUCUN RESULTAT A ENTRER, LES CANDIDATS PRESENTS DANS LA BASE ONT DEJA UN RESULTAT\n");
    } else {
        printf("Vous avez enregistre %d resultat(s)\n", nb);
    }

    //writeLinkedList("data.txt", head);

}
