#include <stdio.h>
#include <stdlib.h>
#include "avl.hpp"
#include "inputs.hpp"

// method for display data 
void RenderData (size_t pData)
{
    printf ("%zu  ->  ", pData);
}

// Method for displaying operation menu
int MainMenu ()
{
    printf ("\n===== Self Balancing Tree =====\n");
    printf ("1. Insert Data\n");
    printf ("2. Update Data\n");
    printf ("3. Delete Data\n");
    printf ("4. Data Existance Check \n");
    printf ("5. Display Tree\n");
    printf ("6. Display Tree In Reversed Order\n");
    printf ("7. Clear Tree\n");
    printf ("8. Exit\n");
    printf ("Enter your choice: ");

    return GetInt ();
}

int main ()
{
        AVL<size_t> avl_tree (nullptr, RenderData);
        size_t      data;
        size_t      new_data;

    while (true) {

        switch (MainMenu ()) {
            case 1:
                printf ("\nData: ");
                data = (size_t) GetUnsignedLongLongInt ();
                
                if (avl_tree.Insert (data)) {

                    printf ("\n- Insertion Successful -\n");
                
                } else {

                    printf ("\n- Insertion Failure -\n");
                }

                break;

            case 2:
                printf ("\nData to be Updated: ");
                data = (size_t) GetUnsignedLongLongInt ();
                
                printf ("\nNew Value : ");
                new_data = (size_t) GetUnsignedLongLongInt ();
                
                if (avl_tree.Update (data, new_data)) {

                    printf ("\n- Updated Successful -\n");
                
                } else {

                    printf ("\n- Updation Failure -\n");
                }

                break;
                
            case 3:
                printf ("\nData to be Deleted : ");
                data = (size_t) GetUnsignedLongLongInt ();
                
                if (avl_tree.Delete (data)) {

                    printf ("\n- Deletion Successful -\n");
                
                } else {

                    printf ("\n- Deletion Failure -\n");
                }

                break;

            case 4:
                printf ("\nExistance check for Data: ");
                data = (size_t) GetUnsignedLongLongInt ();
                
                if (avl_tree.IsPresent (data)) {

                    printf ("\n- Data Exists-\n");

                } else {
                    
                    printf ("\n- Data Not Found-\n");
                }

                break;

            case 5:
                printf ("\n\n===== Sorted Binary Search Tree =====\n");
                avl_tree.Display ();
                break;

            case 6:
                printf ("\n\n===== Reversed Binary Search Tree =====\n");
                avl_tree.Display (true);
                break;

            case 7:
                avl_tree.Clear ();
                printf ("\n\n- Tree Cleared -\n");
                break;

            case 8:
                printf ("\n\nExiting program. Goodbye!\n");
                return 0;

            default:
                printf ("\n\nInvalid choice. Please try again.\n");
        }

        printf ("\n");
        system ("pause");
        system ("clear");
    }

    return 0;
}
