#ifndef COVID19_OPERATIONS_H
#define COVID19_OPERATIONS_H
#include "LinkedList.h"

// Παραγωγή ενός τυχαίου αριθμού από 50 έως 100 για τις διαστάσεις του πλέγματος
const int D = rand() % 50 + 50;

// Ορισμός της απόστασης μεταξύ κάθε στοιχείου του πλέγματος σε μέτρα
const int gridDistance = 20;

// Ορισμός χρηστών
const int usersNumber = 50;

// Ορισμός ημερών
const int daysNum = 3;

bool possibleCOVID_19Infection(listPtr userTrajectory, int day, listPtr allUsers[], int usersNumber);
void repair(listPtr userTrajectory);
int findCrowdedPlaces(int day, int startSeconds, int endSeconds, int squareRegionOfInterest, int minimumStayDuration, listPtr users[][usersNumber]);
void summarizeTrajectory();

#endif