// Jessica Ng
// CSCI340-03

// Process.h

#ifndef PROCESS_H
#define PROCESS_H

#include <unordered_map>
// remove timestamp?


class Process {
    
    //enum STATE { NEW , READY , WAITING , RUNNING , TERMINATED }

    
public:
    
    Process (unsigned int p) {
        PID_ = p;
        priority_ = 0;
        quantum_passed_ = 0;
    }
    Process (unsigned int p, unsigned int t) {
        PID_ = p;
        priority_ = 0;
        timestamp_ = t;
        quantum_passed_ = 0;
    }
    void setTimestamp( int t ) { timestamp_ = t; }
    void setAddress(unsigned int page, unsigned int frame) {
        std::cout << "set page" << page << " at frame " << frame << std::endl;
        page_table_[page] = frame;
    }
    void passQuantum() { quantum_passed_++; }
    bool removeAddress(unsigned int page) { return page_table_.erase(page) == 1; }
    bool AddressExists(unsigned int page) { return (page_table_.find(page) != page_table_.end()); }
    unsigned int getFrame(unsigned int page) { return page_table_[page]; }
    std::unordered_map<unsigned int, unsigned int> getTable() { return page_table_; }
    unsigned int getTimestamp() { return timestamp_; }
    unsigned int getPID() { return PID_; }
    unsigned int getPriority() { return priority_; }
    
    unsigned int getQuantumPassed() { return quantum_passed_; }
    unsigned int reducePriority() {
        if (priority_ < 2) priority_++;
        return priority_;
    }
    
    void display() { std::cout << "PID: " << getPID() << std::endl << "priority: " << getPriority() << std::endl << "quantum passed: " << getQuantumPassed() << std::endl; }
    
private:
    
    unsigned int quantum_passed_;
    
    unsigned int PID_;
    unsigned int priority_; // 0, 1, or 2 ; 0 is highest
    //vector<Pair<int, int>> memoryaddresses;
    unsigned int timestamp_;
    std::unordered_map<unsigned int, unsigned int> page_table_; // page, frame
    
};

#endif // PROCESS_H
