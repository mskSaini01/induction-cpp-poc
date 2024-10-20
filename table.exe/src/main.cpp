#include <stdio.h>
#include "table.hpp"

#define ROW_SIZE 10
#define COL_SIZE 10

int main () 
{
        int             row                     = ROW_SIZE;
        int             col                     = COL_SIZE;
        Table           table (row, col, 1ll);
        std::jthread    write_thread1;
        std::jthread    write_thread2;
        std::jthread    read_thread1;
        std::jthread    read_thread2;

    printf ("\nWrite 3 at (0, 0) in Table!\n");
    write_thread1 = std::jthread (&Table::WriteAt, &table, 0, 0, 3ll);

    printf ("\nWrite 4 at (1, 0) in Table!\n");
    write_thread2 = std::jthread (&Table::WriteAt, &table, 1, 0, 4ll);

    write_thread1.join ();
    write_thread2.join ();

    printf ("\nPrint Rows (0-7) of Table!\n");
    read_thread2 = std::jthread (&Table::ReadRows, &table, 0, 7);

    printf ("\nPrint 1st Row of Table!\n");
    read_thread1 = std::jthread (&Table::ReadRow, &table, 1);

    read_thread1.join ();
    read_thread2.join ();

    printf ("\nPrinting Final Table!\n");
    table.PrintTable ();

    return 0;
}
