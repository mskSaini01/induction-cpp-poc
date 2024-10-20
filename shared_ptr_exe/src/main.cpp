#include <stdio.h>          // printf
#include <new>              // nothrow
#include "shared_ptr.hpp"

void UserDeleter (int * pPointer) 
{
    delete[] pPointer;
}

int main ()
{
        int *           data                    = new (std::nothrow) int (5);
        int *           int_arr;
        SharedPtr<int>  int_arr_ptr;
        SharedPtr<int>  ptr                     = SharedPtr<int> (data);
        SharedPtr<int>  int_ptr (new int (10));
        SharedPtr<int>  int_ptr_copy;

    if (data != nullptr) {
        ptr = SharedPtr<int> (data);

        printf ("ptr (Address): %p\n", ptr.Get ());
        printf ("ptr (Value): %d\n", *ptr);
        printf ("ptr (RefCount): %zu\n\n", ptr.UseCount ());
    
        {
            SharedPtr <int> second_ptr = ptr;

            printf ("second_ptr (Address): %p\n", second_ptr.Get ());
            printf ("second_ptr (Value): %d\n", *second_ptr);
            printf ("second_ptr (RefCount): %zu\n\n", second_ptr.UseCount ());
        }

        printf ("ptr (Address): %p\n", ptr.Get ());
        printf ("ptr (Value): %d\n", *ptr);
        printf ("ptr (RefCount): %zu\n\n", ptr.UseCount ());
    }

    // Access and print the data using the overloaded operators
    printf ("Data: %d\n", *int_ptr);

    // Test UseCount method
    printf ("UseCount: %zu\n", int_ptr.UseCount ());

    // Create another SharedPtr pointing to the same data
    int_ptr_copy = int_ptr;

    // Print UseCount after creating a second SharedPtr
    printf ("UseCount after creating int_ptr_copy: %zu\n", int_ptr.UseCount ());

        // Test Move Constructor
        SharedPtr<int> int_ptr3 = std::move (int_ptr_copy);

    // Print UseCount after move construction
    printf ("UseCount after move construction: %zu\n", int_ptr.UseCount ());

    // Reset SharedPtr with a new int
    int_ptr.Reset (new int (15));

    // Print the new data
    printf ("New Data: %d\n", *int_ptr);

    // Test arithmetic operators
    int_ptr += 2;
    printf ("Data after += 2: %d\n", *int_ptr);

    int_ptr -= 1;
    printf ("Data after -= 1: %d\n", *int_ptr);

    int_ptr -= 1;
    
    int_arr     = new int [10];
    int_arr_ptr = SharedPtr <int> (int_arr, UserDeleter);

    int_arr_ptr.Reset ();

    return 0;
}
