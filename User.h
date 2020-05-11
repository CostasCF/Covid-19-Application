#ifndef USER_H
#define USER_H
#include <iostream>
using namespace std;

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
        infected = random == 0;
    }

    void displayUserData() const {
        cout << "User " << id <<  " -> Coordinates: x = " << x << " y = " << y << ". Time ";
        cout << hours << ":" << minutes << ":" << seconds << boolalpha << " Infection status: " << infected << endl;
    }
};

#endif