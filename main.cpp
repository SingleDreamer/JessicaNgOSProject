// Jessica Ng
// CSCI340-3

// main.cpp

#include <iostream>
#include <string>

#include "OS_Sim.h"
using namespace std;


#include "ReadyQueue.h"

// how to make sure is int
int main() {
    
    string input;
    unsigned int RAM, pfsize, num_disks;
    
    cout << "How much RAM memory is there on the simulated computer?" << endl;
    cin >> RAM;
    while (cin.fail()) {
        //Not an int.
        cout << "not an int" << endl;
        cout << "How much RAM memory is there on the simulated computer?" << endl;
        cin.clear();
        cin >> RAM;
    }
    while (RAM > 4000000000) {
        cout << "Too big" << endl;
        cout << "How much RAM memory is there on the simulated computer?" << endl;
        cin.clear();
        cin >> RAM;
    }
    cin.clear();
    cout << "What is the size of a page/frame?" << endl;
    cin >> pfsize;
    while (pfsize > RAM) {
        cout << "Too big" << endl;
        cout << "What is the size of a page/frame?" << endl;
        cin.clear();
        cin >> pfsize;
    }
    cin.clear();
    cout << "How many hard disks does the simulated computer have?" << endl;
    cin >> num_disks;
    cin.clear();
    
    OS_Sim sim = OS_Sim(RAM, pfsize, num_disks);
    
    sim.run();
     
    
    /*
    int counter = 0;
    string input = "";
    Process* p;
    ReadyQueue queue; 
    
    while (input != "e") {
        cin >> input;
        if (input == "i") {
            p = new Process(counter);
            counter++;
            queue.insert(p);
        }
        else if(input == "p") {
            queue.print();
        }
        else if (input == "d") {
            p = queue.pop();
            delete p;
        }
    }
     */
     
    /*Process* p1= new Process(1);
    Process* p2= new Process(2);
    Process* p3= new Process(3);
    Process* p4= new Process(4);
    Process* p5= new Process(5);
    Process* p6= new Process(6);

    Process* p = p1;
    
    p2->reducePriority();
    p3->reducePriority();
    p4->reducePriority();
    p4->reducePriority();
    p5->reducePriority();
    p5->reducePriority();
    p5->reducePriority();
    
    ReadyQueue queue;
    queue.insert(p1);
    queue.preempt(p6);
    queue.preempt(p2);
    queue.preempt(p4);
    queue.preempt(p5);

    queue.print();

    while(p != NULL) {
        p = queue.pop();
        if (p != NULL) {
            cout << p->getPID() << endl;
            delete p;
            
        }
        cout << "0 : " << queue.l0_empty() << endl;
        cout << "1 : " << queue.l1_empty() << endl;
        cout << "2 : " << queue.l2_empty() << endl;

        queue.print();
        cout << endl;
    }
    queue.preempt(p3);
    queue.print();*/

    /*delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete p5;
    delete p6; */
    return 0;
}
