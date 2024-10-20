#include "bst.hpp"

/**
* @brief Binary Search Tree Constructor
*/
BST::BST ()
{
    vRoot = nullptr;
}

/**
* @brief Binary Search Tree Destructor
*/
BST::~BST ()
{
    // iterate in the tree to delete all the BST nodes along with their stock data
    vRoot = Clear (vRoot);
}

/**
* @brief Stock Insertion in Binary Search Tree
* Inserts a pointer to the stock in the tree
*/
void BST::Insert (tStock * pStock)
{
        tBSTNode * curr_node = vRoot;
        tBSTNode * prev_node = vRoot;
        tBSTNode * new_node  = new (std::nothrow) tBSTNode (pStock);
        bool       to_left   = false;

    if (vRoot == nullptr) {
        vRoot = new_node;
        return;
    }
    
    // iterate to the appropriate position for insertion based on stock quantity
    while (curr_node != nullptr) {

        to_left   = false;
        prev_node = curr_node;

        // check for navigation to left or right subtree
        if (pStock->uQuantity <= curr_node->uData->uQuantity) {
            curr_node = curr_node->uLeftNode;
            to_left   = true;
        
        } else {
            curr_node = curr_node->uRightNode;
        }
    }

    if (to_left) {
        prev_node->uLeftNode = new_node;
    
    } else {
        prev_node->uRightNode = new_node;
    }
}

/**
* @brief Update stock in Binary Search Tree
* Update the stock in the tree with new quantity
*/
void BST::Update (tStock * pStock, size_t pNewQuantity)
{
    // Delete that node from the stock
    Delete (pStock);

    // Update the Stock value
    pStock->uQuantity = pNewQuantity;

    // Insert the updated stock
    Insert (pStock);
}

/**
* @brief Stock deletion in Binary Search Tree
*/
void BST::Delete (tStock * pStock)
{
    // delete the node after going to the appropriate position
    vRoot = DeleteNode (vRoot, pStock);
}

/**
* @brief Display Stock items and their quantity below a threshold quantity in binary seach tree
*/
void BST::Display (size_t pQuantityLimit) const
{
    PreOrderTraverse (vRoot, pQuantityLimit);
}

/**
* @brief Release all the stock data in binary seach tree
* @return New value of root of the Binary search tree
*/
tBSTNode * BST::Clear (tBSTNode * & pRoot)
{
    if (pRoot == nullptr) {
        return nullptr;
    }

    // release left subtree
    if (pRoot->uLeftNode != nullptr) {
        pRoot->uLeftNode  = Clear (pRoot->uLeftNode);
    }
    
    // release right subtree
    if (pRoot->uRightNode != nullptr) {
        pRoot->uRightNode = Clear (pRoot->uLeftNode);
    }
    
    // release stock data in curr node
    delete (pRoot->uData);
    pRoot->uData = nullptr;
    
    // release curr node
    delete pRoot;
    pRoot = nullptr;

    return pRoot;
}

/**
* @brief Preorderly display all stocks data in binary seach tree below a threshold quantity
*/
void BST::PreOrderTraverse (tBSTNode * pNode, size_t pQuantityLimit) const
{
    if (pNode == nullptr) {
        return;
    }

    PreOrderTraverse (pNode->uLeftNode);
    
    if (pNode->uData->uQuantity <= pQuantityLimit) {
        printf ("->%s:\t", pNode->uData->uStock.GetString ());

        printf ("%zu\n", pNode->uData->uQuantity);
    }

    PreOrderTraverse (pNode->uRightNode);
}

/**
* @brief Stock deletion in Binary Search Tree
* Find the replacement of the node to be deleted at the leafnode of the right sub tree of the node,
* or, the right node when left branch of the right node, does not exists.
* Keep updating the value of each hierarchical parent node of the node to be deleted recursively
* @return New value of root of the Binary search tree after deletion
*/
tBSTNode * BST::DeleteNode (tBSTNode * pNode, tStock * pStock)
{
        tBSTNode * replacement;
        tBSTNode * replacements_parent;

    if (pNode == nullptr) {
        return nullptr;
    }

    if (pStock->uQuantity < pNode->uData->uQuantity) {          // validation for left traversal
        pNode->uLeftNode = DeleteNode (pNode->uLeftNode, pStock);
        return pNode;

    } else if (pStock->uQuantity > pNode->uData->uQuantity) {   // validation for left traversal
        pNode->uRightNode = DeleteNode (pNode->uRightNode, pStock);
        return pNode;
    }
    
    if (pNode->uLeftNode == nullptr) {                          // No Left Subtree
        tBSTNode * next_node = pNode->uRightNode;
        
        delete pNode;
        
        return next_node;

    } else if (pNode->uRightNode == nullptr) {                  // No Right Subtree
        tBSTNode * next_node = pNode->uLeftNode;
        
        delete pNode;
        
        return next_node;
    }
    
    // Both (left and right) subtree exists

    replacements_parent = pNode;
    replacement         = replacements_parent->uRightNode;

    // get the last value in the leftmost node in the right sub tree
    while (replacement->uLeftNode != nullptr) {

        replacements_parent = replacement;
        replacement         = replacement->uLeftNode;
    }

    if (replacements_parent == pNode) {         // no leftmost node in the rightmost subtree
        replacements_parent->uRightNode = replacement->uRightNode;
    
    } else {
        replacements_parent->uLeftNode = replacement->uRightNode;
    }
 
    // Update the Node data for deletion by changing data of some other node
    pNode->uData = replacement->uData;
 
    // Delete replacement and return for updation
    delete replacement;

    return pNode;
}
