// Jessica Ng
// CSCI340-3

// OS_Sim.cpp

#ifndef OS_SIM_CPP
#define OS_SIM_CPP

#include "OS_Sim.h"

void OS_Sim::run() {
    string input;
    
    while (true) {
        //getline(cin, input);
        cout << endl;
        cout << "> ";
        cin >> input;
        
        cout << input << endl;
        if (input == "A") {
            // make new process
            createProcess();
        }
        else if (input == "Q") {
            // spend one time quantum
            //cout << addTime() << endl;
            //queue.pop();
            passQuantum(); 
        }
        else if (input == "t") {
            // terminate current process
            terminate();
        }
        else if (input == "d") {
            // read number
            int number;
            cin >> number;
            cin.clear();
            // read filename
            string filename;
            cin >> filename;
            cin.clear();
            // read from disk
        }
        else if (input == "D") {
            // read in nnumber
            int number;
            cin >> number;
            cin.clear();
            // finish reading from disk
        }
        else if (input == "m") {
            // memory operation
        }
        else if (input == "S") {
            char input;
            cin >> input;
            cin.clear();
            // r
            if(input == 'r') {
                cout << endl << "CPU: ";
                if (CPU_.empty()) cout << "<empty>" << endl << endl;
                else cout << CPU_.getProcess()->getPID() << endl;
                queue_.print(); 
            }
            // i
            else if (input == 'i') {
                
            }
            // m
            else if (input == 'm') {
                
            }
            else {
                cout << "Invalid Input" << endl;
            }
        }
        else if (input == "info") {
            cout << get_RAM() << endl;
            cout << get_pfsize() << endl;
            cout << get_num_disks() << endl;
        }
        else {
            if (input == "e") return;
            cout << "Invalid input" << endl;
        }
        
    }
    
    //return;
}

void OS_Sim::createProcess() {
    Process* p = new Process(getNewPID());
    p->setTimestamp(getTime());
    if (CPU_.empty()) {
        CPU_.execute(p);
    } else {
        queue_.insert(p);
        if (CPU_.getProcess()->getPriority() > 0) {
            queue_.preempt(CPU_.stop());
            CPU_.execute(queue_.pop());
        }
    }
    
    /*
     cout << CPU_.empty() << endl;
     Process* p = CPU_.terminate();
     if (p != NULL) cout << p->getPID() << endl; 
     delete p;
     p = new Process(getNewPID());
     cout << p->getPID() << endl; 
     cout << CPU_.execute(p) << endl;
     */
}

void OS_Sim::passQuantum() {
    cout << addTime() << endl;
    if (CPU_.empty()) return;
    Process* p = CPU_.getProcess();
    if (p->getPriority() == 0) {
        cout << "insert queue 1" << endl;
        CPU_.stop();
        p->reducePriority();
        //p->setTimestamp(getTime());
        queue_.insert(p);
        Process* n = queue_.pop();
        n->setTimestamp(getTime());
        CPU_.execute(n);
    } else if (p->getPriority() == 1 && p->getTimestamp()+1 != getTime()) {
        cout << "insert queue 2" << endl;
        CPU_.stop();
        p->reducePriority();
        //p->setTimestamp(getTime());
        queue_.insert(p);
        Process* n = queue_.pop();
        n->setTimestamp(getTime());
        CPU_.execute(n);
    }
    return; 
}

void OS_Sim::terminate() {
    CPU_.stop();
    if (queue_.empty()) return;
    CPU_.execute(queue_.pop());
}


#endif // OS_SIM_CPP
