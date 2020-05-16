#include "LinkedList.h"
#include <iostream>
using namespace std;

void llInit(listPtr* head) {
    *head = nullptr;
}

User llData(listPtr ptr) {
    return ptr->data;
}

int llInsertEnd(listPtr* head, User user) {
    listPtr newNode;

    newNode = (listNode*)malloc(sizeof(listNode));
    if (!newNode) {
        cout << "Memory couldn't be allocated" << endl;
        return false;
    }
    newNode->data = user;

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

int llInsertAfter(listPtr p, User user) {
    listPtr newNode;

    // Δέσμευση μνήμης για νέο κόμβο
    newNode = (listNode*)malloc(sizeof(listNode));
    // Έλεγχος επιτυχίας δέσμευσης μνήμης
    if (!newNode) {
        cout << "Memory couldn't be allocated" << endl;
        return false;
    }
    // Προσθήκη του user στο data
    newNode->data = user;

    newNode->next = p->next; // Το next του νέου κόμβου δείχνει εκεί όπου έδειχνε το p->next
    p->next = newNode; // Και το p->next τώρα δείχνει στο νέο κόμβο
    return true;
}

int llDeleteStart(listPtr* head, User* user) {
    listPtr current;

    if (*head==nullptr) {
        cout << "Δεν υπάρχει στοιχείο στη λίστα για διαγραφή" << endl;
        return false;
    }

    current = *head;
    *user = current->data;

    *head = (*head)->next;
    free(current);
    return true;
}

int llDeleteAfter(listPtr prev, User* user) {
    listPtr current;

    if (prev->next==nullptr) {
        cout << "Δεν υπάρχει κόμβος μετά τον δοθέν για διαγραφή";
        return false;
    }

    current = prev->next;
    *user = current->data;

    prev->next = current->next;
    free(current);
    return true;
}

void llDisplay(listPtr head) {
    listPtr current;

    current = head;
    while (current != nullptr) {
        (current->data).displayUserData();
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