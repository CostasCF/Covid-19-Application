#include <iostream>
#include <ctime>
#include "User.h"
#include "LinkedList.h"


using namespace std;

int main() {

    // srand ώστε να μην παράγονται οι ίδιοι αριθμοί κάθε φορά που τρέχει το πρόγραμμα
    srand(time(nullptr));
    // Παραγωγή ενός τυχαίου αριθμού από 50 έως 100 για τις διαστάσεις του πλέγματος
    const int D = rand() % 50 + 50;
    // Δημιουργεία του πλέγματος
    int grid[D][D];

    // Δημιουργεία χρηστών
    const int UsersNumber = 10;
    // Πίνακας των χρηστών
    listPtr Users[UsersNumber];
    for (int userId = 0; userId < UsersNumber; userId++) {
        // Δημιουργεία νέας λίστας (με βάση το LinkedList.h και LinkedList.cpp που δημιουργήθηκαν προηγουμένως)
        listPtr userTrajectory;
        // Αρχικοποίηση συνδεδεμένης λίστας
        llInit(&userTrajectory); // Περνάμε τη διεύθυνση του userTrajectory επειδή η llInit ζητάει δείκτη

        Users[userId] = userTrajectory;
    }


    // Δημιουργεία ενός πίνακα 7 θέσεων (για καθεμία από τις 7 μέρες) με δείκτες,
    // όπου σε κάθε θέση αποθηκεύεται ο δείκτης που δείχνει στον πρώτο κόμβο
    // αμέσως μετά την αλλαγή της ημέρας
    //listPtr dayPtr[7];

    // Επανάληψη για 7 ημέρες
    for (int day = 1; day <= 1; day++) {

        for (int userId = 0; userId < UsersNumber; userId++) {

            int seconds = 0;
            int minutes = 0;
            int hours = 0;

            // Δημηουργία αντικειμένου User
            User user;

            // Ορισμός ταυτότητας και κατάστασης μόλυνσης κάθε χρήστη
            for (int i = 0; i < UsersNumber; i++) {
                // Ορισμός ταυτότητας του χρήστη
                user.id = userId + 1;
                // Ορισμός κατάστασης μόλυνσης
                user.setInfectionStatus();
            }

            // Επανάληψη που κρατάει όσο τα δευτερόλεπτα μίας ημέρας
            for (int i = 0; i < 86400; i += 30) {

                // Μετατροπή δευτερολέπτων σε λεπτά
                if (seconds == 60) {
                    minutes++;
                    seconds = 0;
                }

                // Μετατροπή λεπτών σε ώρες
                if (minutes == 60) {
                    hours++;
                    minutes = 0;
                }

                // Ορισμός τυχαίων συντεταγμένων για κάθε χρήστη σε κάθε χρονική στιγμή
                for (int i = 0; i < UsersNumber; i++) {
                    // Συντεταγμένες
                    user.x = rand() % D;
                    user.y = rand() % D;
                }

                for (int j = 0; j < UsersNumber; j++) {
                    user.seconds = seconds;
                    user.minutes = minutes;
                    user.hours = hours;
                }

                llInsertEnd(&Users[userId], user);

                seconds += 30;
            }

        }
        cout << "Dimension: " << D << endl;

        for (listPtr u : Users) {
            llDisplay(u);
        }
    }
}

