/* 
 * CS61C Summer 2017
 * Name: Margo Oka, Michelle Zhang
 * Login: abp, afe
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "flights.h"
#include "timeHM.h"

struct flightSys {
    // Place the members you think are necessary for the flightSys struct here.
};

struct airport {
    // Place the members you think are necessary for the airport struct here.
};

struct flight {
    // Place the members you think are necessary for the flight struct here.
};

/*
   This should be called if memory allocation failed.
 */
static void allocation_failed() {
    fprintf(stderr, "Out of memory.\n");
    exit(EXIT_FAILURE);
}


/*
   Creates and initializes a flight system, which stores the flight schedules of several airports.
   Returns a pointer to the system created.
 */
flightSys_t* createSystem() {
    // Replace this line with your code
    return NULL;
}


/* Given a destination airport, a departure and arrival time, and a cost, return a pointer to new flight_t. Note that this pointer must be available to use even
   after this function returns. (What does this mean in terms of how this pointer should be instantiated)?
*/

flight_t* createFlight(airport_t* dest, timeHM_t dep, timeHM_t arr, int c) {
   // Replace this line with your code
   return NULL;
}

/*
   Frees all memory associated with this system; that's all memory you dynamically allocated in your code.
 */
void deleteSystem(flightSys_t* s) {
    // Replace this line with your code
}


/*
   Adds a airport with the given name to the system. You must copy the string and store it.
   Do not store "name" (the pointer) as the contents it point to may change.
 */
void addAirport(flightSys_t* s, char* name) {
    // Replace this line with your code
}


/*
   Returns a pointer to the airport with the given name.
   If the airport doesn't exist, return NULL.
 */
airport_t* getAirport(flightSys_t* s, char* name) {
    // Replace this line with your code
    return NULL;
}


/*
   Print each airport name in the order they were added through addAirport, one on each line.
   Make sure to end with a new line. You should compare your output with the correct output
   in flights.out to make sure your formatting is correct.
 */
void printAirports(flightSys_t* s) {
    // Replace this line with your code
}


/*
   Adds a flight to src's schedule, stating a flight will leave to dst at departure time and arrive at arrival time.
 */
void addFlight(airport_t* src, airport_t* dst, timeHM_t* departure, timeHM_t* arrival, int cost) {
    // Replace this line with your code
}


/*
   Prints the schedule of flights of the given airport.

   Prints the airport name on the first line, then prints a schedule entry on each 
   line that follows, with the format: "destination_name departure_time arrival_time $cost_of_flight".

   You should use printTime (look in timeHM.h) to print times, and the order should be the same as 
   the order they were added in through addFlight. Make sure to end with a new line.
   You should compare your output with the correct output in flights.out to make sure your formatting is correct.
 */
void printSchedule(airport_t* s) {
    // Replace this line with your code
}


/*
   Given a src and dst airport, and the time now, finds the next flight to take based on the following rules:
   1) Finds the cheapest flight from src to dst that departs after now.
   2) If there are multiple cheapest flights, take the one that arrives the earliest.

   If a flight is found, you should store the flight's departure time, arrival time, and cost in departure, arrival, 
   and cost params and return true. Otherwise, return false. 

   Please use the function isAfter() from time.h when comparing two timeHM_t objects.
 */
bool getNextFlight(airport_t* src, airport_t* dst, timeHM_t* now, timeHM_t* departure, timeHM_t* arrival, int* cost) {
    // Replace this line with your code
    return false;
}

/* Given a list of flight_t pointers (flight_list) and a list of destination airport names (airport_name_list), first confirm that it is indeed possible to take these sequences of flights,
   (i.e. be sure that the i+1th flight departs after or at the same time as the ith flight arrives) (HINT: use the isAfter and isEqual functions).
   Then confirm that the list of destination airport names match the actual destination airport names of the provided flight_t struct's.
   sz tells you the number of flights and destination airport names to consider. Be sure to extensively test for errors (i.e. if you encounter NULL's for any values that you might expect to
   be non-NULL, return -1).

   Return from this function the total cost of taking these sequence of flights. If it is impossible to take these sequence of flights, if the list of destination airport names
   doesn't match the actual destination airport names provided in the flight_t struct's, or if you run into any errors mentioned previously or any other errors, return -1.
*/
int validateFlightPath(flight_t** flight_list, char** airport_name_list, int sz) {
    // Replace this line with your code
    return -1;
}
