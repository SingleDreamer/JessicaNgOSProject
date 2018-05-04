// Jessica Ng
// CSCI340-3

// ReadyQueue.h

#ifndef READYQUEUE_H
#define READYQUEUE_H

#include <iostream>
#include <string>
#include <list>

#include "Process.h"

using namespace std;

class ReadyQueue {
    
public:
    
    ~ReadyQueue(); 
    
    void insert(Process* /*&*/p);
    void preempt(Process* /*&*/p);
    Process* pop();
    void print();
    
    bool l0_empty() { return level0_.empty(); }
    bool l1_empty() { return level1_.empty(); }
    bool l2_empty() { return level2_.empty(); }
    
    bool empty() { return l0_empty() && l1_empty() && l2_empty(); }

    
private:
    list<Process*> level0_; // RR with time quantum 1
    list<Process*> level1_; // RR with time quantum 2
    list<Process*> level2_; // FCFS
    
};

#endif //READYQUEUE_H
