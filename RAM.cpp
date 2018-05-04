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

#endif //RAM_CPP