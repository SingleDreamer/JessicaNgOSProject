/* We can use stl container list as a double
 ended queue to store the cache keys, with
 the descending time of reference from front
 to back and a set container to check presence
 of a key. But to fetch the address of the key
 in the list using find(), it takes O(N) time.
 This can be optimized by storing a reference
 (iterator) to each key in a hash map. */

#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <iostream>
#include <list>
#include <unordered_map>
//#include <bits/stdc++.h>
using namespace std;

class LRUCache
{
    
private:
    // store keys of cache
    list<int> dq;
    
    // store references of key in cache
    unordered_map<int, list<int>::iterator> ma;
    int csize; //maximum capacity of cache
    
    
    
public:

    LRUCache(): csize(1) {}

    LRUCache(int);
    void refer(int);
    //void display();
    int peek();
    int pop();
    
    //void setMaxSize( int size );
};


// This code is contributed by Satish Srinivas
// https://www.geeksforgeeks.org/lru-cache-implementation/

#endif //LRUCACHE_H
