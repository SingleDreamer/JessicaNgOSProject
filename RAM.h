// Jessica Ng
// CSCI340-3

// RAM.h

#ifndef RAM_H
#define RAM_H

#include "LRUCache.h"
#include "Process.h"
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

struct Frame {
    Frame():
    frame_number_(-1),
    page_number_(-1),
    PID_(-1),
    timestamp_(-1),
    empty_(true) {}
    /*unsigned*/ int frame_number_;
    /*unsigned*/ int page_number_;
    /*unsigned*/ int PID_;
    /*unsigned*/ int timestamp_;
    bool empty_;
    void clear() {
        page_number_ = -1;
        PID_ = -1;
        timestamp_ = -1;
        empty_ = true; 
    }
    bool empty() { return empty_; }
    friend ostream& operator<<(ostream& os, const Frame& f) {
        if (f.frame_number_ != -1) os << f.frame_number_ << "\t";
        if (f.page_number_ != -1) os << f.page_number_ << "\t";
        if (f.PID_ != -1) os << f.PID_ << "\t";
        if (f.timestamp_ != -1) os << f.timestamp_;
        cout << endl; 
        return os;
    }
};

class RAM {
    
public:
    RAM(unsigned int r, unsigned int s);
    
    unsigned int request(/*unsigned*/ int PID, /*unsigned*/ int address, /*unsigned*/ int timestamp);
    bool access(/*unsigned*/ int frame, /*unsigned*/ int PID, /*unsigned*/ int page_number, /*unsigned*/ int timestamp);
    void remove(/*unsigned*/ int PID);
    
    void print(); 
    
private:
    vector<Frame> frames_;
    LRUCache cache;
    unsigned int RAMsize_;
    unsigned int pfsize_; //page and frame size
    unsigned int num_frames_;
};

#endif //RAM_H