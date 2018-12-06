#include "threads.h"

//source: fusharblog.com for learning about define operators                                                                                                                                                

struct CFSEntry
{
        Thread* thread;
        uint32_t timeBeforeRun;
        uint32_t timeAfterRun;
        uint32_t ranTime;
        uint32_t waitTime;
        bool operator<(CFSEntry<T> other) const
        {
                return accumulatedTime > other.accumulatedTime;
        }
}

class CFS
{
        RBT<CFSEntry> tree;
        uint32_t allowedTime;
        uint32_t numProcesses;
public:
        void add(Thread* thread);
        Thread* remove();
}
