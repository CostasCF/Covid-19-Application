#include "User.h"

struct node {
    User data;
    struct node* next;
};

typedef struct node listNode; // Συνώνυμο του κόμβου λίστας
typedef struct node* listPtr; // Συνώνυμο του δείκτη κόμβου

// Λειτουργίες της λίστας
void llInit(listPtr* head);
User llData(listPtr p);
int llInsertStart(listPtr* head, User user);
int llInsertEnd(listPtr* head, User user);
int llInsertAfter(listPtr p, User user);
int llDeleteStart(listPtr* head, User* user);
int llDeleteAfter(listPtr prev, User* user);
void llDisplay(listPtr head);
void llDestroy(listPtr* head);