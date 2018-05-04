// Jessica Ng
// CSCI340-03

// Process.h

#ifndef PROCESS_H
#define PROCESS_H

class Process {
    
public:
    
    Process (int p) {
        PID_ = p;
        priority_ = 0;
    }
    Process (int p, int t) {
        PID_ = p;
        priority_ = 0;
        timestamp_ = t;
    }
    void setTimestamp( int t ) { timestamp_ = t; }
    int getTimestamp() { return timestamp_; }
    int getPID() { return PID_; }
    int getPriority() { return priority_; }
    int reducePriority() {
        if (priority_ < 2) priority_++;
        return priority_;
    }
    
private:
    
    int PID_;
    int priority_; // 0, 1, or 2 ; 0 is highest
    //vector<Pair<int, int>> memoryaddresses;
    int timestamp_;
    
};

#endif // PROCESS_H
