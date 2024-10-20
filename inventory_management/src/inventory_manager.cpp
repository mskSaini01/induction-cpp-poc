#include "inventory_manager.hpp"

/**
* @brief Stock Entry Insertion
* Inserts a stock item in the inventory only when it doesn't already exists in the inventory
* @return true if the insertion was successful; otherwise false
*/
bool InventoryManager::Insert (const char * pItem, size_t pQuantity)
{
        tStock * new_stock;

    // check for duplicate key
    if (vStockMaps.Find (pItem) != nullptr) {
        return false;
    }

    new_stock = new (std::nothrow) tStock (pItem, pQuantity);

    // memory allocation failure
    if (new_stock == nullptr) {
        return false;
    }

    // add stock to hashmap
    vStockMaps.Insert (pItem, new_stock);

    // add new_stock to BST
    vStockTree.Insert (new_stock);
    
    return true;
}

/**
* @brief Updates Stock Quantity
* Updates a stock item in the inventory only when it exists in the inventory
* @return true if the Update was successful; otherwise false
*/
bool InventoryManager::Update (const char * pItem, size_t pNewQuantity)
{
        tStock * stock = vStockMaps.Find (pItem);

    // no stock found
    if (stock == nullptr) {
        return false;
    }

    // Update the Stock tree and the quantity in stock
    vStockTree.Update (stock, pNewQuantity);
    
    return true;
}

/**
* @brief Stock Quantity
* @return Stock Quantity of a specific item only if it exists in the inventory; otherwise false
*/
size_t InventoryManager::GetItem (const char * pItem) const
{
        tStock * stock = vStockMaps.Find (pItem);

    // no stock found
    if (stock == nullptr) {
        return 0;
    }

    return stock->uQuantity;
}

/**
* @brief Display Stock items and their quantity below a threshold quantity in the inventory
*/
void InventoryManager::GetLeast (size_t pThresholdQuantity) const
{
    vStockTree.Display (pThresholdQuantity);
}
/**
* @brief Display all Stock items and their quantity in the inventory
*/
void InventoryManager::Display () const
{
    vStockTree.Display ();
}
