#ifndef _queue_h_
#define _queue_h_

#include "atomic.h"
#include "pit.h"

template <typename T>
class Queue {
    T* first = nullptr;
    T* last = nullptr;
    InterruptSafeLock lock;
    uint32_t size;
public:
    Queue() : first(nullptr), last(nullptr), lock() {}

    void add(T* t) {
        InterruptSafeLocker x(lock);
        t->next = nullptr;
        if (first == nullptr) {
            first = t;
        }else{
            auto cur = first;
            while(cur != nullptr) {
                if(*t >= *cur){
                    if(cur->next!=nullptr){
                        if(!(*t >= *(cur->next))){
                            t->next = cur->next;
                            cur->next = t;
                            break;
                        }
                    }
                    else{
                        
                        t->next = nullptr;
                        cur->next = t;
                        break;
                    }        
                }else{
                    t->next = cur;
                    first = t;
                    break;
                }
                
                cur = cur->next;
            }
        } 
        
        if(t != nullptr) {
            t->setCount(Pit::jiffies - t->getAdd());
            t->setAdd(Pit::jiffies);
        }
        last = t;
        size++;
    }

    void addFront(T* t) {
        InterruptSafeLocker x(lock);
        t->next = first;
        first = t;
        if (last == nullptr) last = first;
        size++;
    }

    T* remove() {
        InterruptSafeLocker x(lock);
        if (first == nullptr) {
            return nullptr;
        }
        auto it = first;
        first = it->next;
        if (first == nullptr) {
            last = nullptr;
        }
        uint32_t max = (Pit::jiffies - it->getAdd()) / size;
        it->setMax(max);
        it->setAdd(Pit::jiffies);
        size--;
        return it;
    }
};

#endif
