// Jessica Ng
// CSCI340-3

// OS_Sim.h

#ifndef OS_SIM_H
#define OS_SIM_H

#include <iostream>
#include <string>

#include "Process.h"
#include "ReadyQueue.h"

using namespace std;

struct CPU {
    CPU(): process_(NULL) {}
    ~CPU() { if (!empty()) delete process_; }
    Process* process_;
    Process* getProcess() { return process_; }
    bool execute(Process* /*&*/p) {
        if (empty()) {
            process_ = p;
            return true;
        }
        return false;
    }
    Process* stop() {
        Process* temp = process_;
        process_ = NULL;
        return temp;
    }
    bool empty() { return process_ == NULL; }
};

class OS_Sim {
    
public:
    OS_Sim(unsigned int r, unsigned int s, unsigned int d) {
        time_ = 0;
        RAM_ = r;
        pfsize_ = s;
        num_disks_ = d;
        
        pid_counter_ = 1; // PIDs start at 0
    }
    
    unsigned int getNewPID() { return pid_counter_++; }
    unsigned int getTime() { return time_; }
    
    unsigned int get_RAM() { return RAM_; }
    unsigned int get_pfsize() { return pfsize_; }
    unsigned int get_num_disks() { return num_disks_; }
    
    unsigned int addTime() { return ++time_ ; }
    void passQuantum();
    void terminate();    
    void createProcess();
    
    void run();
    
private:
    unsigned int time_;
    unsigned int RAM_;
    unsigned int pfsize_; //page and frame size
    unsigned int num_disks_;
    
    unsigned int pid_counter_;
    CPU CPU;
    ReadyQueue queue;
    // multilevel queue
    /*list<Process*> level0_; // RR with time quantum 1
     list<Process*> level1_; // RR with time quantum 2
     list<Process*> level2_;*/ // FCFS
    // I/O queue
    
};


#endif // OS_SIM_H
