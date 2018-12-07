#include "stdint.h"
#include "smp.h"
#include "debug.h"
#include "config.h"
#include "threads.h"
#include "pit.h"
#include "future.h"

#define N 5000000

/* Called by one CPU */
void kernelMain(void) {
    int nCpus = kConfig.totalProcs;
    int nThreads = nCpus * 2;
    volatile uint32_t *perCpu = new uint32_t[nCpus];
    auto *perThread = new Future<uint32_t>*[nThreads];

    for (int i = 0; i<nCpus; i++) perCpu[i] = 0;

    for (int i = 0; i<nThreads; i++) perThread[i] = new Future<uint32_t>();

    for (int i = 0; i<nThreads; i++) {
        thread([i,perCpu,perThread]() {
            for (int j = 0; j < N; j++) {
                perCpu[SMP::me()] ++;
            }
            perThread[i]->set(N);
        });
    }

    for (int i=0; i<nThreads; i++) {
        Debug::printf("*** thread %d did %d\n",i,perThread[i]->get());
    }

    for (int i=0; i<nCpus; i++) {
        Debug::printf("| cpu %d did %d\n",i,perCpu[i]);
        if (perCpu[i] == 0) {
            Debug::printf("*** cpu %d didn't do any work\n",i);
        }
    }
    Debug::printf("*** done\n");
}

