#include <stdio.h>
#include "memory_manager.hpp"

int main ()
{
        int * a = (int *) Malloc_ (sizeof (int));
        int * b = (int *) Malloc_ (sizeof (int));
        int * c = (int *) Malloc_ (sizeof (int));
        int * d = nullptr;
        int * e = nullptr;
        int * f = nullptr;

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

    printf ("b : %p\n", b);
    printf ("b : %d\n", *b);

    printf ("c : %p\n", c);
    printf ("c : %d\n", *c);

    printf ("\nAfter allocation - \n");

    *a = 5;
    *b = 4;
    *c = 3;

    printf ("a : %p\n", a);
    printf ("a : %d\n", *a);

    printf ("b : %p\n", b);
    printf ("b : %d\n", *b);

    printf ("c : %p\n", c);
    printf ("c : %d\n", *c);

    Free_ (c);
    Free_ (a);
    Free_ (b);

    d = (int *) Malloc_ (sizeof (int));
    e = (int *) Malloc_ (sizeof (int));

    *d = 2;

    printf ("d : %p\n", d);
    printf ("d : %d\n", *d);

    e = (int *) Calloc_ (5, sizeof(int));

    printf ("e : %p\nCalloc (size: 5)\n", e);

    for (int i = 0; i < 5; i++) {
        printf ("e%d : %d\n", i, *e);
        e++;
    }

    Free_(d);
    Free_(e);

    f  = new int;
    *f = 10;
    
    printf ("f : %p\nf: Using 'new'\n", e);
    printf ("f : %p\n", f);
    printf ("f : %d\n", *f);
    
    delete f;

    return 0;
}
