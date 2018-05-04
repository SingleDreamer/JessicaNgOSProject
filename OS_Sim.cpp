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
                if (CPU.empty()) cout << "<empty>" << endl << endl;
                else cout << CPU.getProcess()->getPID() << endl;
                queue.print(); 
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
    if (CPU.empty()) {
        CPU.execute(p);
    } else {
        queue.insert(p);
        if (CPU.getProcess()->getPriority() > 0) {
            queue.preempt(CPU.stop());
            CPU.execute(queue.pop());
        }
    }
    
    /*
     cout << CPU.empty() << endl;
     Process* p = CPU.terminate();
     if (p != NULL) cout << p->getPID() << endl; 
     delete p;
     p = new Process(getNewPID());
     cout << p->getPID() << endl; 
     cout << CPU.execute(p) << endl;
     */
}

void OS_Sim::passQuantum() {
    cout << addTime() << endl;
    if (CPU.empty()) return;
    Process* p = CPU.getProcess();
    if (p->getPriority() == 0) {
        cout << "insert queue 1" << endl;
        CPU.stop();
        p->reducePriority();
        //p->setTimestamp(getTime());
        queue.insert(p);
        Process* n = queue.pop();
        n->setTimestamp(getTime());
        CPU.execute(n);
    } else if (p->getPriority() == 1 && p->getTimestamp()+1 != getTime()) {
        cout << "insert queue 2" << endl;
        CPU.stop();
        p->reducePriority();
        //p->setTimestamp(getTime());
        queue.insert(p);
        Process* n = queue.pop();
        n->setTimestamp(getTime());
        CPU.execute(n);
    }
    return; 
}

void OS_Sim::terminate() {
    CPU.stop();
    if (queue.empty()) return;
    CPU.execute(queue.pop());
}


#endif // OS_SIM_CPP
