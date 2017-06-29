/* 
 * CS61C Summer 2017
 * Name: Michelle Zhang, Margo Oka
 * Login: abp, afe
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "flights.h"
#include "timeHM.h"

typedef struct node {
  struct airport * airp;
  struct node * next;
} node;

typedef struct node2 {
  struct flight * flight;
  struct node2 * next;
} node2;

struct flightSys  {
  node* airp;
};

struct airport {
  char * name;
  node2 * flights;
};

struct flight {
  airport_t *dest_airport;
  timeHM_t arrival;
  timeHM_t departure;
  int cost_of_flight;
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
    flightSys_t* s = (flightSys_t*) malloc(sizeof(flightSys_t));
    if (!s) {
        allocation_failed();
    }
    s->airp = (node*) malloc(sizeof(node));
    if (!s->airp) {
        allocation_failed();
    }
    s->airp->airp = NULL;
    s->airp->next = NULL;
    return s;
}


/* Given a destination airport, a departure and arrival time, and a cost, return a pointer to new flight_t. Note that this pointer must be available to use even
   after this function returns. (What does this mean in terms of how this pointer should be instantiated)?
*/

flight_t* createFlight(airport_t* dest, timeHM_t dep, timeHM_t arr, int c) {
    if (!dest) {
        printf("null input\n");
        return NULL;  
    }
    flight_t* newFlight = (flight_t*) malloc(sizeof(flight_t));
    if (!newFlight) {
        allocation_failed();
    }
    newFlight->dest_airport = dest;
    newFlight->departure = dep;
    newFlight->arrival = arr;
    newFlight->cost_of_flight = c;
    return newFlight;
}

/*
   Frees all memory associated with this system; that's all memory you dynamically allocated in your code.
 */
void deleteSystem(flightSys_t* s) {
    if (!s->airp) {
        free(s);
	      return;
    }
    node* n = s->airp;
    while(n) {
        if (!n->airp) {
          free(n);
          break;
        } 
        node2* n2 = n->airp->flights;
        while(n2) {
            if (n2->flight) {
                free(n2->flight);
                node2* temp2 = n2->next;
                free(n2);
                n2 = temp2;
            }    
            else {
              free(n2);
              break;
            }   
        }
        if (n->airp) {
            free(n->airp->name);
            free(n->airp);  
            node* temp = n->next;
            free(n);
            n = temp;
        }    
           
    }
    free(s);
}


/*
   Adds a airport with the given name to the system. You must copy the string and store it.
   Do not store "name" (the pointer) as the contents it point to may change.
 */
void addAirport(flightSys_t* s, char* name) {
    if(!s || !name) {
        return;
    } 
    node* n = s->airp;
    while(n->airp) {
        n = n->next;
    }
    /* Make a new airport. */
    airport_t* newAirport = (airport_t*) malloc(sizeof(airport_t));
    if (!newAirport) {
      
        allocation_failed();
    }

    newAirport->name = strdup(name);
    newAirport->flights = (node2*) malloc(sizeof(node2));

    if(!newAirport->flights) {
        allocation_failed();
    }
    newAirport->flights->flight = NULL;
    newAirport->flights->next = NULL;
    n->airp = newAirport;
    
    node* nextNode = (node*) malloc(sizeof(node));
    if (!nextNode) {
        allocation_failed();
    }
    n->next = nextNode;
    nextNode->next = NULL;
    nextNode->airp = NULL;
    
}


/*
   Returns a pointer to the airport with the given name.
   If the airport doesn't exist, return NULL.
 */
airport_t* getAirport(flightSys_t* s, char* name) {
    node* n = s->airp;
    while (n != NULL) {
      airport_t* a = n->airp;
      if (!a) {
        return NULL;
      }
      if (strcmp(a->name, name) == 0) {
        return a;
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
    if (!s) {
      printf("null input\n");
      return;
    }
    node* n = s->airp;
    while(n != NULL) {   
        airport_t* a = n->airp;
        if (!a) 
            return;
        printf("%s\n", a->name);
        n = n->next;
    }
}


/*
   Adds a flight to src's schedule, stating a flight will leave to dst at departure time and arrive at arrival time.
 */
void addFlight(airport_t* src, airport_t* dst, timeHM_t* departure, timeHM_t* arrival, int cost) {
    flight_t* f = createFlight(dst, *departure, *arrival, cost);
    node2* n = src->flights;
    while (n->flight != NULL) {
        n = n->next;
    }
    n->flight = f;
    node2* nextNode = (node2*) malloc(sizeof(node2));
    if (!nextNode) {
        allocation_failed();
    }
    n->next = nextNode;
    nextNode->next = NULL;
    nextNode->flight = NULL;
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
    if (!s) {
      printf("null input\n");
      return;
    }
    printf("%s\n", s->name);
    node2* n = s->flights;
    while(n->flight != NULL) {
        flight_t* f = n->flight;
        printf("%s ", f->dest_airport->name);
        printTime(&f->departure);
        printf(" ");
        printTime(&f->arrival);
        printf(" $%d\n", f->cost_of_flight);
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
    
    if (!src || !dst || !now || !departure || !arrival || !cost) {
        return false;
    }

    //First find the number and cost of the cheapest flight(s)
    node2 * n = src->flights;
    
    if (!n || !n->flight) {
        return false;
    }
    int num_c_flights = 0;
    int c_cost = INT_MAX;
    while (n->flight) {
      flight_t * f = n->flight;
      if (isAfter(&(f->departure), now) && !strcmp(dst->name, f->dest_airport->name)) {
          if (f->cost_of_flight == c_cost) {
              num_c_flights++;
          }
          if (f->cost_of_flight < c_cost) {
               
              num_c_flights = 1;
              c_cost = f->cost_of_flight;
          }
      }
      n = n->next;
    }
    if(num_c_flights == 0) {
        return false;
    }
    //Make an array of the cheapest flight(s) 
    flight_t * c_flights[num_c_flights];
    n = src->flights;
    int i = 0;
    while (n->flight) {
      if (c_cost == n->flight->cost_of_flight) {
          c_flights[i] = n->flight;
          i++;
      }
      n = n->next;
    }

    flight_t* earliest_flight = c_flights[0];
    timeHM_t* earliest_arrival = &(c_flights[0]->arrival);
    for(int k = 0; k < num_c_flights; k++) {
      flight_t* fi = c_flights[k];
      if (isAfter(earliest_arrival, &(fi->arrival))) {
          earliest_arrival = &(fi->arrival);
          earliest_flight = fi;
      }
    }

    *departure = earliest_flight->departure;
    *arrival = earliest_flight->arrival;
    *cost = earliest_flight->cost_of_flight;

    return true;

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
   
    if(!flight_list || !airport_name_list) {
        return -1;
    }
    flight_t* curFlight = *flight_list;  
    char* curAirportName =  *airport_name_list;
    if (curFlight == NULL) {
        return -1;
    }
    flight_t* nextFlight = *(flight_list + 1);
    int totalCost = 0;
    for (int i = 1; i<sz; i++) {
        if (!(isAfter(&(nextFlight->departure), &(curFlight->arrival)) 
            || isEqual(&(nextFlight->departure), &(curFlight->arrival)))) {
            return -1;
        }
        if (strcmp(curFlight->dest_airport->name, curAirportName)) {         
            return -1;
        }
        totalCost += curFlight->cost_of_flight;
        curAirportName = curAirportName + 4;  
        curFlight = nextFlight;
        nextFlight = curFlight + 1;
        if(!curFlight || !curAirportName) {
             return -1;
        }

    }
    totalCost += curFlight->cost_of_flight;
    if (strcmp(curFlight->dest_airport->name, curAirportName) == 0) {
      
        return totalCost;
    }
    return -1;
    
}
