#include "threads.h"
#include "pit.h"
#include "rbt.h"

//source: fusharblog.com for learning about define operators                                                                                                                                               
class CFS
{
        RBT<Thread> tree;
public:
	CFS(): tree() {}
        void add(Thread* thread) {
		if(thread == nullptr)
			return;
		//Debug::printf("%d\n",(uint32_t)thread);
                //thread->setCount(Pit::mseconds() - thread->getAdd());

		Debug::printf("B");
                //thread->setAdd(Pit::mseconds());

		Debug::printf("C");
                tree.add(thread);

		Debug::printf("D");
        }

        Thread* remove() {
                Thread* thread = tree.removeLeftMost();
                //uint32_t max = (Pit::mseconds() - thread->getAdd()) / tree.getSize();
                //thread->setMax(max);
                //thread->setAdd(Pit::mseconds());
                return thread;
        }

        uint32_t getSize() {
                return tree.getSize();
        }
};
