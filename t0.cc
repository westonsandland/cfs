#include "debug.h"
#include "future.h"
#include "threads.h"

/* Called by one CPU */
void kernelMain(void) {
     int x = 100;

     Future<int> f;

     thread([&f,x]() {
         f.set(x+1);
     });


     Debug::printf("*** x = %d, result = %d\n",x,f.get());

}

