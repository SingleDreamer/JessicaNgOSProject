// Jessica Ng
// CSCI340-3

// RAM.cpp

#ifndef RAM_CPP
#define RAM_CPP

#include "RAM.h"

void RAM::print() {
    cout << endl; 
    cout << "F#\tP#\tPID\tts" << endl;
    for (auto it = frames_.begin(); it != frames_.end(); it++) {
        cout << *it << endl;
    }

}


unsigned int RAM::request(unsigned int PID, unsigned int address, unsigned int timestamp) {
    cout << "request" << endl;
    //cache.display();
    unsigned int page_number = address / pfsize_;
    int lru = cache.peek();
    cout << lru;
    Frame&& f = move(frames_[lru]);
    f.page_number_ = page_number;
    f.PID_ = PID;
    f.timestamp_ = timestamp;
    cache.refer(lru);
    return lru; 
    
}

void RAM::remove(unsigned int PID) {
    for (unsigned int i = 0; i < num_frames_; i++) {
        if (frames_[i].PID_ == PID) {
            frames_[i].clear(); 
        }
    }
}


#endif //RAM_CPP