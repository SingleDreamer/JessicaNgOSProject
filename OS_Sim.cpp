// Jessica Ng
// CSCI340-3

// OS_Sim.cpp

#ifndef OS_SIM_CPP
#define OS_SIM_CPP

#include "OS_Sim.h"

OS_Sim::OS_Sim(unsigned int r, unsigned int s, unsigned int d): memory_(RAM(r,s))
{
    time_ = 1;
    RAM_ = r;
    pfsize_ = s;
    num_disks_ = d;
    
    PID_counter_ = 1; // PIDs start at 0
    
    disks_.resize(d);
    for (unsigned int i = 0; i < d; i++) {
        disks_[i] = Disk(i);
    }
}


void OS_Sim::run() {
    string input;
    
    while (true) {
        cout << endl;
        
        /*if (!CPU_.empty()) {
            cout << endl << "current process: " << endl;
            CPU_.getProcess()->display();
            cout << endl;
        }*/
        
        cout << "> ";
        cin >> input;
        
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
        // !!!check if d operations are safe!!!
        else if (input == "d") {
            requestDisk();
        }
        else if (input == "D") {
            returnDisk();
        }
        else if (input == "m") {
            accessMemory();
        }
        else if (input == "S") {
            snapshot();
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
        addTime(); // add time even on invalid?

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
    
    int f = memory_.request(p->getPID(), 0, getTime());
    p->setAddress(0, f);
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
    //cout << addTime() << endl;
    if (CPU_.empty()) return;
    Process* p = CPU_.getProcess();
    p->passQuantum();
    if (p->getPriority() == 0) {
        // cout << p->getPID() << " insert queue level 1" << endl;
        CPU_.stop();
        p->reducePriority();
        p->resetQuantum();
        //p->setTimestamp(getTime());
        queue_.insert(p);
        Process* n = queue_.pop();
        n->setTimestamp(getTime());//
        CPU_.execute(n);
    } //else if (p->getPriority() == 1 && p->getTimestamp()+1 != getTime()) {
    else if (p->getPriority() == 1 && p->getQuantumPassed() == 2) {
        // cout  << p->getPID() << " insert queue level 2" << endl;
        CPU_.stop();
        p->reducePriority();
        p->resetQuantum();
        //p->setTimestamp(getTime());
        queue_.insert(p);
        Process* n = queue_.pop();
        n->setTimestamp(getTime());//
        CPU_.execute(n);
    }
    return; 
}

void OS_Sim::terminate() {
    Process* p = CPU_.stop();
    unsigned int PID = p->getPID();
    memory_.remove(PID);

    if (queue_.empty()) return;
    CPU_.execute(queue_.pop());
    
    delete p;
}

void OS_Sim::snapshot() {
    char input;
    cin >> input;
    cin.clear();
    // r
    if(input == 'r') {
        cout << endl << "**************" << endl << "CPU" << endl << "**************" << endl;
        if (CPU_.empty()) cout << "<empty>" << endl << endl;
        //cout << endl;
        else {
            //cout << CPU_.getProcess()->getPID() << endl;
            //cout << endl;
            CPU_.getProcess()->display();
        }
        cout << endl << "**************" << endl << endl << endl << "**************" << endl ;
        cout << "Queue" << endl << "**************" << endl << endl;
        queue_.print();
        cout << endl << "**************";
    }
    // i
    else if (input == 'i') {
        for (auto it = disks_.begin(); it != disks_.end(); it++) {
            (*it).display();
        }
    }
    // m
    else if (input == 'm') {
        memory_.print();
    }
    else {
        cout << "Invalid Input" << endl;
    }
}

void OS_Sim::accessMemory() {
    // memory operation
    // put in one function
    int address;
    cin >> address;
    if (!CPU_.empty()) {
        int page_number = address/get_pfsize();
        Process* p = CPU_.getProcess();
        if (!p->AddressExists(page_number) ||
            (!memory_.access(p->getFrame(page_number), p->getPID(), page_number, getTime()))) {
            int f = memory_.request(p->getPID(), address, getTime());
            p->setAddress(page_number, f);
        } // update timestamp
    }

}

void OS_Sim::requestDisk() {
    // read number
    int number;
    cin >> number;
    cin.clear();
    // read filename
    string filename;
    cin >> filename;
    cin.clear();
    // read from diski
    if (number >= 0) {
        if ((unsigned)number < num_disks_ && !CPU_.empty()) {
            //cout << CPU_.getProcess()->getPID() << endl;
            disks_[number].request(CPU_.getProcess(), filename);
            CPU_.stop();
            if (!queue_.empty()) {
                Process* next = queue_.pop();
                next->setTimestamp(getTime());//
                CPU_.execute(next);
            }
        }
    }

}

void OS_Sim::returnDisk() {
    // read in nnumber
    int number;
    cin >> number;
    cin.clear();
    // finish reading from disk
    if (number >= 0) {
        
        if ((unsigned)number < num_disks_) {
            Process* p = disks_[number].finish();
            if (p != NULL) {
                p->resetQuantum();
                if (CPU_.empty()) {
                    CPU_.execute(p);
                } else {
                    // behavior here??????
                    queue_.insert(p);
                    queue_.preempt(CPU_.stop());
                    CPU_.execute(queue_.pop());
                }
            }
            
        }
    }

}

#endif // OS_SIM_CPP
