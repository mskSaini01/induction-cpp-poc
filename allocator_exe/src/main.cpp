#include <stdio.h>
#include "allocator.hpp"
#include "profiler.hpp"

#define BUFFER_LIMIT 1024

int main ()
{
        PROFILER_FILE ("memory_allocator_profile.txt");
        InitMemManager (BUFFER_LIMIT);

        int * a = (int *) Malloc_ (sizeof (int));
        int * b = (int *) Malloc_ (sizeof (int));
        int * c = (int *) Malloc_ (sizeof (int));
        int * d = nullptr;
        int * e = nullptr;

    if (!a) {
        printf ("a : nullptr\n");
        return 0;
    }

    if (!b) {
        printf ("b : nullptr\n");
        return 0;
    }

    if (!c) {
        printf ("c : nullptr\n");
        return 0;
    }

    printf ("Before allocation - \n");
    
    printf ("a : %p\n", a);
    printf ("a : %d\n", *a);

    printf ("After allocation - \n");

    *a = 5;
    *b = 4;
    *b = 3;
    
    printf ("a : %p\n", a);
    printf ("a : %d\n", *a);

    printf ("b : %p\n", b);
    printf ("b : %d\n", *b);
    
    printf ("c : %p\n", c);
    printf ("c : %d\n", *c);

    if (Free_(c)) {
        printf ("c : freed!\n");
    }

    if (Free_(b)) {
        printf ("b : freed!\n");
    }

    if (Free_(a)) {
        printf ("a : freed!\n");
    }

    // Profile for 10000 custom malloc
    START_PROFILER;

    for (int i = 0; i < 100000; i++) {
        INIT_PROFILER;
        d = (int *) Malloc_ (sizeof (int));
    }

    END_PROFILER ("Custom Malloc");

    // Profile for 10000 standard malloc
    START_PROFILER;
    
    for (int i = 0; i < 100000; i++) {
        INIT_PROFILER;
        e = (int *) malloc (sizeof (int));
    }
    
    END_PROFILER ("Standard Malloc");

    return 0;
}
