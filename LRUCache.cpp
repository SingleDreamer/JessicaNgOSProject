#ifndef LRUCACHE_CPP
#define LRUCACHE_CPP

#include "LRUCache.h"

LRUCache::LRUCache(int n)
{
    csize = n;
}


int LRUCache::peek() {
    return dq.back(); 
}


/* Refers key x with in the LRU cache */
void LRUCache::refer(int x)
{
    // not present in cache
    if (ma.find(x) == ma.end())
    {
        // cache is full
        if (dq.size() == csize)
        {
            //delete least recently used element
            int last = dq.back();
            dq.pop_back();
            ma.erase(last);
        }
    }
    
    // present in cache
    else
        dq.erase(ma[x]);
    
    // update reference
    dq.push_front(x);
    ma[x] = dq.begin();
}

int LRUCache::pop() {
    int n = peek();
    refer(n);
    return n; 
}

// display contents of cache
/*void LRUCache::display()
{
    for (auto it = dq.begin(); it != dq.end(); it++)
        cout << (*it) << " ";
    
    cout << endl;
}*/


// This code is contributed by Satish Srinivas
// https://www.geeksforgeeks.org/lru-cache-implementation/


#endif //LRUCACHE_CPP
