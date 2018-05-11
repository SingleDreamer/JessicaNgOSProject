// Jessica Ng
// CSCI340-3

// RAM.cpp

#ifndef RAM_CPP
#define RAM_CPP

#include "RAM.h"



RAM::RAM(unsigned int r, unsigned int s)//: cache(LRUCache(r/s))
{
    RAMsize_ = r;
    pfsize_ = s;
    num_frames_ = RAMsize_ / pfsize_;
    
    frames_.resize(num_frames_);
    
    cache = LRUCache(num_frames_);
    for (unsigned int i = 0; i < num_frames_; i++) {
        frames_[i].frame_number_ = i;
        cache.refer(i);
    }
    
    
};

void RAM::print() {
    cout << endl;
    cout << "***************************" << endl;
    cout << "F#\tP#\tPID\tts" << endl;
    cout << "***************************" << endl;
    for (auto it = frames_.begin(); it != frames_.end(); it++) {
        cout << *it << endl;
    }

}


unsigned int RAM::request(unsigned int PID, unsigned int address, unsigned int timestamp) {
    // cout << "request address :";
    //cache.display();
    unsigned int page_number = address / pfsize_;
    int lru = cache.peek();
    // cout << lru << endl;
    Frame&& f = move(frames_[lru]);
    f.page_number_ = page_number;
    f.PID_ = PID;
    f.timestamp_ = timestamp;
    f.empty_ = false; 
    cache.refer(lru);
    return lru; 
    
}

bool RAM::access(unsigned int frame, unsigned int PID, unsigned int page_number, unsigned int timestamp) {
    // cout << "accessed" << endl;
    if (frames_[frame].PID_ == PID && frames_[frame].page_number_ == page_number) {
        Frame&& f = move(frames_[frame]);
        f.timestamp_ = timestamp;
        cache.refer(frame);
        // cout << "memory exists, timestamp was overwritten" << endl;
    }
    else {
        // cout << "memory was overwritten, need to retrieve again." << endl ;
    }
    return frames_[frame].PID_ == PID && frames_[frame].page_number_ == page_number;
}

void RAM::remove(/*unsigned*/ int PID) {
    for (unsigned int i = 0; i < num_frames_; i++) {
        if (frames_[i].PID_ == PID) {
            frames_[i].clear();
            cache.reset(i);
            //cache.refer(i); // make sure that empty is least recently used?
        }
    }
}


#endif //RAM_CPP