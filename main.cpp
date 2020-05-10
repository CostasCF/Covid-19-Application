#include <iostream>
#include <ctime>
#include "User.h"
#include "LinkedList.h"


using namespace std;

int main() {

    // srand ώστε να μην παράγονται οι ίδιοι αριθμοί κάθε φορά που τρέχει το πρόγραμμα
    srand(time(NULL));
    // Παραγωγή ενός τυχαίου αριθμού από 50 έως 100 για τις διαστάσεις του πλέγματος
    const int D = rand() % 50 + 50;
    // Δημιουργεία του πλέγματος
    int grid[D][D];

    // Δημιουργεία χρηστών
    const int UsersNumber = 30;
    // Πίνακας των χρηστών
    User Users[UsersNumber];
    
    // Ορισμός ταυτότητας και κατάστασης μόλυνσης κάθε χρήστη
    for (int i = 0; i < UsersNumber; i++) {
        // Ορισμός ταυτότητας για κάθε χρήστη
        Users[i].id = i + 1;
        // Ορισμός κατάστασης μόλυνσης
        Users[i].setInfectionStatus();
    }
    
    // Αρχικοποίηση συνδεδεμένης λίστας
    listPtr head;

    // Επανάληψη για 7 ημέρες
    //for (int day = 1; day <= 7; day++) {

        int seconds = -30; // -30 επειδή πριν αποθηκευτούν τα δευτερόλεπτα για πρώτη φορά αυξάνονται κατά 30
        int minutes = 0;
        int hours = 0;

        // Επανάληψη που κρατάει όσο τα δευτερόλεπτα μίας ημέρας
        for (int i = 0; i < 86400; i += 30) {
            
            // Μετατροπή δευτερολέπτων σε λεπτά
            if (seconds == 60) {
                minutes++;
                seconds = 0;
            }

            // Μετατροπή λεπτών σε ώρες
            if (minutes == 60 ) {
                hours++;
                minutes = 0;
            }

            seconds += 30;
            
            // Ορισμός τυχαίων συντεταγμένων για κάθε χρήστη σε κάθε χρονική στιγμή
            for (int i = 0; i < UsersNumber; i++) {
                // Συντεταγμένες
                Users[i].x = rand() % D;
                Users[i].y = rand() % D;
            }

            for (int j = 0; j < UsersNumber; j++) {
                Users[j].seconds = seconds;
                Users[j].minutes = minutes;
                Users[j].hours = hours;
            }

        }

        cout << "Dimension: " << D << endl;

        for (User user : Users) {
            cout << "User " << user.id << ":" << endl << "Coordinates: x = " << user.x << " y = " << user.y << ". Time ";
            cout << user.hours << ":" << user.minutes << ":" << user.seconds << boolalpha << " Infection status: " << user.infected << endl;
        }
        
    //}
}

