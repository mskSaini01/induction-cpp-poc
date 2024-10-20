#ifndef INVENTORY_MANAGER_HPP
#define INVENTORY_MANAGER_HPP

#include "hashmap.hpp"
#include "bst.hpp"
#include "stock.hpp"

/**
* @class Inventory Manager manages the stocks items in the inventory
* Displays the Stocks with Least Stock quantity in the inventory
* Handles duplicate stock item entry
* 
* Note-
* No duplicate items
*/
class InventoryManager {

  public:

    // @name: Utility Interface
    bool          Insert              (const char * pItem, size_t pQuantity = 0);
    bool          Update              (const char * pItem, size_t pNewQuantity);
    size_t        GetItem             (const char * pItem)                          const;
    void          GetLeast            (size_t pThresholdQuantity = 1)                   const;
    void          Display             ()                                            const;

  private:

    // @name: Data Memeber
    HashMap<String, tStock *> vStockMaps;      // Hashmap for stock name and its quantity
    BST                       vStockTree;      // BST with pointer to stocks for Least Stock Quantities
};

#endif // !INVENTORY_MANAGER_HPP
