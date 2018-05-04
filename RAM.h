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
    timestamp_(-1) {}
    /*unsigned*/ int frame_number_;
    /*unsigned*/ int page_number_;
    /*unsigned*/ int PID_;
    /*unsigned*/ int timestamp_;
    void clear() {
        page_number_ = -1;
        PID_ = -1;
        timestamp_ = -1;
    }
    friend ostream& operator<<(ostream& os, const Frame& f) {
        os << f.frame_number_ << "\t";
        os << f.page_number_ << "\t";
        os << f.PID_ << "\t";
        os << f.timestamp_ << endl;
        return os;
    }
};

class RAM {
    
public:
    RAM(unsigned int r, unsigned int s): cache(LRUCache(r/s))
    {
        RAMsize_ = r;
        pfsize_ = s;
        num_frames_ = RAMsize_ / pfsize_;
        
        frames_.resize(num_frames_);
        for (unsigned int i = 0; i < num_frames_; i++) {
            frames_[i].frame_number_ = i;
            cache.refer(i);
        }
        

    };
    
    
    
    unsigned int request(unsigned int PID, unsigned int address, unsigned int timestamp);
    bool access(unsigned int frame, unsigned int PID, unsigned int page_number) {
        cout << "accessed" << endl;
        return frames_[frame].PID_ == PID && frames_[frame].page_number_ == page_number; }
    void remove(unsigned int PID); 
    
    void print(); 
    
private:
    vector<Frame> frames_;
    LRUCache cache;
    unsigned int RAMsize_;
    unsigned int pfsize_; //page and frame size
    unsigned int num_frames_;
};

#endif //RAM_H