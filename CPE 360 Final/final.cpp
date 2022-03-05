/*
Author: Murad Arslaner, Andrew Capro
I pledge my honor that I have abided by the Stevens Honor System
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int storeClock = 0;

class Customer {
 public:
  // clock
  int inTime;
  int outTime;

  // time spent in queue
  int waitTime;
  int orderTime;
  int serviceTime; // wait + order

  Customer* next;

  Customer() {
    next = NULL;

    // determined on enqueue
    inTime = storeClock;
    orderTime = (rand() % 6) + 1;
    
    // determined on dequeue
    outTime = 0;
    waitTime = -orderTime; // wait + order = serv  ---->  wait = serv - order (serv is TBD later)
    serviceTime = 0;
  }
};

//enqueue to tail, dequeue from head
class Queue {
 public:
  Customer* head;

  Queue() {
    head = NULL;
  }

  void enqueue() {
    Customer* temp = new Customer;

    if (head == NULL) {
      head = temp;
    } else {
      Customer* tail = head;
      while (tail->next != NULL) {
        tail = tail->next;
      }
      tail->next = temp;
      temp->next = NULL;
    }

    cout << "New customer entered the line at minute " << temp->inTime
         << " with an order time of " << temp->orderTime << " minute(s)\n";
  }

  // only to be done when order is finished
  void updateStats() {
    if (head == NULL) {
      return;
    } else {
      head->outTime = storeClock;
      head->serviceTime = head->outTime - head->inTime;
      head->waitTime += head->serviceTime;
    }
  }

  void dequeue() {
    if (head == NULL) {
      return;
    } else {
      Customer* temp = head;
      head = head->next;
      cout << "Customer exited the line at minute " << temp->outTime
           << " with a wait time of " << temp->waitTime
           << " minute(s) and a service time of " << temp->serviceTime << " minute(s)\n";
      delete temp;
    }
  }

  int size() {
    if (head == NULL) {
      return 0;
    } else {
      int count = 0;
      Customer* temp = head;
      while (temp != NULL) {
        count++;
        temp = temp->next;
      }
      return count;
    }
  }
};

int main() {
  srand(time(NULL));

  // compute avgs using customerCount or storeClock
  int customerCount = 0;
  int customerProcessed = 0;

  int queueLengthSum = 0;
  int waitTimeSum = 0;
  int serviceTimeSum = 0;

  // compute best + worst cases
  int minWaitTime = 999;
  int minWaitClock = 0;
  int maxWaitTime = -999;
  int maxWaitClock = 0;

  int minServiceTime = 999;
  int minServClock = 0;
  int maxServiceTime = -999;
  int maxServClock = 0;

  int minQueueLength = 999;
  int minLengthClock = 0;
  int maxQueueLength = -999;
  int maxLengthClock = 0;

  // RNG
  int randNum;
  int pa = 30; //init pa @ 8am

  Queue whiteCastle2;

  while (1) {
    /*
    there is no minute 0! min 1 = 8am, min 2 = 8:01am, min 3 = 8:02am ...... min 60 = 8:59am, min 61 = 9am ......
    min 1020 = 12:59am, **min 1021 = 1am** (if line is empty, end simulation; if not, continue until it is and don't let anyone new enter)
    */
    switch (storeClock) {
      /*
      store clock advances immediately after this check so probability changes take effect on first minute after number designated in switch case
      this means probabilites line up correctly with their right times at xx:00 or xx:30
      */
      case 120: //10am
        pa = 10;
        break;
      case 210: //11:30am
        pa = 40;
        break;
      case 330: //1:30pm
        pa = 10;
        break;
      case 570: //5:30pm
        pa = 25;
        break;
      case 720: //8pm
        pa = 20;
        break;
      case 900: //11pm
        pa = 10;
        break;
      case 1020: //1am
        pa = 0;
        break;
    }
    storeClock++;

    // check for arriving customers
    if (storeClock <= 1020) {
      randNum = (rand() % 100) + 1;
      if (randNum <= pa) {
        // success
        customerCount++;
        whiteCastle2.enqueue();
      }
    }

    // check on head customer's order
    
    // if finished
    if (whiteCastle2.head != NULL && whiteCastle2.head->orderTime == 0) {
      // process final stats before dequeue
      customerProcessed++;
      whiteCastle2.updateStats();

      // wait time: add to sum for avg + check min/max
       waitTimeSum += whiteCastle2.head->waitTime;
      if (whiteCastle2.head->waitTime > maxWaitTime) {
        maxWaitTime = whiteCastle2.head->waitTime;
        maxWaitClock = storeClock;
      }
      if (whiteCastle2.head->waitTime < minWaitTime) {
        minWaitTime = whiteCastle2.head->waitTime;
        minWaitClock = storeClock;
      }

      // serv time: add to sum for avg + check min/max
      serviceTimeSum += whiteCastle2.head->serviceTime;
      if (whiteCastle2.head->serviceTime > maxServiceTime) {
        maxServiceTime = whiteCastle2.head->serviceTime;
        maxServClock = storeClock;
      }
      if (whiteCastle2.head->serviceTime < minServiceTime) {
        minServiceTime = whiteCastle2.head->serviceTime;
        minServClock = storeClock;
      }

      // dequeue
      whiteCastle2.dequeue();
    }

    /* 
    whether head is the same customer as before or (if dequeue happened) the customer after, order time should decrement regardless
    if this is not done, it cause an artificial 1 min wait period where **no one's** order gets worked on
    after all, the back of house should move onto the next order ASAP as long as FIFO and 1 minute granularity are maintained
    */
    if (whiteCastle2.head != NULL) {
      whiteCastle2.head->orderTime--;
    }

    // queue length: add to sum for avg + check min/max
    cout << "End of minute " << storeClock << ": Line has " << whiteCastle2.size() << " customer(s)\n";
    queueLengthSum += whiteCastle2.size();
    if (whiteCastle2.size() > maxQueueLength) {
      maxQueueLength = whiteCastle2.size();
      maxLengthClock = storeClock;
    }
    if (whiteCastle2.size() < minQueueLength) {
      minQueueLength = whiteCastle2.size();
      minLengthClock = storeClock;
    }

    // end simulation when it hits 1am or later AND all customers have left (don't kick people off line at 1am on the dot)
    if (storeClock >= 1020 && whiteCastle2.head == NULL) {
      cout << "The time is now 1am (or later), White Castle 2 has closed for the night\n\n";
      cout << "                                 ####  @@@@            " << endl;                    
      cout << "                            /########  @@@@@@@@          " << endl;                  
      cout << "                       *    #########  @@@@@@@@@           " << endl;                
      cout << "                    ##      #########  @@@@@@@@@      @&      " << endl;             
      cout << "                ######      #########  @@@@@@@@@     *@@@@@@      " << endl;         
      cout << "             * #######  #############  @@@@@@@@@@@@@ &@@@@@@@         " << endl;     
      cout << "        ## @@/,&@@#@ @@##@ @@#@@@& @@  @@@&#####@@@@@@@@@@@@@     @@    " << endl;   
      cout << "    ######@ @@   @@    @@    @@    @@@@@@@@@@@@@@@   @@@@@@@@@@@  @@@@@@   " << endl;
      cout << "    *#######&@   @@,   @@@   @@.        @@@    #@.   ,@@@@@    @@@@@@@@    " << endl;
      cout << "  .#########&@   @@,   @@@   @@/   @@@    @@    @@   *@@    @@    @@@@@@@  " << endl;
      cout << "       #####&%   @@,   @@@   @@(   @@@    @@    @@   *@@         /@@@      " << endl;
      cout << "      ######@    &@          @@*   @@@    @@    @@   *@@     @@*  @@@@     " << endl;
      cout << "      ####@       @@@&   @@@@@@@   @@@   ,@@   @@@@   @@@@@   %@@@@@@#     " << endl;
      cout << "       ###@@@,      .@@@@@@@@@@@@@@@@   @@@@@@@@@@@@@.  @@@@@@@@@@@@@      " << endl;
      cout << "       @@    .@@@@@    @@@@@@@@@@@@@@@@@@@@@@    @@@    @@@@@@@@@@@@@    " << endl;  
      cout << "      @@    @@@@@@@@ @@@@       @@          @/   @@@    @@@@@     @@    " << endl;   
      cout << "            @@@@@@@@@@@@@@@@@   @@    @@@@@@@.   @@@    @@@   @@@       " << endl;   
      cout << "       %     @@@@@@@@@    @@    @@          @    @@@    @@@       @@    " << endl;   
      cout << "        @       @@@@@&    @@    %@@    @    @    @@@    . @     @      " << endl;    
      cout << "          &@@      @@#@@    @@  @@@@@.  @@@@@@@@ .@@@@  @@@@@@  @@     " << endl;    
      cout << "         .           *###############  @@@@@@@@@@@@@@@               " << endl;      
      cout << "                 .         ,#########  @@@@@@@@@                   " << endl;        
      cout << "                                  ###  @@@                       " << endl;

      // final stats for wait, serv, q length
      // avg, best (min), worst (max)

      cout << "\nAverage customer wait time: " << (double)waitTimeSum / customerProcessed << " minute(s)\n";
      cout << "Best case wait time: " << minWaitTime << " minute(s) [first recorded at minute " << minWaitClock << "]\n";
      cout << "Worst case wait time: " << maxWaitTime << " minute(s) [first recorded at minute " << maxWaitClock << "]\n\n";

      cout << "Average customer service time: " << (double)serviceTimeSum / customerProcessed << " minute(s)\n";
      cout << "Best case service time: " << minServiceTime << " minute(s) [first recorded at minute " << minServClock << "]\n";
      cout << "Worst case service time: " << maxServiceTime << " minute(s) [first recorded at minute " << maxServClock << "]\n\n";
      
      cout << "Average queue length: " << (double)queueLengthSum / storeClock << " customer(s)\n";
      cout << "Best case queue length: " << minQueueLength << " customer(s) [first recorded at minute " << minLengthClock << "]\n";
      cout << "Worst case queue length: " << maxQueueLength << " customers(s) [first recorded at minute " << maxLengthClock << "]\n\n";

      exit(1);
    }
  }
}