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
    /*LRUCache cache(5);
    cache.refer(1);
    cache.refer(2);
    cache.refer(3);
    cache.refer(4);
    cache.refer(5);
    cache.refer(3);
    cache.reset(4);
    cache.refer(5);

    cache.display();*/
    
    return 0;
}
