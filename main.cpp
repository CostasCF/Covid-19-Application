#include <iostream>
#include <ctime>
#include "User.h"
#include "LinkedList.h"
using namespace std;
void repair();

bool userWillMove() {
    // 33.3% πιθανότητα να κουνηθεί ο χρήστης
    int random = rand() % 3;
    return random == 1;
}

bool gpsWorked() {
    // 10% πιθανότητα να μη δουλέψει το gps και να χαθεί μία χρονική στιγμή
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

    // Ορισμός της απόστασης μεταξύ κάθε στοιχείου του πλέγματος

    // Δημιουργεία χρηστών
    const int UsersNumber = 3;

    // Ορισμός ημερών
    const int daysNum = 2;

    // Δήλωση ενός δισδιάστατου πίνακα του τύπου listPtr που κάθε γραμμή αντιστοιχεί σε μία μέρα
    // και περιέχει μία απλά συνδεδεμένη λίστα για την τροχιά του κάθε χρήστη εκείνη τη μέρα
    listPtr Users[daysNum][UsersNumber];

    for (int day = 0; day < daysNum; day++) {
        for (int userNum = 0; userNum < UsersNumber; userNum++) {

            // Αρχικοποίηση όλων των συνδεδεμένων λίστών με την τιμή null
            llInit(&Users[day][userNum]);

        }
    }

    // Επανάληψη για τις μέρες
    for (int day = 0; day < daysNum; day++) {

        for (int userNum = 0; userNum < UsersNumber; userNum++) {

            // Χρήση μεταβλητών για δευτερόλεπτα, λεπτά και ώρες, ώστε ο χρόνος να
            // εμφανίζεται με πιο όμορφο τρόπο
            int seconds = 0;
            int minutes = 0;
            int hours = 0;

            // Δημιουργία αντικειμένου User
            User user{};

            // Ορισμός ταυτότητας και κατάστασης μόλυνσης κάθε χρήστη
            // Ταυτότητα
            user.id = userNum + 1;
            // Κατάστασης μόλυνσης
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

                // Ορισμός τυχαίων συντεταγμένων του χρήστη
                // Συντεταγμένες
                if (!gpsWorked()) { // H gpsWorked επιστρέφει true αν το gps δούλεψε, αλλιώς false

                    if (userWillMove()) {   // H UserWillMove επιλέγει τυχαία αν θα κινηθεί
                                            // ο χρήστης ή αν θα παραμείνει στάσιμος
                        user.x = rand() % D;
                        user.y = rand() % D;
                    }

                    user.seconds = seconds;
                    user.minutes = minutes;
                    user.hours = hours;

                    // Εισαγωγή στη λίστα του συγκεκριμένου χρήστη της συγκεκριμένης μέρας
                    // της πληροφορίας περί απόστασης, χρόνου, id και κατάστασης μόλυνσης
                    llInsertEnd(&Users[day][userNum], user);

                }

                seconds += 30;

            }
        }
    }

    for (int day = 0; day < daysNum; day++) {
        cout << endl << "DAY " << day+1 << endl << endl;
        for (int userNum=0; userNum < UsersNumber; userNum++) {
            cout << endl << "USER " << userNum+1 << endl << endl;
            llDisplay(Users[day][userNum]);
        }
    }
}