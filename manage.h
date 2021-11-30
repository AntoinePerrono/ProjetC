#ifndef MANAGE_H
#define MANAGE_H

int resultVerif(PARTICIPANT Participant);

int birthVerif(PARTICIPANT Participant);

int genderVerif(PARTICIPANT Participant);

int idVerif(char *id);

void modifyParticipant(char *id, struct Node* head);

int searchParticipant(int searchType, char *field);

void addParticipant(void);

void deleteParticipant(char *id, struct Node *head);

int resultComputed(struct Node* head);

void bubbleSort(struct Node *start);

int age(BIRTHDATE birth);

DATE today(void);

void idAttribution(void);

void resultEnter(struct Node* head);

#endif
