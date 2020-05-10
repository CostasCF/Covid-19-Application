#include "LinkedList.h"
#include <iostream>
using namespace std;

void llInit(listPtr* head) {
    *head = nullptr;
};

int llInsertStart(listPtr* head, int arrayPtr) {
    // Δείκτης σε νέο κόμβο
    listPtr newNode;

    // Δέσμευση μνήμης για νέο κόμβο
    newNode = (listNode*)malloc(sizeof(listNode));
    // Έλεγχος επιτυχίας δέσμευσης μνήμης
    if (!newNode) {
        cout << "Memory couldn't be allocated" << endl;
        return false;
    }
    // Προσθήκη του arrayPtr στο data
    newNode->data = arrayPtr;

    newNode->next = *head; // Το next του νέου κόμβου δείχνει εκεί όπου έδειχνε το head
    *head = newNode; // Και το head τώρα δείχνει στο νέο κόμβο
    return true;
}

int llInsertEnd(listPtr* head, int arrayPtr) {
    listPtr newNode;

    newNode = (listNode*)malloc(sizeof(listNode));
    if (!newNode) {
        cout << "Memory couldn't be allocated" << endl;
        return false;
    }
    newNode->data = arrayPtr;

    newNode->next = nullptr;
    if (*head == nullptr) {
        *head = newNode;
    } else {
        listPtr temp = *head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    return true;
}

int llInsertAfter(listPtr p, User arrayPtr[]) {
    listPtr newNode;

    // Δέσμευση μνήμης για νέο κόμβο
    newNode = (listNode*)malloc(sizeof(listNode));
    // Έλεγχος επιτυχίας δέσμευσης μνήμης
    if (!newNode) {
        cout << "Memory couldn't be allocated" << endl;
        return false;
    }
    // Προσθήκη του arrayPtr στο data
    newNode->data = arrayPtr;

    newNode->next = p->next; // Το next του νέου κόμβου δείχνει εκεί όπου έδειχνε το p->next
    p->next = newNode; // Και το p->next τώρα δείχνει στο νέο κόμβο
    return true;
}

int llDeleteStart(listPtr* head, User* arrayPtr[]) {
    listPtr current;

    if (*head==nullptr) {
        cout << "Δεν υπάρχει στοιχείο στη λίστα για διαγραφή" << endl;
        return false;
    }

    current = *head;
    *arrayPtr = current->data;

    *head = (*head)->next;
    free(current);
    return true;
}

int llDeleteAfter(listPtr prev, User* arrayPtr[]) {
    listPtr current;

    if (prev->next==nullptr) {
        cout << "Δεν υπάρχει κόμβος μετά τον δοθέν για διαγραφή";
        return false;
    }

    current = prev->next;
    *arrayPtr = current->data;

    prev->next = current->next;
    free(current);
    return true;
}

void llDisplay(listPtr head, int userssNumber) {
    listPtr current;

    current = head;
    while (current != nullptr) {
        for (int i=0; i < usersNumber; i++) {

        }
        current = current->next;
    }
}

void llDestroy(listPtr* head) {
    listPtr ptr;

    while (*head != nullptr) {
        ptr = *head;
        *head = (*head)->next;
        free(ptr);
    }
}