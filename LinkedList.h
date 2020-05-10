#include "User.h"

const int usersNumber = 30;

struct node {
    int data;
    struct node* next;
};

typedef struct node listNode; // Συνώνυμο του κόμβου λίστας
typedef struct node* listPtr; // Συνώνυμο του δείκτη κόμβου

// Λειτουργίες της λίστας
void llInit(listPtr* head);
int llInsertStart(listPtr* head, int arrayPtr);
int llInsertEnd(listPtr* head, int arrayPtr);
int llInsertAfter(listPtr p, int arrayPtr);
int llDeleteStart(listPtr* head, int* arrayPtr);
int llDeleteAfter(listPtr prev, int* arrayPtr);
void llDisplay(listPtr head, int usersNumber);
void llDestroy(listPtr* head);