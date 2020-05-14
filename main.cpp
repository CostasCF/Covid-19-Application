#include <iostream>
#include <ctime>
#include <cmath>

#include "User.h"
#include "LinkedList.h"

using namespace std;
void repair(listPtr userTrajectory, int gridDistance);

int FIND_CROWDED_PLACES(listPtr pNode, int i, int i1);

bool userWillMove() {
    // 25% πιθανότητα να κουνηθεί ο χρήστης
    int random = rand() % 4;
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

// Κουνάει το χρήστη και επιστρέφει
// true αν ο χρήστης συνεχίζει να κουνιέται και
// false αν έφτασε στον προορισμό του
bool moveUser(int specifier, int &x, int &y, int desiredX, int desiredY, double &meterCounterX,
              double &meterCounterY, double userSpeedM_30sec, int gridDistance) {
    switch (specifier) {
        case 1:

            if (x < desiredX) {
                meterCounterX += userSpeedM_30sec;
                while (meterCounterX >= gridDistance) {
                    x += 1;
                    meterCounterX -= gridDistance;
                }
            } else if (y < desiredY) {
                meterCounterY += userSpeedM_30sec;
                while (meterCounterY >= gridDistance) {
                    y += 1;
                    meterCounterY -= gridDistance;
                }
            } else {
                return false;
            }
            break;

        case 2:

            if (x < desiredX) {
                meterCounterX += userSpeedM_30sec;
                while (meterCounterX >= gridDistance) {
                    x += 1;
                    meterCounterX -= gridDistance;
                }
            } else if (y > desiredY) {
                meterCounterY += userSpeedM_30sec;
                while (meterCounterY >= gridDistance) {
                    y -= 1;
                    meterCounterY -= gridDistance;
                }
            } else {
                return false;
            }
            break;
        case 3:

            if (x > desiredX) {
                meterCounterX += userSpeedM_30sec;
                while (meterCounterX >= gridDistance) {
                    x -= 1;
                    meterCounterX -= gridDistance;
                }
            } else if (y < desiredY) {
                meterCounterY += userSpeedM_30sec;
                while (meterCounterY >= gridDistance) {
                    y += 1;
                    meterCounterY -= gridDistance;
                }
            } else {
                return false;
            }
            break;

        case 4:

            if (x > desiredX) {
                meterCounterX += userSpeedM_30sec;
                while (meterCounterX >= gridDistance) {
                    x -= 1;
                    meterCounterX -= gridDistance;
                }
            } else if (y > desiredY) {
                meterCounterY += userSpeedM_30sec;
                while (meterCounterY >= gridDistance) {
                    y -= 1;
                    meterCounterY -= gridDistance;
                }
            } else {
                return false;
            }
            break;

        default:
            cout << "Something went wrong" << endl;
    }
    return true;
}



int main() {

    // srand ώστε να μην παράγονται οι ίδιοι αριθμοί κάθε φορά που τρέχει το πρόγραμμα
    srand(time(nullptr));

    // Παραγωγή ενός τυχαίου αριθμού από 50 έως 100 για τις διαστάσεις του πλέγματος
    const int D = rand() % 50 + 50;

    // Δημιουργεία του πλέγματος
    int grid[D][D];

    // Ορισμός της απόστασης μεταξύ κάθε στοιχείου του πλέγματος σε μέτρα
    const int gridDistance = 30;

    // Ορισμός χρηστών
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
            int specifier;

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
                            specifier = 1;
                        } else if (user.x <= desiredX && user.y >= desiredY) {
                            specifier = 2;
                        } else if (user.x >= desiredX && user.y <= desiredY) {
                            specifier = 3;
                        } else {
                            specifier = 4;
                        }

                    }

                }

                if (userMoving) {
                    // Κουνάει το χρήστη και ανανεώνει τη userMoving μεταβλητή
                    userMoving = moveUser(specifier, user.x, user.y, desiredX, desiredY, meterCounterX,
                                meterCounterY, userSpeedM_30sec, gridDistance);
                }

                user.seconds = seconds;
                user.minutes = minutes;
                user.hours = hours;


                if (gpsWorked()) { // H gpsWorked επιστρέφει true αν το gps δούλεψε, αλλιώς false
                    // Εισαγωγή στη λίστα του συγκεκριμένου χρήστη της συγκεκριμένης μέρας
                    // της πληροφορίας περί απόστασης, χρόνου, id και κατάστασης μόλυνσης
                    llInsertEnd(&Users[day][userNum], user);
                }
                seconds += 30;

            }


        }
        // Κάλεσμα repair
        for (int userNum = 0; userNum < UsersNumber; userNum++)
            repair(Users[day][userNum], gridDistance);


    }


    for (int day = 0; day < daysNum; day++) {
        for (int userNum = 0; userNum < UsersNumber; userNum++) {
            cout<<endl<<"new day new life"<<endl;
            llDisplay(Users[day][userNum]);
        }
    }
    //συνεχεια της main
    //καλεσμα FIND_CROWDED_PLACES

   // int crowd = FIND_CROWDED_PLACES(Users[1][UsersNumber],300,D );

}

//time = δευτερολεπτα που παρεμειναν οι χρηστες σε μια περιοχη
int FIND_CROWDED_PLACES(listPtr pNode, int time, int D) {
    int grid[D][D];
    int crowd;
    listPtr current = pNode;
    /* Πρεπει να συγκρίνουμε όλες τις συντεταγμενες των χρηστών ωστε να βρουμε τα σημεια που ειναι ιδιες  (δηλαδη συναντήθηκαν στο ιδιο σημειο x,y δυο χρήστες )
     * το ιδιο χρονικο διαστημα πχ απο τις 4:00 μεχρι τις 4:15
     * ,να τους καταγράψουμε στην μεταβλητη crowd και
     * επίσης να καταγράψουμε τον ελάχιστο χρόνο που δεν μετακινήθηκαν καθόλου απο την στιγμή που ξεκίνησε η συνάντηση τους.
     * */
    return crowd;
}



void repair(listPtr userTrajectory, int gridDistance)  {
    // Μετατροπή ωρών, λεπτών και δευτερολέπτων σε δευτερόλεπτα
    listPtr current;
    listPtr prev;

    prev = userTrajectory;
    current = prev;
    while (current != nullptr) {
        current = prev->next;

        if (current != nullptr) {
            int prevInstanceSeconds = llData(prev).seconds + llData(prev).minutes * 60
                                      + llData(prev).hours * 60 * 60;
            int instanceSeconds = llData(current).seconds + llData(current).minutes * 60
                                  + llData(current).hours * 60 * 60;
            int secondsDiff = instanceSeconds - prevInstanceSeconds;

            if (secondsDiff > 30) {

                int prevX = llData(prev).x;
                int currentX = llData(current).x;
                double meterCounterX = 0;

                int prevY = llData(prev).y;
                int currentY = llData(current).y;
                double meterCounterY = 0;

                User user{};

                user.x = prevX;
                user.y = prevY;

                user.id = llData(prev).id;
                user.infected = llData(prev).infected;

                // Βλέπε β' Λυκείου μαθηματικά κατεύθυνσης απόσταση 2 σημείων
                double realDistance = sqrt(pow((llData(current).x - llData(prev).x), 2)
                                           + pow((llData(current).y - llData(prev).y), 2)) * gridDistance;
                double userSpeed = realDistance / 30;
                double userSpeedM_30sec = userSpeed*1000/60/2;

                for (int seconds = 30; seconds < secondsDiff; seconds += 30) {

                    user.seconds = llData(prev).seconds + 30;
                    user.minutes = llData(prev).minutes;
                    user.hours = llData(prev).hours;

                    // Μετατροπή δευτερολέπτων σε λεπτά
                    if (user.seconds == 60) {
                        user.minutes++;
                        user.seconds = 0;
                    }

                    // Μετατροπή λεπτών σε ώρες
                    if (user.minutes == 60) {
                        user.hours++;
                        user.minutes = 0;
                    }

                    if (prevX < currentX) {
                        meterCounterX += userSpeedM_30sec;
                        while (meterCounterX >= gridDistance) {
                            user.x += 1;
                            meterCounterX -= gridDistance;
                        }
                    } else if (prevX > currentX) {
                        meterCounterX += userSpeedM_30sec;
                        while (meterCounterX >= gridDistance) {
                            user.x -= 1;
                            meterCounterX -= gridDistance;
                        }
                    } else if (prevY < currentY) {
                        meterCounterY += userSpeedM_30sec;
                        while (meterCounterY >= gridDistance) {
                            user.y += 1;
                            meterCounterY -= gridDistance;
                        }
                    } else if (prevY > currentY) {
                        meterCounterY += userSpeedM_30sec;
                        while (meterCounterY >= gridDistance) {
                            user.y -= 1;
                            meterCounterY -= gridDistance;
                        }
                    }

                    llInsertAfter(prev, user);

                    prev = prev->next;
                }
            }
        }
        prev = current;

    }
}