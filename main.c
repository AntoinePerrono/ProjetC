#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include "list.h"
#include "file.h"
#include "manage.h"
#include "print.h"
#include "navigation.h"


int main(void) {

	head = NULL;

    //IMPORT POUR AVOIR DES PARTICIPANTS DEJA ENREGISTRES
    readFile("data_import.txt", head);

    launch();

    return 0;
}
