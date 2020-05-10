#ifndef USER_H
#define USER_H
#include <iostream>

struct User {
    // Ταυτότητα χρήστη
    int id;
    // Ωρα
    int hours;
    int minutes;
    int seconds;
    // Συντεταγμένες
    int x;
    int y;
    // Κατάσταση μόλυνσης
    bool infected;

    // Ορισμός κατάστασης μόλυνσης
    void setInfectionStatus() {
        // Τυχαία επιλογή αν είναι μολυσμένος ή όχι
        int random = rand() % 5;
        // 20% πιθανότητα να είναι μολυσμένος
        if (random == 0) {
            infected = true;
        } else {
            infected = false;
        }
    }
};

#endif