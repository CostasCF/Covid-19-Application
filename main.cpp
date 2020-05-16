#include <iostream>
#include <ctime>
#include <cmath>

#include "User.h"
#include "LinkedList.h"
#include "COVID19_Operations.h"

using namespace std;

// 33.3% πιθανότητα να κουνηθεί ο χρήστης
bool userWillMove() {
    int random = rand() % 3;
    return random == 1;
}

// 10% πιθανότητα να μη δουλέψει το gps και να χαθεί μία χρονική στιγμή
bool gpsWorked() {
    int random = rand() % 10;
    return random != 1;
}

// Οι παρακάτω συναρτήσεις επιστρέφουν μία τυχαία τιμή μέσα στο πλέγμα
int getRandomX(int dimension) {
    return rand() % dimension;
}

int getRandomY(int dimension) {
    return rand() % dimension;
}

// Αυτή η συνάρτηση επιστρέφει μία ταχύτητα από 3 έως 6 χιλιόμετρα άνα ώρα
int getRandomSpeed() {
    return rand() % 3 + 3; // Χιλιόμετρα την ώρα
}

// Οι επόμενες 4 συναρτήσεις χρησιμοποιούνται στην κίνηση του χρήστη και συγκεκριμένα για την αυξομείωση των
// συντεταγμένων ανάλογα με τη θέση στην οποία βρίσκεται ο χρήστης και σε αυτή που θέλει να πάει

// Στην περίπτωση που το x στο οποίο θέλει να πάει είναι μεγαλύτερο από αυτό στο οποίο βρίσκεται πρέπει το χ του χρήστη
// να αυξηθεί
void increaseX(int &x, int desiredX, double &meterCounterX, double userSpeedM_30sec, int gridDistance) {
    meterCounterX += userSpeedM_30sec;
    while (meterCounterX >= gridDistance && x < desiredX) {
        x += 1;
        meterCounterX -= gridDistance;
    }
}

// Στην περίπτωση που το x στο οποίο θέλει να πάει είναι μικρότερο από αυτό στο οποίο βρίσκεται πρέπει το χ του χρήστη
// να μειωθεί
void decreaseX(int &x, int desiredX, double &meterCounterX, double userSpeedM_30sec, int gridDistance) {
    meterCounterX += userSpeedM_30sec;
    while (meterCounterX >= gridDistance && x > desiredX) {
        x -= 1;
        meterCounterX -= gridDistance;
    }
}

// Στην περίπτωση που το Υ στο οποίο θέλει να πάει είναι μεγαλύτερο από αυτό στο οποίο βρίσκεται πρέπει το Υ του χρήστη
// να αυξηθεί
void increaseY(int &y, int desiredY, double &meterCounterY, double userSpeedM_30sec, int gridDistance) {
    meterCounterY += userSpeedM_30sec;
    while (meterCounterY >= gridDistance && y < desiredY) {
        y += 1;
        meterCounterY -= gridDistance;
    }
}

// Στην περίπτωση που το Υ στο οποίο θέλει να πάει είναι μικρότερο από αυτό στο οποίο βρίσκεται πρέπει το Υ του χρήστη
// να μειωθεί
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
        case 1: // Αν το x και το y του χρήστη είναι μικρότερα από το x και το y στα οποία θέλει να πάει

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

        case 2: // Αν το χ του χρήστη είναι μικρότερο από το χ που θέλει να πάει,
                // αλλά το y του μεγαλύτερο από το y που θέλει να πάει

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
        case 3: // Αν το χ του χρήστη είναι μεγαλύτερο από το χ που θέλει να πάει,
                // αλλά το y του μικρότερο από το y που θέλει να πάει

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

        case 4: // Αν το x και το y του χρήστη είναι μεγαλύτερα από το x και το y στα οποία θέλει να πάει

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



// ------------------------------------------------- MAIN ------------------------------------------------- \\



int main() {

    // srand ώστε να μην παράγονται οι ίδιοι αριθμοί κάθε φορά που τρέχει το πρόγραμμα
    srand(time(nullptr));

    // Δήλωση ενός δισδιάστατου πίνακα του τύπου listPtr (δηλαδή του πρώτου δείκτη κόμβου μιας απλά συνδεδεμένης λίστας που κάθε
    // γραμμή αντιστοιχεί σε μία μέρα και περιέχει μία απλά συνδεδεμένη λίστα για την τροχιά του κάθε χρήστη εκείνη τη μέρα
    listPtr Users[daysNum][usersNumber];

    for (int day = 0; day < daysNum; day++) {
        for (int userNum = 0; userNum < usersNumber; userNum++) {
            // Αρχικοποίηση όλων των συνδεδεμένων λίστών (όπου κάθε μία από αυτές περιέχει την τροχιά ενός χρήστη) με την τιμή null
            llInit(&Users[day][userNum]);
        }
    }

    // Επανάληψη για τις μέρες
    for (int day = 0; day < daysNum; day++) {

        cout << "--------------------- DAY " << day + 1 << " ---------------------" << endl << endl;

        for (int userNum = 0; userNum < usersNumber; userNum++) {

            // Δημιουργία αντικειμένου User
            User user{};

            // Παραγωγή τυχαίας τοποθεσίας για τη γέννηση νέου χρήστη
            user.x = getRandomX(D);
            user.y = getRandomY(D);

            // Μεταβλητές που υποδεικνύουν την περιοχή στην οποία θέλει να πάει ο χρήστης
            int desiredX = user.x;
            int desiredY = user.y;

            // Ανάμεσα σε κάθε κελί του πλέγματος υπάρχει μία απόσταση gridDistance(δηλωμένο στο COVID19_Operations.h).
            // Συνεπώς για την κίνηση των χρηστών χρειάζεται μία μεταβλητή (για το χ και y αντίστοιχα) η οποία
            // αν ξεπερνάει το gridDistance να προχωράει ο χρήστης

            double meterCounterX = 0;
            double meterCounterY = 0;

            // Ταχύτητα του χρήστη
            int userSpeedKm_h; // σε χιλιόμετρα ανά ώρα
            double userSpeedM_30sec; // Σε μέτρα ανά 30 δευτερόλεπτα (ώστε να μπορούμε να μετρήσουμε ευκολότερα την απόσταση)

            // Ορισμός μεταβλητής που υποδεικνύει εάν ο χρήστης βρίσκεται σε κίνηση ή όχι
            bool userMoving = false;

            // Ορισμός ταυτότητας και κατάστασης μόλυνσης κάθε χρήστη
            // Ταυτότητα
            user.id = userNum + 1;
            // Κατάστασης μόλυνσης
            user.setInfectionStatus();  // Στο πρόγραμμα δεν υπάρχει λίστα με COVID-19 patients, το αν είναι μολυσμένος ή
                                        // όχι ένας χρήστης καθορίζεται από τη μεταβλητή infected του struct User

            // Χρήση μεταβλητών για δευτερόλεπτα, λεπτά και ώρες, ώστε ο χρόνος να
            // εμφανίζεται με πιο όμορφο τρόπο
            int seconds = 0;
            int minutes = 0;
            int hours = 0;

            // Int που χρησιμοποιείται σε ένα switch παρακάτω ώστε να ξεκινήσει η σωστή διαδικασία
            // με βάση την τοποθεσία του χρήστη σε σχέση με την τοποθεσία που θέλει να πάει
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


                // Εάν ο χρήστης δεν κινείται ήδη έχει μία πιθανότητα να αποφασίσει να κινηθεί σε νέα τοποθεσία
                // ή να παραμείνει στάσιμος
                if (!userMoving && userWillMove()) {
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

                // H gpsWorked επιστρέφει true αν το gps δούλεψε, αλλιώς false
                if (gpsWorked()) {
                    // Εισαγωγή στη λίστα του συγκεκριμένου χρήστη της συγκεκριμένης μέρας
                    // της πληροφορίας περί απόστασης, χρόνου, id και κατάστασης μόλυνσης
                    llInsertEnd(&Users[day][userNum], user);
                }
                seconds += 30;

            }


        }

        // Επανάληψη για όλους τους χρήστες
        for (int userNum = 0; userNum < usersNumber; userNum++) {
            // Κάλεσμα repair για τη συμπλήρωση των χαμένων στιγμών λόγω του gps
            repair(Users[day][userNum]);
        }

        // Κάλεσμα possible COVID-19 Infection

        // Λογική μεταβλητή για την εμφάνιση του κατάλληλου μηνύματος στην περίπτωση που κανένας χρήστης δεν πρόκειται
        // να έχει μολυνθεί
        bool atLeast1UserMayBeSick = false;

        // Επανάληψη για όλους τους χρήστες
        for (int userNum = 0; userNum < usersNumber; userNum++) {
            // Επειδή η κάθε λίστα περιέχει και τους υγιείς και τους ασθενείς πρέπει σε αυτό το στάδιο να γίνει
            // διαχωρισμός και να καλείται η possible COVID-19 Infection μόνο για τους υγιείς
            bool userIsSick = llData(Users[day][userNum]).infected;

            if (!userIsSick) {
                bool userMayBeSick = possibleCOVID_19Infection(Users[day][userNum], day, Users);
                if (userMayBeSick) {
                    atLeast1UserMayBeSick = true;
                    cout << "User " << userNum+1 << " was dangerously close to a COVID-19 patient and he may be sick" << endl;
                }
            }
        }

        if (!atLeast1UserMayBeSick) {
            cout << "Noone was dangerously close to a COVID-19 patient today" << endl;
        }

        int answer;
        cout << endl << "Do you want to check for crowded places? Press 1 for yes, or 0 for no" << endl;
        cin >> answer;

        if (answer == 1) {

            int startTime = rand() % 82800; // Τυχαία τιμή από 0 δευτερόλεπτα μέχρι 23 ώρες
            int endTime = rand() % (86370-startTime) + startTime; // Τυχαία τιμή από το startTime μέχρι το τέλος της μέρας

            int squareRegionOfInterest = rand() % (D-20) + 10; // Τυχαία τιμή από 10 μέχρι D-20 (όπου D οι διαστάσεις του πλέγματος)

            int minimumStayDuration = rand() % 1800 + 180; // Τυχαία τιμή από 3 λεπτά μέχρι μισή ώρα

            cout << "Based on the provided data there were " <<
            findCrowdedPlaces(day, startTime, endTime, squareRegionOfInterest, minimumStayDuration, Users) << " people in the given area" << endl << endl;

        }

    }

    // Εκτέλεση της Summarize trajectory την 7η μέρα για την 1η
    // H summarize trajectory έχει κάποιο error και γι αυτό μένει στα σχόλια
    /*for (int userNum = 0; userNum < usersNumber; userNum++) {
        summarizeTrajectory(Users[0][userNum]);
    }*/

    // H παρακάτω επανάληψη συνίσταται για τη δοκιμή της summarizeTrajectory καθώς εμφανίζει μόνο την πρώτη μέρα
    /*for (int userNum = 0; userNum < usersNumber; userNum++) {
        llDisplay(Users[0][userNum]);
    }*/

    // Η παρακάτω επανάληψη εμφανίζει την πορεία όλων των χρηστών για κάθε μέρα. Χρησιμοποιήθηκε κυρίως για
    // δοκιμαστικούς λόγους και γι αυτό βρίσκεται σε σχόλια

    /*for (int day = 0; day < daysNum; day++) {
        for (int userNum = 0; userNum < usersNumber; userNum++) {
            llDisplay(Users[day][userNum]);
        }
    }*/

    return 0;
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