#include <stdio.h>
#include "inventory_manager.hpp"
#include "inputs.hpp"

// For User to have more flexibility with Stock Item name
void ToLowerCase (char * pString)
{
    while (*pString) {

        // Convert uppercase letter to lowercase
        if (*pString >= 'A' && *pString <= 'Z') {
            *pString = *pString + ('a' - 'A');
        }

        pString++;
    }
}

int MainMenu ()
{
    printf ("\n===== Inventory Management System =====\n");
    printf ("1. Insert Stock Item\n");
    printf ("2. Update Stock Quantity\n");
    printf ("3. Get Stock Quantity\n");
    printf ("4. Display Inventory\n");
    printf ("5. Display Stocks with Least Quantity\n");
    printf ("6. Exit\n");
    printf ("Enter your choice: ");

    return GetInt ();
}

int main ()
{
        InventoryManager    inventory_manager;
        String              item;
        size_t              quantity;

    while (true) {

        switch (MainMenu ()) {
            case 1:
                item = "";
            
                printf ("\n\nStock Item Name: ");
                item.InputStr ();
                ToLowerCase (item.GetString ());

                printf ("\nStock Quantity: ");
                quantity = (size_t) GetUnsignedLongLongInt ();

                if (inventory_manager.Insert (item.GetString (), quantity)) {
                    printf  ("\n- Insertion Successful -\n");

                } else {
                    printf  ("\n- Insertion Failure -\n");
                }
                break;

            case 2:
                item = "";
            
                printf ("\n\nStock Item Name: ");
                item.InputStr ();
                ToLowerCase (item.GetString ());

                printf ("\nStock Quantity: ");
                quantity = (size_t) GetUnsignedLongLongInt ();
                
                if (inventory_manager.Update (item.GetString (), quantity)) {
                    printf  ("\n- Updated Successful -\n");

                } else {
                    printf  ("\n- Update Failure -\n");
                }
                break;

            case 3:
                item = "";
            
                printf ("\n\nStock Item Name: ");
                item.InputStr ();
                ToLowerCase (item.GetString ());

                quantity = inventory_manager.GetItem (item.GetString ());
                
                printf("\nQuantity of %s: %zu\n", item.GetString (), quantity);
                break;

            case 4:
                printf("\n\n===== Inventory =====\n");
                inventory_manager.Display ();
                break;

            case 5:
                printf("\n\nThreshold Stock Quantity: ");
                quantity = (size_t) GetUnsignedLongLongInt ();
                
                printf("\n\n===== Stocks with Least Quantity =====\n");
                inventory_manager.GetLeast (quantity);
                break;

            case 6:
                printf("\n\nExiting program. Goodbye!\n");
                return 0;

            default:
                printf("\n\nInvalid choice. Please try again.\n");
        }

        system("pause");
        system("clear");
    }

    return 0;
}
