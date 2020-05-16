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
    // Δημιουργεία νέου κόμβου
    listPtr newNode;

    newNode = (listNode*)malloc(sizeof(listNode));
    // Τυπικός έλεγχος στην περίπτωση που δεν υπάρχει μνήμη
    if (!newNode) {
        cout << "Memory couldn't be allocated" << endl;
        return false;
    }
    // Αποθήκευση του user που δόθηκε ως data του κόμβου
    newNode->data = user;

    // Ορισμός του pointer που δείχνει στον επόμενο κόμβο σε null αφού δεν υπάρχει άλλος
    newNode->next = nullptr;

    // Αν δεν υπάρχει στοιχείο στη λίστα ορισμός του newNode ως το πρώτο στοιχείο
    if (*head == nullptr) {
        *head = newNode;
    } else { // Διαφορετικά διάσχιση της λίστας μέχρι να βρεθεί το τέλος και να προστεθεί ο νέος κόμβος στο τέλος
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
    // Το head και το user έχουν περάσει με pointer ώστε να επηρεαστούν από τη συνάρτηση και να διαγραφούν
    *user = current->data;

    // Σύνδεση το κόμβου με τον επόμενο
    *head = (*head)->next;
    // Διαγραφή του αρχικού
    free(current);
    return true;
}

// Παρόμοια με την llDeteleStart
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

    // Διαγραφή όλων των στοιχείων της λίστας
    while (*head != nullptr) {
        ptr = *head;
        *head = (*head)->next;
        free(ptr);
    }
}