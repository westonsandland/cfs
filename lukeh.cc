#include "debug.h"
#include "future.h"
#include "threads.h"
#include "rbt.h"

/* Called by one CPU */
void kernelMain(void) {
     RBT<int> tree;
     int a = 5, b = 3, c = 10, d = 42, e = 8;
     tree.add(&a);
     tree.add(&b);
     tree.add(&c);
     tree.add(&d);
     tree.add(&e);

     //tree.printTree();
     int *x = tree.removeLeftMost();
     x = tree.removeLeftMost();
     //tree.printTree();


     Debug::printf("*** x = %d\n",*x);
}
