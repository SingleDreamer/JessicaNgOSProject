// Jessica Ng
// CSCI340-3

// OS_Sim.h

#ifndef OS_SIM_H
#define OS_SIM_H

#include <iostream>
#include <string>
#include <unordered_map>

#include "Process.h"
#include "ReadyQueue.h"
#include "RAM.h"

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

struct Disk {
    Disk(): number_(-1), process_(NULL), filename_("") {}
    Disk(int n): number_(n), process_(NULL), filename_("") {}
    ~Disk() { if (process_ != NULL) delete process_; }
    
    int number_;
    Process* process_;
    string filename_; // have in process??
    list<pair<Process*, string>> IOQueue;
    
    void request (Process* p, string filename) {
        // cout << p->getPID() << " added to IO queue of disk " << number_ << endl;
        IOQueue.push_front(make_pair(p, filename));
        if (process_ == NULL) pop(); 
        //pop();
    }
    
    void pop() {
        pair<Process*, string> next = IOQueue.back();
        IOQueue.pop_back();
        process_ = next.first;
        filename_ = next.second;
    }
    
    Process* finish() {
        Process* p = process_;
        process_ = NULL;
        filename_ = "";
        if (!IOQueue.empty()) {
            pop();
        }
        return p;
    }
    
    void display() {
        cout << "*********" << endl;
        cout << "*********" << endl;
        cout << "Disk " << number_ << endl;
        if (process_ != NULL) cout << process_->getPID() << " " << filename_ << endl;
        cout << "*********" << endl << "I/O queue" << endl;
        for (auto it = IOQueue.begin(); it != IOQueue.end(); it++) {
            cout << "\t^" << endl; 
            cout << it->first->getPID() << " " << it->second << endl;
        }
        cout << "*********" << endl;
        cout << "*********" << endl;
        cout << endl << endl;
    }
    
};

class OS_Sim {
    
public:
    OS_Sim(unsigned int r, unsigned int s, unsigned int d): memory_(RAM(r,s))
    {
        time_ = 1;
        RAM_ = r;
        pfsize_ = s;
        num_disks_ = d;
        
        PID_counter_ = 1; // PIDs start at 0
        
        disks_.resize(d);
        for (int i = 0; i < d; i++) {
            disks_[i] = Disk(i);
        }
    }
    
    unsigned int getNewPID() { return PID_counter_++; }
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
    
    unsigned int PID_counter_;
    CPU CPU_;
    ReadyQueue queue_;
    RAM memory_;
    
    vector<Disk> disks_;
    // multilevel queue
    /*list<Process*> level0_; // RR with time quantum 1
     list<Process*> level1_; // RR with time quantum 2
     list<Process*> level2_;*/ // FCFS
    // I/O queue
    
};


#endif // OS_SIM_H
