#ifndef LIST_H
#define LIST_H

typedef struct date
{
    int day;
    int month;
    int year;
} DATE;

typedef struct result
{
    int hours;
    int minutes;
    int seconds;
    unsigned resultComputed;
} RESULT;

typedef struct birthdate
{
    int BirthDay;
    int BirthMonth;
    int BirthYear;
    int AgeComputed;
}  BIRTHDATE;

#define LENGTH_ID   8
#define LENGTH_TXT_FIELD    32
#define LENGTH_GENDER    3

typedef struct Participant
{
    char ID[LENGTH_ID];
    char Lastname[LENGTH_TXT_FIELD];
    char Firstname[LENGTH_TXT_FIELD];
    char Gender[LENGTH_GENDER];
    BIRTHDATE Birth;
    RESULT Result;
} PARTICIPANT;


typedef struct Node  {
	PARTICIPANT Participant;
	struct Node* next;
	struct Node* prev;
} NODE;

struct Node* head; // global variable - pointer to head node.

struct Node* GetNewNode(PARTICIPANT Participant);

void InsertAtHead(PARTICIPANT Participant);

#endif
