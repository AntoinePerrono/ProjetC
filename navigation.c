#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include "list.h"
#include "file.h"
#include "manage.h"
#include "print.h"
#include "navigation.h"

//Global variable for close the registration
int CLOSE = 0;

void launch(void){
    while(1) {

        home();
        navigate();
    }

}

void home(void){
    clearCmd();
    logoPrint();
    printf("MENU PARTICIPANT MANAGER\n");
    if (CLOSE) { printf("[ATTENTION : LES INSCRIPTIONS SONT CLOTUREES]\n"); }
    printf("Que souhaitez-vous faire ?\n");
    printf("1. Ajouter un participant\n");
    printf("2. Modifier un participant\n");
    printf("3. Afficher la liste des participants\n");
    printf("4. Afficher par tranche d'age choisie\n");
    printf("5. Rechercher un participant par ID ou NOM DE FAMILLE\n");
    printf("6. Trier par ordre croissant les resultats\n");
    printf("7. Entrer les resultats des participants\n");
    printf("8. Cloturer les inscriptions\n");
    printf("9. Importer un fichier\n");
    printf("10. Sauvegarder dans un fichier\n");
    printf("11. Quitter le programme\n");
}

void navigate(){
    int rq = 0;
    printf("Choix : ");
    scanf("%d", &rq);
    char filename[LENGTH_TXT_FIELD];

    switch(rq) {
        case 1: //Ajouter un participant
            if (CLOSE) {
                clearCmd();
                printf("AJOUT D'UN PARTICIPANT\n");
                printf("ACCES REFUSE : les inscriptions sont cloturees\n");
                returnHome();

            } else {
                addParticipant();
            }

            break;
        case 2: //Modifier un participant
            clearCmd();
            linePrint();
            printf("MODIFICATION D'UN PARTICIPANT");
            linePrint();
            listPrint(head);
            printf("ID DU PARTICPANT A MODIFIER : ");
            char tmpID[LENGTH_ID];
            scanf("%6s", tmpID);
            modifyParticipant(tmpID, head);
            break;
        case 3:
            clearCmd();
            listPrint(head);
            returnHome();
            break;
		case 4: //Affichage participant par tranche d'âge
			clearCmd();
			printf("AFFICHAGE DES PARTICIPANTS PAR TRANCHE D'AGE\n");
			int min, max;
			printf("Age min : ");
			scanf("%d", &min);
			printf("Age max : ");
			scanf("%d", &max);
			
			agePartPrint(min, max, head);
			
			returnHome();
			break;
			

        case 5: //Recherche d'un participant
            clearCmd();
            printf("RECHERCHER UN PARTICIPANT\n");
            linePrint();

            int type = 0;

            printf("TYPE  DE RECHERCHE :\t1. ID\t 2. NOM DE FAMILLE\n CHOIX : ");
            scanf("%d", &type);


            switch(type){
                case 1: //Par ID
                    printf("RECHERCHE PAR ID\n");
                    char ID[LENGTH_ID];
                    printf("Entrez ID : ");
                    scanf("%s", ID);
                    searchParticipant(1, ID);
                    returnHome();
                    break;

                case 2: //Par nom
                    printf("RECHERCHE PAR NOM DE FAMILLE\n");
                    char lastname[LENGTH_TXT_FIELD];
                    printf("Entrez NOM DE FAMILLE : ");
                    scanf("%s", lastname);
                    searchParticipant(2, lastname);
                    returnHome();
                    break;

                default:
                    break;
            }
        case 6: //Affichage liste triée
            clearCmd();
            bubbleSort(head);
            listPrint(head);
            returnHome();
            break;

        case 7: //Entrer les résultats
            resultComputed(head);
            resultEnter(head);
            break;

        case 8: //Clôturer les inscriptions
            registrationClosed();
            break;

        case 9: //Import fichier txt
            clearCmd();
            printf("IMPORTER UN FICHIER TXT\n");

            printf("Entrez un nom de fichier (ne pas mettre l'extension)\nNom du fichier : ");
            scanf("%s", filename);
            strcat(filename, ".txt");
            if (readFile(filename, head) == 1){
                printf("Les donnees ont ete lue depuis le fichier %s\n", filename);
            } else {
                printf("Erreur de lecture du fichier %s\n", filename);
            }
            returnHome();

            break;

        case 10: //Sauvegarde vers fichier txt
            clearCmd();
            printf("ENREGISTRER DANS UN FICHIER TXT\n");

            printf("Entrez un nom de fichier (ne pas mettre l'extension)\nNom du fichier : ");
            scanf("%s", filename);
            strcat(filename, ".txt");
            if (writeLinkedList(filename, head)){
                printf("Les donnees ont importees sans erreur dans %s\n", filename);
            }
            returnHome();
            break;
        case 11:
            exit(0);
            printf("Une erreur s'est produite lors de la fermeture du programme");
            break;
        default:
            break;

    }


}


void returnHome(void){
    int choice = 0;
    while (choice != 1) {
        printf("RETOUR AU MENU (TAPEZ 1) : ");
        scanf("%d", &choice);
    }
}

void registrationClosed(void){
    int confirmation = 0;
    clearCmd();
    printf("CLOTURE DES INSCRIPTIONS\n");
    if (CLOSE == 0) {
        printf("Voulez-vous cloturer les inscriptions ?\t1. Oui\t2. Non\n");
        printf("Choix : "); scanf("%d", &confirmation);
        if (confirmation == 1) {
            CLOSE = 1;
            printf("LES INSCRIPTIONS SONT CLOTUREES\n");
        }
    } else {
        printf("LES INSCRIPTIONS SONT DEJA CLOTUREES\n");
    }

    returnHome();
}

