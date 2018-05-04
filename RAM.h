// Jessica Ng
// CSCI340-3

// RAM.h

#ifndef RAM_H
#define RAM_H

#include "LRUCache.h"
#include <vector>
#include <iostream>

using namespace std;

struct Frame {
    Frame():
    frame_number_(-1),
    page_number_(-1),
    pid_(-1),
    timestamp_(-1) {}
    /*unsigned*/ int frame_number_;
    /*unsigned*/ int page_number_;
    /*unsigned*/ int pid_;
    /*unsigned*/ int timestamp_;
    void set(unsigned int f) { frame_number_ = f; }
    friend ostream& operator<<(ostream& os, const Frame& f) {
        os << f.frame_number_ << "\t" << f.page_number_ << "\t" << f.pid_ << "\t" << f.timestamp_ << endl;
        return os;
    }
};

class RAM {
    
public:
    RAM(unsigned int r, unsigned int s)//: cache(LRUCache(r/s))
    {
        RAMsize_ = r;
        pfsize_ = s;
        num_frames_ = RAMsize_ / pfsize_;
        
        frames_.resize(num_frames_);
        for (unsigned int i = 1; i <= num_frames_; i++) {
            frames_[i-1].set(i);
        }
        
        //cache = LRUCache(4);
    };
    
    void print(); 
    
private:
    //Frame frames_[];
    vector<Frame> frames_;
    //LRUCache cache;
    unsigned int RAMsize_;
    unsigned int pfsize_; //page and frame size
    unsigned int num_frames_;
};

#endif //RAM_H