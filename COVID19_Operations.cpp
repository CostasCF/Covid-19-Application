#include <cmath>

#include "COVID19_Operations.h"

// Επειδή δεν υπάρχει ξεχωριστή λίστα με ασθενείς περνάει όλος ο πίνακας και στη συνέχεια γίνεται ο διαχωρισμός
bool possibleCOVID_19Infection(listPtr userTrajectory, int day, listPtr allUsers[][usersNumber]) {

    // Επανάληψη για όλους τους χρήστες:
    for (int userID = 0; userID < usersNumber; userID++) {
        // if για να αποφευχθεί η χρήση του userTrajectory όταν είναι null
        if (userTrajectory != nullptr) {

            // Φιλτράρισμα των ασθενών χρηστών ώστε να συγκριθούν μόνο αυτοί με τον δοθέντα υγιή χρήστη
            bool userIsSick = llData(allUsers[day][userID]).infected;

            if (userIsSick) {

                int seconds = 0;
                int minutes = 0;
                int hours = 0;

                int R = rand() % 4 + 2; // random τιμή από 2 μέχρι 6 για την ακτίνα
                int T1 = rand() % 1770 + 30; // random τιμή από 30 δευτερόλεπτα μέχρι μισή ώρα
                int T2 = rand() % 21600 + 3600; // random τιμή από 1 ώρα μέχρι 6 ώρες

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

                    // Δημιουργεία νέου pointer για την παρακάτω επανάληψη ώστε να μην πειραχθεί ο
                    listPtr healthyUserTrajectory = userTrajectory;

                    // Επανάληψη που κρατάει όσο ο μέγιστος χρόνος που μπορεί να περάσει, ώστε να μολυνθεί ένας υγιής
                    // χρήστης ο οποίος βρέθηκε εντός ακτίνας R από τις συντεταγμένες του ασθενή για τουλάχιστον Τ1 χρόνο
                    for (int t2Seconds = 0; t2Seconds < T2; t2Seconds += 30) {

                        if (healthyUserTrajectory != nullptr) {
                            // Αποθήκευση των συντεταγμένων του χρήστη
                            int userX = llData(healthyUserTrajectory).x;
                            int userY = llData(healthyUserTrajectory).y;

                            // Απόσταση μεταξυ του μολυσμένου χρήστη και του υγιούς
                            double distance = sqrt(pow(infectedUserX - userX, 2) + pow(infectedUserY - userY, 2));

                            // Αν η απόσταση είναι εντός της ακτίνας
                            if (distance <= R) {
                                // Αυξάνονται τα δευτερόλεπτα και εάν φτάσουν ή ξεπεράσουν την ελάχιστη διάρκεια
                                // ο χρήστης ίσως έχει μολυνθεί
                                secondsStayed += 30;
                                if (secondsStayed >= T1) {
                                    return true;
                                }
                            } else {
                                secondsStayed = 0;
                            }

                            // Μετακίνηση στον επόμενο κόμβο της λίστας
                            healthyUserTrajectory = healthyUserTrajectory->next;
                        } else {
                            break;
                        }
                    }

                    seconds += 30;

                    if (userTrajectory != nullptr) {
                        userTrajectory = userTrajectory->next;
                    } else {
                        break;
                    }
                }
            }
        } else {
            break;
        }
    }
    return false;
}


int findCrowdedPlaces(int day, int startSeconds, int endSeconds, int squareRegionOfInterest, int minimumStayDuration, listPtr users[][usersNumber]) {

    // Μετρητής των χρηστών
    int userCounter = 0;

    for (int userNum = 0; userNum < usersNumber; userNum++) {

        listPtr userTrajectory = users[day][userNum]; // Pointer στην αρχή της λίστας (τροχιάς) του userNum χρήστη για την day μέρα

        // If για την αποφυγή SIGSEGV (Segmentation fault)
        if (userTrajectory != nullptr) {

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


// Επειδή υπάρχει πίνακας με τις μέρες και τους χρήστες δεν απαιτείται η μέρα σαν όρισμα
void repair(listPtr userTrajectory)  {
    // Δημιουργεία δύο δεικτών στην αρχή της λίστας. Έναν για το τωρινό στοιχείο κι έναν για το προηγούμενο
    listPtr current;
    listPtr prev;

    prev = userTrajectory;
    current = prev;

    // Όσο η λίστα έχει συνέχεια
    while (current != nullptr) {
        current = prev->next;

        // if για την αποφυγή crash
        if (current != nullptr) {
            // Βρίσκει τη χρονική διαφορά μεταξύ δύο διαδοχικών καταγεγραμμένων στιγμών
            int prevInstanceSeconds = llData(prev).seconds + llData(prev).minutes * 60
                                      + llData(prev).hours * 60 * 60;
            int instanceSeconds = llData(current).seconds + llData(current).minutes * 60
                                  + llData(current).hours * 60 * 60;
            int secondsDiff = instanceSeconds - prevInstanceSeconds;

            // Αν η διαφορά είναι μεγαλύτερη του 30 τότε τουλάχιστον μία χρονική στιγμή δεν έχει καταγραφεί
            if (secondsDiff > 30) {
                // Αποθήκευση των συντεταγμένων
                int prevX = llData(prev).x;
                int currentX = llData(current).x;
                double meterCounterX = 0;

                int prevY = llData(prev).y;
                int currentY = llData(current).y;
                double meterCounterY = 0;

                // Δημιουργεία αντικειμένου user για να προστεθεί στο νέο κόμβο που θα δημιουργηθεί
                User user{};

                // Αρχικοποίηση στις συντεταγμένες του προηγούμενου κόμβου
                user.x = prevX;
                user.y = prevY;

                // Το id και το infected παραμένουν σταθερά
                user.id = llData(prev).id;
                user.infected = llData(prev).infected;

                // Χρήση μαθηματικού τύπου της απόστασης δύο σημείων
                double realDistance = sqrt(pow((llData(current).x - llData(prev).x), 2)
                                           + pow((llData(current).y - llData(prev).y), 2)) * gridDistance;

                double userSpeed = realDistance / 30;   // Εύρεση της ταχύτητας του χρήστη διαιρώντας την απόσταση με τη
                                                        // χρονική απόσταση

                // Μετατροπή km/h σε μέτρα ανά 30 δευτερόλεπτα
                double userSpeedM_30sec = userSpeed*1000/60/2;

                // Η επανάληψη αυτή υπάρχει στην περίπτωση που λείπουν περισσότεροι από έναν κόμβοι
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

                    // Παρόμοια διαδικασία με αυτή στη main για την κίνηση του χρήστη προς τη σωστή κατεύθυνση
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

                    // Δημιουργεία νέου κόμβου μετά τον προηγούμενο
                    llInsertAfter(prev, user);

                    // Αυξάνεται το prev στην περίπτωση η διαφορά των δευτερολέπτων είναι μεγαλύτερη του 60
                    prev = prev->next;
                }
            }
        }
        // prev = current ώστε να προχωρήσει το prev στον επόμενο κόμβο και στη συνέχεια το current να προχωρήσει και αυτό
        prev = current;

    }
}

// Για όρισμα χρησιμοποιείται και πάλι μόνο το userTrajectory λόγω του δισδιάστατου πίνακα με τις τροχιές των χρηστών
void summarizeTrajectory(listPtr userTrajectory) {
    int R = rand() % 5 + 1; // Τυχαία τιμή από 1 μέχρι 5 για την ακτίνα

    // Πρώτο στίγμα
    int userX = llData(userTrajectory).x;
    int userY = llData(userTrajectory).y;

    listPtr current = userTrajectory;
    listPtr prev = userTrajectory;
    bool coordinatesInsideR = true;
    while (coordinatesInsideR) {

        if (current->next != nullptr) {

            current = prev->next;
            // Συντεταγμένες της current χρονικής στιγμής
            int currentX = llData(current).x;
            int currentY = llData(current).y;

            // Χρήση του μαθηματικού τύπου της απόστασης
            double distance = sqrt(pow(currentX - userX, 2) + pow(currentY - userY, 2));

            // Αν η απόσταση είναι μικρότερη της ακτίνας τότε ο κόμβος διαγράφεται
            if (distance < R) {
                llDeleteAfter(prev, &prev->data);
            } else {
                userX = llData(current).x;
                userY = llData(current).y;
                coordinatesInsideR = false;
            }

            // Επόμενος κόμβος εφόσον υπάρχει
            prev = current;

        } else {
            break;
        }
    }
}