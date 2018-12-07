#include "threads.h"
#include "pit.h"
#include "rbt.h"

//source: fusharblog.com for learning about define operators                                                                                                                                               
class CFS
{
        RBT<Thread> tree;
public:
        void add(Thread* thread) {
                thread->setCount(Pit::mseconds() - thread->getAdd());
                thread->setAdd(Pit::mseconds());
                tree.add(thread);
        }

        Thread* remove() {
                Thread* thread = tree.removeLeftMost();
                uint32_t max = (Pit::mseconds() - thread->getAdd()) / tree.getSize();
                thread->setMax(max);
                thread->setAdd(Pit::mseconds());
                return thread;
        }

        uint32_t getSize() {
                return tree.getSize();
        }
};