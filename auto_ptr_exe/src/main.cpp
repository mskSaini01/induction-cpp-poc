#include <stdio.h>          // printf
#include <new>              // nothrow
#include "auto_ptr.hpp"

void UserDeleter (int * pPointer) 
{
    delete[] pPointer;
}

int main () 
{
        int *           released_data;
        int *           int_arr;
        AutoPtr<int>    int_arr_ptr;
        AutoPtr<int>    int_ptr (new (std::nothrow) int (5));
        AutoPtr<int>    int_ptr_new;
        AutoPtr<double> double_ptr;

    // Access and print the data using the overloaded operators
    printf ("\nData: %d\n", *int_ptr);
    
    // Use the conversion operator to create an AutoPtr of a different type
    double_ptr = static_cast<AutoPtr<double>> (int_ptr);
    printf ("\nConverted Data (double): %lf\n", *double_ptr);

    int_ptr = static_cast<AutoPtr<int>> (double_ptr);

    // Test Release and Reset methods
    released_data = int_ptr.Release ();
    printf ("\nReleased Data: %d\n", *released_data);

    // Reset AutoPtr with a new int
    int_ptr.Reset (new (std::nothrow) int (10));
    printf ("New Data: %d\n", *int_ptr);

    // Test arithmetic operators
    int_ptr_new = AutoPtr<int> (new int (20));
    int_ptr_new += 2;
    printf ("Data after += 2: %d\n", *int_ptr_new);

    int_ptr_new -= 1;
    printf ("Data after -= 1: %d\n", *int_ptr_new);

    int_ptr_new -= 1;
    int_ptr_new = std::move (int_ptr); // Move assignment

    // Check if the original pointer is now null
    if (int_ptr.Get () == nullptr) {
        printf ("Original pointer is null after move.\n");
    }

    int_arr     = new int [10];
    int_arr_ptr = AutoPtr <int> (int_arr, UserDeleter);

    int_arr_ptr.Reset ();

    return 0;
}
