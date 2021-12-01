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
*   Nom : readFile
*   Usage : Lecture d'un fichier
*   Parametères :
* 		paramètre 1 : Nom du fichier
* 		paramètre 2 : liste dans laquelle est importée le fichier
*   Retour :
* 		valeur -1 : Erreur dans l'ouverture du fichier
* 		valeur 0 : Erreur dans le parsing du fichier
* 		valeur 1 : Fichier importé avec succès
*/
int readFile(char *fileName, struct Node* head)
{
    // Ouverture du fichier
    FILE *fp = fopen(fileName, "r");
    // Création d'un participant temporaire pour stockage des données
    struct Participant temp;

    // Erreur dans l'ouverture du fichier, inexistant ?
    if (fp == NULL)
    {
        printf("ERREUR : Impossible d'ouvrir le fichier %s\n", fileName);
        return -1;
    }

    //Longueur de lecture max par ligne : max 256 bytes
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    int line = 1;

    // Lecture de chaque ligne dans le fichier
    // comme un chaîne de caractère ensuite réutilisée pour
    // récupérer les infos par parsing
    while (fgets(buffer, MAX_LENGTH, fp))
    {
        char *p;
        // ID
        p = strtok(buffer, ",/;");
        if (p)
        {
            strcpy(temp.ID, p);
        }
        // Lastname
        p = strtok(NULL, ",/;");
        if (p)
        {
            strcpy(temp.Lastname, p);
        }
        // Firstname
        p = strtok(NULL, ",/;");
        if (p)
        {
            strcpy(temp.Firstname, p);
        }
        // Gender
        p = strtok(NULL, ",/;");
        if (p)
        {
            strcpy(temp.Gender, p);
        }
        // Birth day
        p = strtok(NULL, ",/;");
        if (p)
        {
            temp.Birth.BirthDay = atoi(p);
        }
        // Birth month
        p = strtok(NULL, ",/;");
        if (p)
        {
            temp.Birth.BirthMonth = atoi(p);
        }
        // Birth year
        p = strtok(NULL, ",/;");
        if (p)
        {
            temp.Birth.BirthYear = atoi(p);
        }
        // Time hour
        p = strtok(NULL, ",/;");
        if (p)
        {
            temp.Result.hours = atoi(p);
        }
        // Time minute
        p = strtok(NULL, ",/;");
        if (p)
        {
            temp.Result.minutes = atoi(p);
        }
        // Time seconde
        p = strtok(NULL, ",/;");
        if (p)
        {
            temp.Result.seconds = atof(p);
        }

		// Vérification de la conformité des données à ajouter
        if ( (idVerif(temp.ID)==0) && genderVerif(temp) && birthVerif(temp) && resultVerif(temp) ) {
			// Insertion du participant dans la liste
			InsertAtHead(temp);
        } else {
			//Erreur avec le contenu du fichier
            printf("Erreur dans le fichier import : parsing impossible; line : %d\n", line);
            printf("Plusieurs raisons possibles :\n");
            printf("- ID deja existant\n");
            printf("- Erreur dans le champ genre, date ou resultat\n");
            printf("- Formatage des champs non respectes\n");
            return 0;
            break;
        }

        line += 1;

    }
    // close the file pointer to avoid memory leak
    fclose(fp);
    return 1;
}

/*
*   Nom : writeLinkedList
*   Usage : Ecriture de la liste dans un fichier txt
*   Parametères :
* 		paramètre 1 : Nom du fichier pour l'export
* 		paramètre 2 : liste à exporter dans un fichier
*   Retour :
* 		valeur -1 : Erreur dans l'ouverture du fichier
* 		valeur 1 : Fichier exporté avec succès
*/
int writeLinkedList(char *filename, struct Node* head){

    struct Node* temp = head;

	// Ouverture (ou création) du fichier d'export
    FILE* file;
    file = fopen (filename, "w");
    if (file == NULL)
    {
        fprintf(stderr, "\nImpossible d'ouvrir le fichier\n");
        return -1;
    }


    // Ecriture de tous les noeuds de la liste
    while(temp!=NULL)
    {
        //Ecriture dans le fichier
        fprintf(file,"%s,%s,%s,%s,%02d/%02d/%02d,%02d/%02d/%02d;\n",
                temp->Participant.ID,
                temp->Participant.Lastname,
                temp->Participant.Firstname,
                temp->Participant.Gender,
                temp->Participant.Birth.BirthDay,temp->Participant.Birth.BirthMonth,temp->Participant.Birth.BirthYear,
                temp->Participant.Result.hours,temp->Participant.Result.minutes,temp->Participant.Result.seconds
                );

        temp = temp->next;
    }

    fclose(file);
    return 1;

}
