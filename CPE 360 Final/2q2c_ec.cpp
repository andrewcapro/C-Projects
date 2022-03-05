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

    cout << "New customer entered at minute " << temp->inTime
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
      cout << "Customer exited at minute " << temp->outTime
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

  // queue 1
  int lengthSumQ1 = 0;
  int minQ1Length = 999;
  int minQ1Clock = 0;
  int maxQ1Length = -999;
  int maxQ1Clock = 0;

  // queue 2
  int lengthSumQ2 = 0;
  int minQ2Length = 999;
  int minQ2Clock = 0;
  int maxQ2Length = -999;
  int maxQ2Clock = 0;

  // combined
  int queueLengthSum = 0;
  int minQueueLength = 999;
  int minLengthClock = 0;
  int maxQueueLength = -999;
  int maxLengthClock = 0;

  // RNG
  int randNum;
  int pa = 30; //init pa @ 8am

  Queue wc2queue1;
  Queue wc2queue2;

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
        // peak hrs = any time where pa is over 10%
        if (wc2queue2.size() < wc2queue1.size() && pa > 10) {
          cout << "Line 2: ";
          wc2queue2.enqueue();
        } else {
          cout << "Line 1: ";
          wc2queue1.enqueue();
        }
      }
    }

    // check on head customer's order
    // if finished

    // queue 1
    if (wc2queue1.head != NULL && wc2queue1.head->orderTime == 0) {
      // process final stats before dequeue
      customerProcessed++;
      wc2queue1.updateStats();

      // wait time: add to sum for avg + check min/max
       waitTimeSum += wc2queue1.head->waitTime;
      if (wc2queue1.head->waitTime > maxWaitTime) {
        maxWaitTime = wc2queue1.head->waitTime;
        maxWaitClock = storeClock;
      }
      if (wc2queue1.head->waitTime < minWaitTime) {
        minWaitTime = wc2queue1.head->waitTime;
        minWaitClock = storeClock;
      }

      // serv time: add to sum for avg + check min/max
      serviceTimeSum += wc2queue1.head->serviceTime;
      if (wc2queue1.head->serviceTime > maxServiceTime) {
        maxServiceTime = wc2queue1.head->serviceTime;
        maxServClock = storeClock;
      }
      if (wc2queue1.head->serviceTime < minServiceTime) {
        minServiceTime = wc2queue1.head->serviceTime;
        minServClock = storeClock;
      }

      // dequeue
      cout << "Line 1: ";
      wc2queue1.dequeue();
    }

    // queue 2
    if (wc2queue2.head != NULL && wc2queue2.head->orderTime == 0) {
      // process final stats before dequeue
      customerProcessed++;
      wc2queue2.updateStats();

      // wait time: add to sum for avg + check min/max
      waitTimeSum += wc2queue2.head->waitTime;
      if (wc2queue2.head->waitTime > maxWaitTime) {
        maxWaitTime = wc2queue2.head->waitTime;
        maxWaitClock = storeClock;
      }
      if (wc2queue2.head->waitTime < minWaitTime) {
        minWaitTime = wc2queue2.head->waitTime;
        minWaitClock = storeClock;
      }

      // serv time: add to sum for avg + check min/max
      serviceTimeSum += wc2queue2.head->serviceTime;
      if (wc2queue2.head->serviceTime > maxServiceTime) {
        maxServiceTime = wc2queue2.head->serviceTime;
        maxServClock = storeClock;
      }
      if (wc2queue2.head->serviceTime < minServiceTime) {
        minServiceTime = wc2queue2.head->serviceTime;
        minServClock = storeClock;
      }

      // dequeue
      cout << "Line 2: ";
      wc2queue2.dequeue();
    }

    /* 
    whether head is the same customer as before or (if dequeue happened) the customer after, order time should decrement regardless
    if this is not done, it cause an artificial 1 min wait period where **no one's** order gets worked on
    after all, the back of house should move onto the next order ASAP as long as FIFO and 1 minute granularity are maintained
    */
    if (wc2queue1.head != NULL) {
      wc2queue1.head->orderTime--;
    }

    if (wc2queue2.head != NULL) {
      wc2queue2.head->orderTime--;
    }

    // queue length: add to sum for avg + check min/max
    cout << "End of minute " << storeClock << ": Line 1 has " << wc2queue1.size() << " customer(s) and line 2 has " << wc2queue2.size() << " customer(s)\n";
    lengthSumQ1 += wc2queue1.size();
    lengthSumQ2 += wc2queue2.size();
    queueLengthSum += wc2queue1.size() + wc2queue2.size();

    if (wc2queue1.size() > maxQ1Length) {
      maxQ1Length = wc2queue1.size();
      maxQ1Clock = storeClock;
      if (maxQ1Length > maxQueueLength) {
        maxQueueLength = maxQ1Length;
        maxLengthClock = maxQ1Clock;
      }
    }
    if (wc2queue1.size() < minQ1Length) {
      minQ1Length = wc2queue1.size();
      minQ1Clock = storeClock;
      if (minQ1Length < minQueueLength) {
        minQueueLength = minQ1Length;
        minLengthClock = minQ1Clock;
      }
    }
    if (wc2queue2.size() > maxQ2Length) {
      maxQ2Length = wc2queue2.size();
      maxQ2Clock = storeClock;
      if (maxQ2Length > maxQueueLength) {
        maxQueueLength = maxQ2Length;
        maxLengthClock = maxQ2Clock;
      }
    }
    if (wc2queue2.size() < minQ2Length) {
      minQ2Length = wc2queue2.size();
      minQ2Clock = storeClock;
      if (minQ2Length < minQueueLength) {
        minQueueLength = minQ2Length;
        minLengthClock = minQ2Clock;
      }
    }

    // end simulation when it hits 1am or later AND all customers have left (don't kick people off line at 1am on the dot)
    if (storeClock >= 1020 && wc2queue1.head == NULL && wc2queue2.head == NULL) {
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
      
      cout << "Queue 1 average length: " << (double)lengthSumQ1 / storeClock << " customer(s)\n";
      cout << "Queue 1 best case length: " << minQ1Length << " customer(s) [first recorded at minute " << minQ1Clock << "]\n";
      cout << "Queue 1 worst case length: " << maxQ1Length << " customers(s) [first recorded at minute " << maxQ1Clock << "]\n\n";

      cout << "Queue 2 average length: " << (double)lengthSumQ2 / storeClock << " customer(s)\n";
      cout << "Queue 2 best case length: " << minQ2Length << " customer(s) [first recorded at minute " << minQ2Clock << "]\n";
      cout << "Queue 2 worst case length: " << maxQ2Length << " customers(s) [first recorded at minute " << maxQ2Clock << "]\n\n";

      cout << "Combined average queue length: " << (double)queueLengthSum / storeClock << " customer(s)\n";
      cout << "Combined best case queue length: " << minQueueLength << " customer(s) [first recorded at minute " << minLengthClock << "]\n";
      cout << "Combined worst case queue length: " << maxQueueLength << " customers(s) [first recorded at minute " << maxLengthClock << "]\n\n";

      exit(1);
    }
  }
}