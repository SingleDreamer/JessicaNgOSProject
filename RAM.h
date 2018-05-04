// Jessica Ng
// CSCI340-3

// RAM.h

#ifndef RAM_H
#define RAM_H

#include "LRUCache.h"

using namespace std;

struct Frame {
    Frame(unsigned int f):
    frame_number_(f),
    page_number_(-1),
    pid_(-1),
    timestamp_(-1) {}
    /*unsigned*/ int frame_number_;
    /*unsigned*/ int page_number_;
    /*unsigned*/ int pid_;
    /*unsigned*/ int timestamp_;
};

class RAM {
    
public:
    RAM(unsigned int r, unsigned int s): cache(LRUCache(r/s))
    {
        RAMsize_ = r;
        pfsize_ = s;
        num_frames_ = RAMsize_ / pfsize_;
        
        //cache = LRUCache(4);
    };
    
private:
    //Frame frames_[];
    LRUCache cache;
    unsigned int RAMsize_;
    unsigned int pfsize_; //page and frame size
    unsigned int num_frames_;
};

#endif //RAM_H