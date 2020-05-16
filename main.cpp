#include <iostream>
#include <ctime>
#include <cmath>

#include "User.h"
#include "LinkedList.h"
#include "COVID19_Operations.h"

using namespace std;

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

void increaseX(int &x, int desiredX, double &meterCounterX, double userSpeedM_30sec, int gridDistance) {
    meterCounterX += userSpeedM_30sec;
    while (meterCounterX >= gridDistance && x < desiredX) {
        x += 1;
        meterCounterX -= gridDistance;
    }
}

void decreaseX(int &x, int desiredX, double &meterCounterX, double userSpeedM_30sec, int gridDistance) {
    meterCounterX += userSpeedM_30sec;
    while (meterCounterX >= gridDistance && x > desiredX) {
        x -= 1;
        meterCounterX -= gridDistance;
    }
}

void increaseY(int &y, int desiredY, double &meterCounterY, double userSpeedM_30sec, int gridDistance) {
    meterCounterY += userSpeedM_30sec;
    while (meterCounterY >= gridDistance && y < desiredY) {
        y += 1;
        meterCounterY -= gridDistance;
    }
}

void decreaseY(int &y, int desiredY, double &meterCounterY, double userSpeedM_30sec, int gridDistance) {
    meterCounterY += userSpeedM_30sec;
    while (meterCounterY >= gridDistance && y > desiredY) {
        y -= 1;
        meterCounterY -= gridDistance;
    }
}

// Κουνάει το χρήστη και επιστρέφει
// true αν ο χρήστης συνεχίζει να κουνιέται και
// false αν έφτασε στον προορισμό του
bool moveUser(int specifier, int &x, int &y, int desiredX, int desiredY, double &meterCounterX,
              double &meterCounterY, double userSpeedM_30sec, int gridDistance) {
    switch (specifier) {
        case 1:

            if (x < desiredX) {
                increaseX(x, desiredX ,meterCounterX, userSpeedM_30sec, gridDistance);
            } else if (y < desiredY) {
                increaseY(y, desiredY ,meterCounterY, userSpeedM_30sec, gridDistance);
            } else {
                meterCounterX = 0;
                meterCounterY = 0;
                return false;
            }
            break;

        case 2:

            if (x < desiredX) {
                increaseX(x, desiredX, meterCounterX, userSpeedM_30sec, gridDistance);
            } else if (y > desiredY) {
                decreaseY(y, desiredY, meterCounterY, userSpeedM_30sec, gridDistance);
            } else {
                meterCounterX = 0;
                meterCounterY = 0;
                return false;
            }
            break;
        case 3:

            if (x > desiredX) {
                decreaseX(x, desiredX ,meterCounterX, userSpeedM_30sec, gridDistance);
            } else if (y < desiredY) {
                increaseY(y, desiredY ,meterCounterY, userSpeedM_30sec, gridDistance);
            } else {
                meterCounterX = 0;
                meterCounterY = 0;
                return false;
            }
            break;

        case 4:

            if (x > desiredX) {
                decreaseX(x, desiredX ,meterCounterX, userSpeedM_30sec, gridDistance);
            } else if (y > desiredY) {
                decreaseY(y, desiredY ,meterCounterY, userSpeedM_30sec, gridDistance);
            } else {
                meterCounterX = 0;
                meterCounterY = 0;
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

    // Δήλωση ενός δισδιάστατου πίνακα του τύπου listPtr που κάθε γραμμή αντιστοιχεί σε μία μέρα
    // και περιέχει μία απλά συνδεδεμένη λίστα για την τροχιά του κάθε χρήστη εκείνη τη μέρα
    listPtr Users[daysNum][usersNumber];

    for (int day = 0; day < daysNum; day++) {
        for (int userNum = 0; userNum < usersNumber; userNum++) {

            // Αρχικοποίηση όλων των συνδεδεμένων λίστών με την τιμή null
            llInit(&Users[day][userNum]);

        }
    }

    // Επανάληψη για τις μέρες
    for (int day = 0; day < daysNum; day++) {
        for (int userNum = 0; userNum < usersNumber; userNum++) {

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

        for (int userNum = 0; userNum < usersNumber; userNum++) {
            // Κάλεσμα repair
            repair(Users[day][userNum]);
        }

        /*for (int userNum = 0; userNum < usersNumber; userNum++) {
            // Κάλεσμα possible COVID-19 Infection
            bool userIsSick = llData(Users[day][userNum]).infected;
            if (!userIsSick) {
                //possibleCOVID_19Infection(Users[day][userNum], day, *Users);
                cout << "nvm" << endl;
            }
        }*/

        int answer;
        cout << "Do you want to check for crowded places? Press 1 for yes, or 0 for no" << endl;
        cin >> answer;
        if (answer == 1) {

            int startTime = 3600; // από τη 1
            int endTime = 5000; // μέχρι τις 2
            //cout << "Type the time interval" << endl;
            //cin >> timeInterval;

            int squareRegionOfInterest = 40; // 25x25
            //cout << "Type the squareRegionOfInterest" << endl;
            //cin >> squareRegionOfInterest;

            int minimumStayDuration = 180; // 3 λεπτά
            //cout << "Type the minimum stay duration" << endl;
            //cin >> minimumStayDuration;

            cout << "Based on the provided data there were " <<
            findCrowdedPlaces(day, startTime, endTime, squareRegionOfInterest, minimumStayDuration, Users) << " people" << endl;

        }

    }


    /*for (int day = 0; day < daysNum; day++) {
        cout<<endl<<"new day new life"<<endl;
        for (int userNum = 0; userNum < usersNumber; userNum++) {
            llDisplay(Users[day][userNum]);
        }
    }*/

}
























/*User user{};

    int crowd = 0;
    listPtr userCurrent;
    listPtr userPrev;
    listPtr current;
    listPtr prev;

    int timer = 0;
    userPrev = userPosition;
    userCurrent = userPrev;
    prev = userPosition;
    current = prev;

    //στιγμαίος χρονος
    int instanceSeconds = llData(current).seconds + llData(current).minutes * 60
                          + llData(current).hours * 60 * 60;


    while (userCurrent != nullptr) { //επαναληψη για χρηστες
        userCurrent = userPrev ->next;
        //οσο η στιγμαια ωρα που δινεται ειναι μικρότερη απο την τελικη ώρα που δινεται, επαναλαβε και τσεκαρε
        //συντεταγμενες καθε 30 δευτερολεπτα
            for(int i = instanceSeconds; i<=TimeInterval; i+=30) {
                 while (current != nullptr) { //επαναληψη για συντενταγμενες
                     current = prev->next;
                     int prevX = llData(prev).x;
                     int currentX = llData(current).x;

                     int prevY = llData(prev).y;
                     int currentY = llData(current).y;

                    //αρχικοποίηση λογικων
                     bool flag = false;
                     bool flagSquare = false;

                     flag = (currentX == prevX) && (currentY == prevY);



                     if (prevX < D && prevY < D && flag) { // και βρισκονται στο δοθεν region
                         flagSquare = true;
                         timer += 30; // μεταβλητη που μετραει το χρονο που βρέθηκε ο χρηστης μεσα στο region
                     } else {
                         flagSquare = false;
                     }
                     prev = current;
                 }

         if (timer <= MinimumStayDuration) {
            crowd += 1;
        }
        userPrev = userCurrent;
    }
}



    *//*
    return crowd;*/