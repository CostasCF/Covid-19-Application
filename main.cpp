#include <iostream>
#include <ctime>
#include <cmath>

#include "User.h"
#include "LinkedList.h"

using namespace std;
bool repair(int day, listPtr* head)  {
    bool flag;
    listPtr newNode;
    while(flag){
        if  ( )
    }
}

bool userWillMove() {
    // 33.3% πιθανότητα να κουνηθεί ο χρήστης
    int random = rand() % 3;
    return random == 1;
}

bool gpsWorked() {
    // 10% πιθανότητα να μη δουλέψει το gps και να χαθεί μία χρονική στιγμή
    int random = rand() % 10;
    return random != 1;
}

int getRandomX(int dimension) {
    return rand() % dimension;
}

int getRandomY(int dimension) {
    return rand() % dimension;
}

int getRandomSpeed() {
    return rand() % 3 + 3; // Χιλιόμετρα την ώρα
}



int main() {

    // srand ώστε να μην παράγονται οι ίδιοι αριθμοί κάθε φορά που τρέχει το πρόγραμμα
    srand(time(nullptr));

    // Παραγωγή ενός τυχαίου αριθμού από 50 έως 100 για τις διαστάσεις του πλέγματος
    const int D = rand() % 50 + 50;

    // Δημιουργεία του πλέγματος
    int grid[D][D];

    // Ορισμός της απόστασης μεταξύ κάθε στοιχείου του πλέγματος σε μέτρα
    const int gridDistance = 50;

    // Δημιουργεία χρηστών
    const int UsersNumber = 2;

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

            // Δημιουργία αντικειμένου User
            User user{};

            // Παραγωγή τυχαίας τοποθεσίας για τη γέννηση νέου χρήστη
            user.x = getRandomX(D);
            user.y = getRandomY(D);

            // Μεταβλητές που υποδεικνύουν την περιοχή στην οποία θέλει να πάει ο χρήστης
            int desiredX = user.x;
            int desiredY = user.y;

            // Meter counter
            double meterCounterX = 0;
            double meterCounterY = 0;
            // Ταχύτητα του χρήστη
            int userSpeedKm_h; // σε χιλιόμετρα ανά ώρα
            double userSpeedM_30sec; // Σε μέτρα ανά 30 δευτερόλεπτα

            // Ορισμός μεταβλητής που υποδεικνύει εάν ο χρήστης βρίσκεται σε κίνηση ή όχι
            bool userMoving = false;

            // Ορισμός ταυτότητας και κατάστασης μόλυνσης κάθε χρήστη
            // Ταυτότητα
            user.id = userNum + 1;
            // Κατάστασης μόλυνσης
            user.setInfectionStatus();

            // Χρήση μεταβλητών για δευτερόλεπτα, λεπτά και ώρες, ώστε ο χρόνος να
            // εμφανίζεται με πιο όμορφο τρόπο
            int seconds = 0;
            int minutes = 0;
            int hours = 0;

            // Int που χρησιμοποιείται σε ένα switch παρακάτω ώστε να ξεκινήσει η σωστή διαδικασία
            // ανάλογα με την τοποθεσία του χρήστη σε σχέση με την τοποθεσία που θέλει να πάει
            int cases;

            // Επανάληψη που κρατάει όσο τα δευτερόλεπτα μίας ημέρας και αυξάνεται ανα 30
            for (int daySeconds = 0; daySeconds < 86400; daySeconds += 30) {

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
                if (gpsWorked()) { // H gpsWorked επιστρέφει true αν το gps δούλεψε, αλλιώς false

                    if (!userMoving && userWillMove()) {   // H UserWillMove επιλέγει τυχαία αν ο χρήστης θα επιλέξει
                                                        // νέα τοποθεσία ή θα παραμείνει στάσιμος
                        desiredX = getRandomX(D);
                        desiredY = getRandomY(D);
                    }

                    if (user.x != desiredX || user.y != desiredY) {

                        // Αν ο χρήστης δεν κινείται αλλά θέλει να αλλάξει τοποθεσία τότε
                        // Του δίνουμε μία ταχύτητα
                        // Το συγκεκριμένο if εκτελείται μόνο την πρώτη φορά που ο χρήστης αποφασίζει να κινηθεί
                        if (!userMoving) {
                            userSpeedKm_h = getRandomSpeed(); // Επιστρέφει μία τυχαία ταχύτητα από 3 έως 6 km/h
                            userSpeedM_30sec = (double)userSpeedKm_h*1000/60/2; // Μετατροπή των km/h σε μέτρα ανά 30 δευτερόλεπτα
                            userMoving = true; // Ο χρήστης αρχίζει να κινείται

                            // Ολες οι περιπτώσεις για τα μεγέθη των user.x, desiredX, user.y και desiredY
                            // Βρίσκει για πια περίπτωση πρόκειται και γίνονται οι κατάλληλες ενέργειες στο
                            // switch που ακολουθεί
                            if (user.x <= desiredX && user.y <= desiredY) {
                                cases = 1;
                            } else if (user.x <= desiredX && user.y >= desiredY) {
                                cases = 2;
                            } else if (user.x >= desiredX && user.y <= desiredY) {
                                cases = 3;
                            } else {
                                cases = 4;
                            }

                        }

                    }

                    switch (cases) {
                        case 1:

                            if (user.x < desiredX) {
                                meterCounterX += userSpeedM_30sec;
                                if (meterCounterX > gridDistance) {
                                    user.x += 1;
                                    meterCounterX -= gridDistance;
                                }
                            } else if (user.y < desiredY) {
                                meterCounterY += userSpeedM_30sec;
                                if (meterCounterY > gridDistance) {
                                    user.y += 1;
                                    meterCounterY -= gridDistance;
                                }
                            }  else {
                                userMoving = false;
                            }
                            break;

                        case 2:

                            if (user.x < desiredX) {
                                meterCounterX += userSpeedM_30sec;
                                if (meterCounterX > gridDistance) {
                                    user.x += 1;
                                    meterCounterX -= gridDistance;
                                }
                            } else if (user.y > desiredY) {
                                meterCounterY += userSpeedM_30sec;
                                if (meterCounterY > gridDistance) {
                                    user.y -= 1;
                                    meterCounterY -= gridDistance;
                                }
                            } else {
                                userMoving = false;
                            }
                            break;
                        case 3:

                            if (user.x > desiredX) {
                                meterCounterX += userSpeedM_30sec;
                                if (meterCounterX > gridDistance) {
                                    user.x -= 1;
                                    meterCounterX -= gridDistance;
                                }
                            } else if (user.y < desiredY) {
                                meterCounterY += userSpeedM_30sec;
                                if (meterCounterY > gridDistance) {
                                    user.y += 1;
                                    meterCounterY -= gridDistance;
                                }
                            }  else {
                                userMoving = false;
                            }
                            break;

                        case 4:

                            if (user.x > desiredX) {
                                meterCounterX += userSpeedM_30sec;
                                if (meterCounterX > gridDistance) {
                                    user.x -= 1;
                                    meterCounterX -= gridDistance;
                                }
                            } else if (user.y > desiredY) {
                                meterCounterY += userSpeedM_30sec;
                                if (meterCounterY > gridDistance) {
                                    user.y -= 1;
                                    meterCounterY -= gridDistance;
                                }
                            } else {
                                userMoving = false;
                            }
                            break;

                        default:
                            cout << "Κάτι πάει λάθος" << endl;
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
            //calling repair()
            repair(Users[day][&userNum]);
        }

    }

    for (int day = 0; day < daysNum; day++) {
        for (int userNum = 0; userNum < UsersNumber; userNum++) {
           llDisplay(Users[day][userNum]);
        }
    }
}