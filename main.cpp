#include <iostream>
#include <ctime>
#include "User.h"
#include "LinkedList.h"
using namespace std;
void repair();

bool userWillMove() {
    int random = rand() % 3;
    return random == 1;
}

bool gpsWorked() {
    int random = rand() % 10;
    return random == 1;
}

int main() {

    // srand ώστε να μην παράγονται οι ίδιοι αριθμοί κάθε φορά που τρέχει το πρόγραμμα
    srand(time(nullptr));

    // Παραγωγή ενός τυχαίου αριθμού από 50 έως 100 για τις διαστάσεις του πλέγματος
    const int D = rand() % 50 + 50;

    // Δημιουργεία του πλέγματος
    int grid[D][D];

    // Δημιουργεία χρηστών
    const int UsersNumber = 2;

    // Ορισμός ημερών
    const int daysNum = 2;

    // Πίνακας των χρηστών
    listPtr Users[daysNum][UsersNumber];

    for (int day = 0; day < daysNum; day++) {
        for (int userNum = 0; userNum < UsersNumber; userNum++) {
            // Δημιουργεία νέας λίστας (με βάση το LinkedList.h και LinkedList.cpp που δημιουργήθηκαν προηγουμένως)
            //listPtr userTrajectory;
            // Αρχικοποίηση συνδεδεμένης λίστας
            llInit(&Users[day][userNum]); // Περνάμε τη διεύθυνση του userTrajectory επειδή η llInit ζητάει δείκτη

            //Users[day][userNum] = userTrajectory;
        }
    }
    // Δημιουργεία ενός πίνακα 7 θέσεων (για καθεμία από τις 7 μέρες) με δείκτες,
    // όπου σε κάθε θέση αποθηκεύεται ο δείκτης που δείχνει στον πρώτο κόμβο
    // αμέσως μετά την αλλαγή της ημέρας
    //listPtr dayPtr[daysNum][UsersNumber];

    // Επανάληψη για 7 ημέρες
    for (int day = 0; day < daysNum; day++) {
        cout << endl << "ITS A NEW DAWN ITS A NEW DAY ITS A NEW LIFE FOOOOOOOR MEEEE" << endl << endl;
        for (int userNum = 0; userNum < UsersNumber; userNum++) {

            int seconds = 0;
            int minutes = 0;
            int hours = 0;

            // Δημηουργία αντικειμένου User
            User user{};

            // Ορισμός ταυτότητας και κατάστασης μόλυνσης κάθε χρήστη
            // Ορισμός ταυτότητας του χρήστη
            user.id = userNum + 1;
            // Ορισμός κατάστασης μόλυνσης
            user.setInfectionStatus();

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
                // Συντεταγμένες
                if (!gpsWorked()) {

                    if (userWillMove()) {
                        user.x = rand() % D;
                        user.y = rand() % D;
                    }

                    user.seconds = seconds;
                    user.minutes = minutes;
                    user.hours = hours;

                    llInsertEnd(&Users[day][userNum], user);

                }
                seconds += 30;
            }

        }

        cout << "Dimension: " << D << endl;

        //for (int i = 0; i < UsersNumber; i++) {
        //    dayPtr[day][i] = Users[i];
        //}

    }

    for (int day = 0; day < daysNum; day++) {
        cout << endl << "DAY " << day+1 << endl << endl;
        for (int userNum=0; userNum < UsersNumber; userNum++) {
            cout << endl << "USER " << userNum+1 << endl << endl;
            llDisplay(Users[day][userNum]);
        }
    }

    cout << endl << " NEW TEXT " << endl << endl;
    //for (int i = 0; i < UsersNumber; i++) {
     //   llDisplay(dayPtr[0][i]);
    //}
}