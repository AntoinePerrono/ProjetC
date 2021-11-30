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
*   Name : readFile
*   Usage : Read the txt file
*   Parameters : ptr of filename
*   Return : void
*/
int readFile(char *fileName, struct Node* head)
{
    // open the filename passed as parameter
    FILE *fp = fopen(fileName, "r");
    // make a data struct to store the values from file
    struct Participant temp;

    // error if file not exists
    if (fp == NULL)
    {
        printf("ERREUR : Impossible d'ouvrir le fichier %s\n", fileName);
        return -1;
    }

    // reading line by line, max 256 bytes
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    int line = 1;

    // read each line from text file
    // in this we will read a line as a string
    // then we will split the string using strtok to get all the fields values
    while (fgets(buffer, MAX_LENGTH, fp))
    {
        char *p;
        // get id
        p = strtok(buffer, ",/;");
        if (p)
        {
            strcpy(temp.ID, p);
        }
        // get lastname
        p = strtok(NULL, ",/;");
        if (p)
        {
            strcpy(temp.Lastname, p);
        }
        // get firstname
        p = strtok(NULL, ",/;");
        if (p)
        {
            strcpy(temp.Firstname, p);
        }
        // get gender
        p = strtok(NULL, ",/;");
        if (p)
        {
            strcpy(temp.Gender, p);
        }
        // get birth day
        p = strtok(NULL, ",/;");
        if (p)
        {
            temp.Birth.BirthDay = atoi(p);
        }
        // get birth month
        p = strtok(NULL, ",/;");
        if (p)
        {
            temp.Birth.BirthMonth = atoi(p);
        }
        // get birth month
        p = strtok(NULL, ",/;");
        if (p)
        {
            temp.Birth.BirthYear = atoi(p);
        }
        // get time hour
        p = strtok(NULL, ",/;");
        if (p)
        {
            temp.Result.hours = atoi(p);
        }
        // get time minute
        p = strtok(NULL, ",/;");
        if (p)
        {
            temp.Result.minutes = atoi(p);
        }
        // get time second
        p = strtok(NULL, ",/;");
        if (p)
        {
            temp.Result.seconds = atof(p);
        }
        // now add this data struct to doubly linked list head declared at the start

        if ( (idVerif(temp.ID)==0) && genderVerif(temp) && birthVerif(temp) && resultVerif(temp) ) {
           InsertAtHead(temp);
        } else {
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
*   Name : writeLinkedList
*   Usage : Write the txt file
*   Parameters : ptr of filename
*   Return : -1 error, 1 ok
*/
int writeLinkedList(char *filename, struct Node* head){

    struct Node* temp = head;

    FILE* file;
    file = fopen (filename, "w");
    if (file == NULL)
    {
        fprintf(stderr, "\nImpossible d'ouvrir le fichier\n");
        return -1;
    }


    // writing all the nodes of the linked list to the file
    while(temp!=NULL)
    {
        //Ecriture dans le fichier ICI
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
