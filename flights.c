/* 
 * CS61C Summer 2017
 * Name: Michelle Zhang, Margo Oka
 * Login: abp, afe
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "flights.h"
#include "timeHM.h"

typedef struct node {
  struct airport* airp;
  struct node *next;
} node;

typedef struct node2 {
  struct flight* flight;
  struct node2 *next;
} node2;

typedef struct flightSys  {
    // Place the members you think are necessary for the flightSys struct here.
  node* airp;
} flightSystem;

typedef struct airport_t {
    // Place the members you think are necessary for the airport struct here.
  char *name;
  node2* flights;
} airport;

typedef struct flight_t {
    // Place the members you think are necessary for the flight struct here.
  airport *dest_airport;
  timeHM_t arrival;
  timeHM_t departure;
  int cost_of_flight;
} flight;



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
    return (flightSys_t*) malloc(sizeof(flightSystem));
}


/* Given a destination airport, a departure and arrival time, and a cost, return a pointer to new flight_t. Note that this pointer must be available to use even
   after this function returns. (What does this mean in terms of how this pointer should be instantiated)?
*/

flight_t* createFlight(airport_t* dest, timeHM_t dep, timeHM_t arr, int c) {
    flight* newFlight = (flight*) malloc(sizeof(flight));
    newFlight->dest_airport = (airport*) dest;
    newFlight->departure = dep;
    newFlight->arrival = arr;
    newFlight->cost_of_flight = c;

    return (flight_t*) newFlight;
}

/*
   Frees all memory associated with this system; that's all memory you dynamically allocated in your code.
 */
void deleteSystem(flightSys_t* s) {
    // Replace this line with your code
    free(s);
}


/*
   Adds a airport with the given name to the system. You must copy the string and store it.
   Do not store "name" (the pointer) as the contents it point to may change.
 */
void addAirport(flightSys_t* s, char* name) {
    // Replace this line with your code
    node* n = s->airp;
    while(n != NULL) {
        n = n->next;
    }
    airport* newAirport = (airport*) malloc(sizeof(airport));
    strcpy(newAirport->name, name);
    
    node* newNode;
    newNode->airp = (struct airport*) newAirport;
    n->next = newNode;
}


/*
   Returns a pointer to the airport with the given name.
   If the airport doesn't exist, return NULL.
 */
airport_t* getAirport(flightSys_t* s, char* name) {
    // Replace this line with your code
    node* n = s->airp;
    while (n != NULL) {
      airport* a = (airport*)(n->airp);
      if (strcmp(a->name, name) != 0) {
        return (airport_t*) n;
      }
      n = n->next;
    }
    return NULL;
}


/*
   Print each airport name in the order they were added through addAirport, one on each line.
   Make sure to end with a new line. You should compare your output with the correct output
   in flights.out to make sure your formatting is correct.
 */
void printAirports(flightSys_t* s) {
    // Replace this line with your code
    node* n = s->airp;
    while(n != NULL) {
        airport* a = (airport*)(n->airp);
        printf("%s/n", a->name);
        n = n->next;
    }
}


/*
   Adds a flight to src's schedule, stating a flight will leave to dst at departure time and arrive at arrival time.
 */
void addFlight(airport_t* src, airport_t* dst, timeHM_t* departure, timeHM_t* arrival, int cost) {
    // Replace this line with your code
    flight* newFlight = (flight*) createFlight(dst, *departure, *arrival, cost);
    node2* curFlight = ((airport*)src)->flights;
    while (curFlight != NULL) {
      curFlight = curFlight->next;
    }
    curFlight->flight = (flight_t*) newFlight;
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
    airport* a = (airport*)s;
    printf("%s/n", a->name);
    node2* n = a->flights;
    while(n != NULL) {
        flight* f = (flight*)n->flight;
        printf("%s ", f->dest_airport->name);
        printTime(&f->arrival);
        printTime(&f->departure);
        printf("$%c/n", f->cost_of_flight);
        n = n->next;
    }
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
    node2* flights = ((airport*)src)->flights;
    int lowest;

    //find number of flights
    int number_of_flights = 0;
    if (flights != NULL) {
      node2* cur = flights;
      while (cur != NULL) {
        cur = cur->next;
        number_of_flights++;
      }

      //get list of cheapest flights (of the same cost)
      flight cheapest[number_of_flights];

      cur = flights;
      int cheapestCounter = 0;
      while (cur!= NULL) {
        if (isAfter(departure, now)) {
          if (lowest > ((flight*)(cur->flight))->cost_of_flight) {
            flight cheapest [number_of_flights];
            lowest = ((flight*)(cur->flight))->cost_of_flight;
            number_of_flights = 0;
          }
          if (((flight*)(cur->flight))->cost_of_flight == lowest) {
            cheapest[cheapestCounter] = *((flight*)(cur->flight));
            cheapestCounter++;
          }
        }
      }

      //iterate through cheapest flights to find the earliest departing one
      flight* earliest = &cheapest[0];
      for (int i = 0; i < cheapestCounter; i++) {
        if (isAfter(cheapest[i]->departure, earliest->departure)) {
          earliest = &cheapest[i];
        }
      }

      departure = earliest->departure;
      arrival = earliest->arrival;
      cost = earliest->cost;
      return true;
    }

    
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
