#include <cmath>

#include "COVID19_Operations.h"

bool possibleCOVID_19Infection(listPtr userTrajectory, int day, listPtr *allUsers[]) {
    for (int userID = 0; userID < usersNumber; userID++) {
        bool userIsSick = llData(allUsers[day][userID]).infected;
        if (userIsSick) {

            int seconds = 0;
            int minutes = 0;
            int hours = 0;

            int R = rand() % 5 + 1; // random τιμή από 1 μέχρι 5
            int T1 = rand() % 10800 + 1; // random τιμή από 1 δευτερόλεπτο μέχρι 3 ώρες
            int T2 = rand() % 21600 + 3600; // random τιμή από 1 μέχρι 6 ώρες

            int secondsStayed = 0;

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

                // Αποθήκευση των συντεταγμένων του μολυσμένου χρήστη για σύγκριση με τις συντεταγμένες των υγιών χρηστών
                int infectedUserX = llData(allUsers[day][userID]).x;
                int infectedUserY = llData(allUsers[day][userID]).y;

                // Επανάληψη που κρατάει όσο ο μέγιστος χρόνος που μπορεί να περάσει, ώστε να μολυνθεί ένας υγιής
                // χρήστης ο οποίος βρέθηκε εντός ακτίνας R από τις συντεταγμένες του ασθενή για τουλάχιστον Τ1 χρόνο
                for (int t2Seconds = 0; t2Seconds < T2; t2Seconds += 30) {

                    listPtr healthyUserTrajectory = allUsers[day][userID];

                    // Αποθήκευση των συντεταγμένων του χρήστη
                    int userX = llData(healthyUserTrajectory).x;
                    int userY = llData(healthyUserTrajectory).y;

                    double distance = sqrt(pow(infectedUserX - userX, 2) + pow(infectedUserY - userY, 2));

                    if (distance <= R) {
                        secondsStayed += 30;
                        if (secondsStayed >= T1) {
                            cout << "Ο χρήστης " << llData(healthyUserTrajectory).id << " ίσως έχει μολυνθεί." << endl;
                            return true;
                        }
                    } else {
                        secondsStayed = 0;
                    }

                    healthyUserTrajectory = healthyUserTrajectory->next;
                }

                seconds += 30;

                userTrajectory = userTrajectory->next;
            }
        }
    }
    return false;
}


int findCrowdedPlaces(int day, int startSeconds, int endSeconds, int squareRegionOfInterest, int minimumStayDuration, listPtr users[][usersNumber]) {

    // Μετρητής των χρηστών
    int userCounter = 0;

    for (int userNum = 0; userNum < usersNumber; userNum++) {
        listPtr userTrajectory;

        // If για την αποφυγή SIGSEGV (Segmentation fault)
        if (userTrajectory != nullptr) {
            userTrajectory = users[day][userNum]; // Pointer στην αρχή της λίστας (τροχιάς) του userNum χρήστη για την day μέρα

            int timeInSeconds;  // Χρησιμοποιείται για να μετατραπεί η μορφή της ώρας απο ώρες, λέπτα και δευτερόλεπτα
            // σε δευτερόλεπτα

            // Συντεταγμένες του χρήστη
            int userX;
            int userY;

            // H συγκεκριμένη επανάληψη κρατάει μέχρι να βρεθεί η χρονική στιγμή η οποία
            // δόθηκε από το χρήστη και να αποθηκευτούν οι αντίστοιχες συντεταγμένες
            while (true) {

                // Ανάκτηση της ώρα σε ώρες, λεπτά και δευτερόλεπτα
                int userSeconds = llData(userTrajectory).seconds;
                int userMinutes = llData(userTrajectory).minutes;
                int userHours = llData(userTrajectory).hours;

                // Μετατροπή σε δευτερόλεπτα
                timeInSeconds = userSeconds + userMinutes * 60 + userHours * 60 * 60;

                if (timeInSeconds >= startSeconds) {
                    break;
                } else {
                    userTrajectory = userTrajectory->next; // Μετάβαση στον επόμενο κόμβο εφόσον δεν έχει βρεθεί η σωστή ώρα
                }

            }

            bool userStayedInRegion = true; // Λογική μεταβλητή που υποδικνύει εάν ο χρήστης παρέμεινε στην περιοχή ή όχι
            // Αλλάζει στη συνέχεια εάν διαπιστωθεί ότι δεν παρέμεινε

            // Επανάληψη από την αρχή μέχρι το τέλος της χρονικής διάρκειας που έδωσε ο χρήστης
            for (int i = startSeconds; i <= endSeconds; i += 30) {

                listPtr temp = userTrajectory; // Χρησιμοποιείται για τη διάσχιση της λίστας χωρίς να αλλάζει το userTrajectory

                // Αποθήκευση των συντεταγμένων
                userX = llData(temp).x;
                userY = llData(temp).y;

                // Εάν ο υπολοιπόμενος χρόνος είναι αρκετός για να μετρηθεί ένας χρήστης τότε ξεκινάει η διαδικασία ελέγχου
                if (endSeconds - i >= 0) {
                    for (int j = 0; j <= minimumStayDuration; j += 30) {
                        // Εάν ο χρήστης βγει από το squareRegionOfInterest πριν συμπληρωθεί το minimumStayDuration
                        // τότε σπάει η επανάληψη με το minimumStayDuration και το πρόγραμμα συνεχίζει αυξάνοντας το i,
                        // το οποίο είναι τα δευτερόλεπτα βάσης και ελέγχει το επόμενο χρονικό περιθώριο
                        if (userX > squareRegionOfInterest || userY > squareRegionOfInterest) {
                            userStayedInRegion = false;
                            break;
                        }
                        if (temp != nullptr)
                            temp = temp->next; // Πηγαίνει στον επόμενο κόμβο
                        else
                            break;
                    }
                }

                // Εάν ο χρήστης παρέμεινε στο square region of interest κατά τουλάχιστον minimumStayDuration τότε ο μετρητής
                // αυξάνεται. Διαφορετικά το userTrajectory δείχνει στον επόμενο κόμβο.
                // Η διαδικασία επαναλαμβάνεται μέχρι ο χρήστης να μείνει κατά το minimumStayDuration στο squareRegionOfInterest
                // ή να τελειώσει ο χρόνος και στη συνέχεια προχωράει στον επόμενο χρήστη
                if (userStayedInRegion) {
                    userCounter++;
                    break;
                } else if (userTrajectory != nullptr) {
                    userTrajectory = userTrajectory->next;
                } else
                    break;

            }
        } else {
            break;
        }
    }
    return userCounter;
}



void repair(listPtr userTrajectory)  {
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
                // Μετατροπή km/h σε μέτρα ανά 30 δευτερόλεπτα
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