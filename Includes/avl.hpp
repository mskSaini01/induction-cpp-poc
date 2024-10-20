#ifndef AVL_HPP
#define AVL_HPP

#include "avl_node.hpp"

// Function Data Deleting
template <typename Type>
using Deleter = void (*) (Type);

// Function Pointer for Data Rendering
template <typename Type>
using Render = void (*) (Type);

/**
* @class Double Threaded Self Balancing Tree
* Inserts, Updates or deletes Data in the Tree and Automatically Balances Itself accordingly 
* Cannot Delete or update a data not present in the tree
* Flexibility for Data Display and Data Free as per User's Instruction
* Displays Data in the Tree as per user's given render method or overloaded insertion ( << ) operator
* Clear all the data in the Tree
* 
* Note-
* No duplicate Data
* For Duplicates data, Operates on the First Occurance of the data
*/
template <typename Type>
class AVL {

  public:

    // @name: Constructors
                            AVL                 (Deleter<Type> pDeleter = nullptr, Render<Type> pRender = nullptr);

    // @name: Destructors
                            ~AVL                ();

    // @name: Utility Interface
    bool                    Update              (Type pData, Type pNewData);
    bool                    Delete              (Type pData, Deleter<Type> pDeleter = nullptr);
    bool                    Insert              (Type pData)                                                noexcept;
    bool                    IsPresent           (Type pData)                                        const   noexcept;
    void                    Display             (bool pRevereOreder = false)                        const   noexcept;
    void                    Clear               ();

  private:
      
    // @name: Utility helper
    tAVLNode<Type> *        DeleteNode          (tAVLNode<Type> * pNode, Type Data);
    void                    ReleaseNode         (tAVLNode<Type> * & pNode);
    tAVLNode<Type> *        InsertNode          (tAVLNode<Type> * pNode, tAVLNode<Type> * pSource)          noexcept;
    tAVLNode<Type> *        GetBalancedSubTree  (tAVLNode<Type> * pNode)                                    noexcept;
    tAVLNode<Type> *        RotateLLTree        (tAVLNode<Type> * & pRoot)                                  noexcept;
    tAVLNode<Type> *        RotateLRTree        (tAVLNode<Type> * & pRoot)                                  noexcept;
    tAVLNode<Type> *        RotateRRTree        (tAVLNode<Type> * & pRoot)                                  noexcept;
    tAVLNode<Type> *        RotateRLTree        (tAVLNode<Type> * & pRoot)                                  noexcept;
    int                     GetHeight           (tAVLNode<Type> * & pNode)                          const   noexcept;
    int                     GetBalance          (tAVLNode<Type> * & pNode)                          const   noexcept;
    void                    UpdateHeight        (tAVLNode<Type> * & pNode)                                  noexcept;
    void                    UpdateReplacements  (tAVLNode<Type> * & pNode,
                                                 tAVLNode<Type> * & replacement,
                                                 tAVLNode<Type> * & replacements_parent)                    noexcept;

    // @name: Data Memeber
    tAVLNode<Type> *        vRoot;              // Top of the BST
    tAVLNode<Type> *        vThreadManager;     // Dummy node for managing threads in BST
    Deleter<Type>           vDeleter;           // Custom deleter by user for data
    Render<Type>            vRender;            // Custom display by user for node data
};

#include "avl.hxx"

#endif // !AVL_HPP
