// Jessica Ng
// CSCI340-3

// ReadyQueue.h
// multilevel feedback queue
// L0: RR with quantum 1
// L1: RR with quantum 2
// L2: FCFS

#ifndef READYQUEUE_CPP
#define READYQUEUE_CPP

#include "ReadyQueue.h"

ReadyQueue::~ReadyQueue() {

    for (auto it = level0_.begin(); it != level0_.end(); it++) {
        delete (*it);
    }
    for (auto it = level1_.begin(); it != level1_.end(); it++) {
        delete (*it);
    }
    for (auto it = level2_.begin(); it != level2_.end(); it++) {
        delete (*it);
    }

}

void ReadyQueue::insert(Process* p) {
    if(p->getPriority()==0) level0_.push_front(p);
    if(p->getPriority()==1) level1_.push_front(p);
    if(p->getPriority()==2) level2_.push_front(p);
}

void ReadyQueue::preempt(Process* p) {
    int priority = p->getPriority();
    switch(priority) {
        case 0:
            level0_.push_back(p);
            cout << p->getPID() << " preempts level 0" << endl;
            break;
        case 1:
            level1_.push_back(p);
            cout << p->getPID() << " preempts level 1" << endl;
            break;
        case 2:
            level2_.push_back(p);
            cout << p->getPID() << " preempts level 2" << endl;
            break;
    }
}

// make a neater function
Process* ReadyQueue::pop() {
    //cout << "teest" << endl;
    Process* p;
    if(l0_empty() && l1_empty() && l2_empty()) {
        //cout << "NULL" << endl;
        return NULL;
    }
    if (l0_empty() && l1_empty()) {
        p = level2_.back();
        level2_.pop_back();
        return p;
    }
    if (l0_empty()) {
        p = level1_.back();
        level1_.pop_back();
        return p;
    }
    p = level0_.back();
    level0_.pop_back();
    return p;
}

void ReadyQueue::print() {
    cout << "Level 0: " << endl;
    for (auto it = level0_.begin(); it != level0_.end(); it++) {
        cout << (*it)->getPID() << " -> ";
    }
    cout << endl;
    cout << "Level 1: " << endl;
    for (auto it = level1_.begin(); it != level1_.end(); it++) {
        cout << (*it)->getPID() << " -> ";
    }
    cout << endl;
    cout << "Level 2: " << endl;
    for (auto it = level2_.begin(); it != level2_.end(); it++) {
        cout << (*it)->getPID() << " -> ";
    }
    cout << endl;
}

#endif //READYQUEUE_CPP
