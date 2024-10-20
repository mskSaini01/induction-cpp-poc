#ifndef BST_HPP
#define BST_HPP

#include "bst_node.hpp"

class BST {

  public:

    // @name: Constructors
                BST                 ();

    // @name: Destructors
                ~BST                ();

    // @name: Utility Interface
    void        Insert              (tStock * pStockNode);
    void        Update              (tStock * pStock, size_t pQuantity);
    void        Delete              (tStock * pStock);
    void        Display             (size_t pQuantityLimit = SIZE_MAX)                      const;
    tBSTNode *  Clear               (tBSTNode * & pRoot);

  private:
      
    // @name: Utility helper
    void        PreOrderTraverse    (tBSTNode * pNode, size_t pQuantityLimit = SIZE_MAX)    const;
    tBSTNode *  DeleteNode          (tBSTNode * pNode, tStock * pStock);

    // @name: Data Memeber
    tBSTNode *  vRoot;
};

#endif // !BST_HPP
