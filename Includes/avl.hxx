#include "avl.hpp"
#include <iostream>

/**
* @brief Double Threaded Self Balancing Tree Constructor
*/
template <typename Type>
AVL<Type>::AVL (Deleter<Type> pDeleter, Render<Type> pRender) :
    vRoot(nullptr), vDeleter(pDeleter), vRender(pRender)
{
    vThreadManager = new (std::nothrow) tAVLNode<Type>(Type ());
}

/**
* @brief Double Threaded Self Balancing Tree Destructor
*/
template<typename Type>
AVL<Type>::~AVL ()
{
    //Release all the memory in the tree
    Clear ();
    
    if (vThreadManager != nullptr) {

        delete vThreadManager;
    }

    vThreadManager = nullptr;
    vDeleter       = nullptr;
    vRender        = nullptr;
}

/**
* @brief Inserts a new node with the specified data into the AVL tree.
* @param pData The data to be inserted into the tree.
* @return true if the insertion is successful; otherwise false.
*/
template<typename Type>
bool AVL<Type>::Insert (Type pData) noexcept
{
        tAVLNode<Type> * new_node       = new (std::nothrow) tAVLNode <Type> (pData);
        bool             is_root_null   = false;

    // memory allocation failure
    if (new_node == nullptr) {

        return false;
    }

    is_root_null = (vRoot == nullptr);

    vRoot = InsertNode (vRoot, new_node);

    if (is_root_null && (vThreadManager != nullptr)) {

        // update root
        vRoot->uNextNode = vThreadManager;
        vRoot->uPrevNode = vThreadManager;

        // update thread manager
        vThreadManager->uNextNode = vRoot;
        vThreadManager->uPrevNode = vRoot;
    }

    return true;
}

/**
* @brief Updates the data in the AVL tree by replacing the node with the node with specified data.
* @param pData The data of the node to be updated.
* @param pNewData The new data to replace the existing data.
* @return true if the update is successful; otherwise false.
*/
template<typename Type>
bool AVL<Type>::Update (Type pData, Type pNewData)
{
    // Existance Check + Delete that node with pData
    if (Delete (pData) == false) {

        return false;
    }

    // Insert the updated node
    if (Insert (pNewData) == false) {

        return false;
    }

    return true;
}

/**
* @brief Checks if a node with the specified data is present in the AVL tree.
* @param pData The data to be checked for existence.
* @return true if the data is present; otherwise false.
*/
template<typename Type>
bool AVL<Type>::IsPresent (Type pData) const noexcept
{
        tAVLNode<Type> * curr_node = vRoot;

    if (vRoot == nullptr) {

        return false;
    }
    
    // iterate to the appropriate position for insertion based on stock quantity
    while (curr_node != nullptr) {

        if (pData == curr_node->uData) {

            return true;
        }
        if (pData < curr_node->uData) {

            curr_node = curr_node->uLeftNode;
        
        } else {
            curr_node = curr_node->uRightNode;
        }
    }

    return false;
}

/**
* @brief Deletes a node with the specified data from the AVL tree using a custom deleter.
* @param pData The data of the node to be deleted.
* @param pDeleter The custom deleter function for data cleanup.
* @return true if the deletion is successful; otherwise false.
*/
template<typename Type>
bool AVL<Type>::Delete (Type pData, Deleter<Type> pDeleter)
{
    // Existance check
    if (IsPresent(pData) == false) {

        return false;
    }

    if (vDeleter != nullptr && pDeleter != nullptr) {

        vDeleter = pDeleter;
    }

    // delete the node after going to the appropriate position
    vRoot = DeleteNode (vRoot, pData);

    return true;
}

/**
* @brief Displays the AVL tree in either forward or reverse order using threads.
* @param pReverseOrder If true, displays the tree in reverse order; otherwise, in forward order.
*/
template<typename Type>
void AVL<Type>::Display (bool pRevereOreder) const noexcept
{
        tAVLNode<Type> * curr_node;

    // memory allocation failure
    if (vThreadManager == nullptr) {

        return;
    }

    if (pRevereOreder) {
        curr_node = vThreadManager->uPrevNode;
    }
    else {
        curr_node = vThreadManager->uNextNode;
    }

    // traverse in the list of nodes using threads
    while (curr_node != vThreadManager) {
    
        if (vRender == nullptr) {

            std::cout << curr_node->uData;
    
        } else {

            vRender (curr_node->uData);
        }

        
        if (pRevereOreder) {
            curr_node = curr_node->uPrevNode;
        }
        else {
            curr_node = curr_node->uNextNode;
        }
    }
}

/**
* @brief Clears the AVL tree, deallocating all nodes and data.
*/
template<typename Type>
void AVL<Type>::Clear ()
{
        tAVLNode<Type> * curr_node;
        tAVLNode<Type> * next_node;

    // memory allocation failure
    if (vThreadManager == nullptr) {

        return;
    }

    curr_node = vThreadManager->uNextNode;

    // traverse in the list of nodes using threads
    while (curr_node != vThreadManager) {

        next_node = curr_node->uNextNode;
        
        ReleaseNode (curr_node);
        
        curr_node = next_node;
    }
}

/**
* @brief Deletes a node with the specified data from the AVL tree and returns the updated tree.
* @param pNode The root of the tree being processed.
* @param pData The data to be deleted.
* @return The root of the updated AVL tree after deletion.
*/
template<typename Type>
tAVLNode<Type> * AVL<Type>::DeleteNode (tAVLNode<Type> * pNode, Type pData)
{
        tAVLNode<Type> * replacement;
        tAVLNode<Type> * replacements_parent;

    if (pNode == nullptr) {

        return nullptr;
    }

    if (pData == pNode->uData) {

        if (pNode->uLeftNode == nullptr) {

            // No Left Subtree
            replacement = pNode->uRightNode;

            // update thread
            pNode->uNextNode->uPrevNode = pNode->uPrevNode;
            pNode->uPrevNode->uNextNode = pNode->uNextNode;
 
            ReleaseNode (pNode);
        
            return replacement;

        } else if (pNode->uRightNode == nullptr) {

            // No Right Subtree
            replacement = pNode->uLeftNode;
        
            // update thread
            pNode->uNextNode->uPrevNode = pNode->uPrevNode;
            pNode->uPrevNode->uNextNode = pNode->uNextNode;

            ReleaseNode (pNode);
        
            return replacement;
        }

        // Both (left and right) subtree exists

        replacements_parent = pNode;
        replacement         = replacements_parent->uRightNode;

        UpdateReplacements (pNode, replacement, replacements_parent);
 
        // delete the data
        if (vDeleter != nullptr) {

            vDeleter (pNode->uData);
        }

        // Update the Node data for deletion by changing data of some other node
        pNode->uData = replacement->uData;
    
        // update the height of the node at deleted node's position
        if ((pNode->uLeftNode->uHeight + 1) > pNode->uRightNode->uHeight) {

            pNode->uHeight = (pNode->uLeftNode->uHeight + 1);
    
        } else {
            pNode->uHeight = pNode->uRightNode->uHeight;
        }

        // update thread
        replacement->uNextNode->uPrevNode = replacement->uPrevNode;
        replacement->uPrevNode->uNextNode = replacement->uNextNode;
 
        // Delete replacement and return for updation
        ReleaseNode (replacement);

        return pNode;

    } else if (pData < pNode->uData) {

        // left traversal
        pNode->uLeftNode = DeleteNode (pNode->uLeftNode, pData);

    } else if (pData > pNode->uData) {

        // Right traversal
        pNode->uRightNode = DeleteNode (pNode->uRightNode, pData);
    }

    pNode = GetBalancedSubTree (pNode);

    UpdateHeight (pNode);

    return pNode;
}

/**
* @brief Releases a node, including its data, from the AVL tree.
* @param pNode The Refeerence of node to be released.
*/
template<typename Type>
void AVL<Type>::ReleaseNode (tAVLNode<Type> * & pNode)
{
    if (vDeleter != nullptr) {

        vDeleter (pNode->uData);
    }

    pNode->uPrevNode->uNextNode = pNode->uNextNode;
    pNode->uNextNode->uPrevNode = pNode->uPrevNode;

    delete pNode;
    pNode = nullptr;
}

/**
* @brief Inserts a new node into the AVL tree and returns the updated tree.
* @param pNode The root of the tree being processed.
* @param pSource The new node to be inserted.
* @return The root of the updated AVL tree after insertion.
*/
template<typename Type>
tAVLNode<Type> * AVL<Type>::InsertNode (tAVLNode<Type> * pNode, tAVLNode<Type> * pSource) noexcept
{
    if (pNode == nullptr) {

        return pSource;
    }

    if (pSource->uData <= pNode->uData) {
        
        // left traversal
        pNode->uLeftNode = InsertNode (pNode->uLeftNode, pSource);

        if (pNode->uLeftNode->uPrevNode == nullptr) {

            // update the links between the new node and its parent
            pSource->uNextNode = pNode;
            pSource->uPrevNode = pNode->uPrevNode;
            pNode->uPrevNode   = pSource;
            
            if (pSource->uPrevNode != nullptr) {

                pSource->uPrevNode->uNextNode = pSource;
            }
        }
    
    } else {

        // Right traversal
        pNode->uRightNode = InsertNode (pNode->uRightNode, pSource);
    
        if (pNode->uRightNode->uPrevNode == nullptr) {
            
            // update the links between the new node and its parent
            pSource->uPrevNode = pNode;
            pSource->uNextNode = pNode->uNextNode;
            pNode->uNextNode   = pSource;
        
            if (pSource->uNextNode != nullptr) {

                pSource->uNextNode->uPrevNode = pSource;
            }
        }
    }

    pNode = GetBalancedSubTree (pNode);
    
    UpdateHeight (pNode);

    return pNode;
}

/**
* @brief Balances the AVL tree by performing rotations based on the balance factors.
* @param pNode The root of the tree being processed.
* @return The root of the tree after balancing.
*/
template<typename Type>
tAVLNode<Type> * AVL<Type>::GetBalancedSubTree (tAVLNode<Type> * pNode)  noexcept
{
        int node_balance = GetBalance (pNode);

    if (node_balance == 2 && GetBalance(pNode->uLeftNode) == 1) {

        return RotateLLTree (pNode);
    
    } else if (node_balance == 2 && GetBalance(pNode->uLeftNode) == -1) {
        
        return RotateLRTree (pNode);

    } else if (node_balance == -2 && GetBalance(pNode->uRightNode) == -1) {
        
        return RotateRRTree (pNode);

    } else if (node_balance == -2 && GetBalance(pNode->uRightNode) == 1) {
        
        return RotateRLTree (pNode);
    }

    return pNode;
}

/**
* @brief Performs rotation on the branch of left-left structure imbalance in the AVL tree
*        and returns the new root of the tree.
* @param pRoot The root of the tree being rotated.
* @return The new root of the tree after the left-left Tree.
*/
template<typename Type>
tAVLNode<Type> * AVL<Type>::RotateLLTree (tAVLNode<Type> * & pRoot) noexcept
{
        tAVLNode<Type> * left_child = pRoot->uLeftNode;

    pRoot->uLeftNode        = left_child->uRightNode;
    left_child->uRightNode  = pRoot;
    
    UpdateHeight (pRoot);
    UpdateHeight (left_child);

    // new root is the left child
    return left_child;
}

/**
* @brief Performs rotation on the branch of left-right structure imbalance in the AVL tree
*        and returns the new root of the tree.
* @param pRoot The root of the tree being rotated.
* @return The new root of the tree after the left-right rotation.
*/
template<typename Type>
tAVLNode<Type> * AVL<Type>::RotateLRTree (tAVLNode<Type> * & pRoot) noexcept
{
        tAVLNode<Type> * left_child             = pRoot->uLeftNode;
        tAVLNode<Type> * right_of_left_child    = left_child->uRightNode;

    pRoot->uLeftNode                = right_of_left_child->uRightNode;
    right_of_left_child->uRightNode = pRoot;

    left_child->uRightNode          = right_of_left_child->uLeftNode;
    right_of_left_child->uLeftNode  = left_child;

    UpdateHeight (left_child);
    UpdateHeight (pRoot);
    UpdateHeight (right_of_left_child);

    // new root is the right child of left child
    return right_of_left_child;
}

/**
* @brief Performs rotation on the branch of right-right structure imbalance in the AVL tree
*        and returns the new root of the tree.
* @param pRoot The root of the tree being rotated.
* @return The new root of the tree after the right-right rotation.
*/
template<typename Type>
tAVLNode<Type> * AVL<Type>::RotateRRTree (tAVLNode<Type> * & pRoot) noexcept
{
        tAVLNode<Type> * right_child = pRoot->uRightNode;

    pRoot->uRightNode       = right_child->uLeftNode;
    right_child->uLeftNode  = pRoot;
    
    UpdateHeight (pRoot);
    UpdateHeight (right_child);

    // new root is the right child
    return right_child;
}

/**
* @brief Performs rotation on the branch of right-left structure imbalance in the AVL tree
*        and returns the new root of the tree.
* @param pRoot The root of the tree being rotated.
* @return The new root of the tree after the right-left rotation.
*/
template<typename Type>
tAVLNode<Type> * AVL<Type>::RotateRLTree (tAVLNode<Type> * & pRoot) noexcept
{
        tAVLNode<Type> * right_child            = pRoot->uRightNode;
        tAVLNode<Type> * left_of_right_child    = right_child->uLeftNode;

    pRoot->uRightNode               = left_of_right_child->uLeftNode;
    left_of_right_child->uLeftNode  = pRoot;

    right_child->uLeftNode          = left_of_right_child->uRightNode;
    left_of_right_child->uRightNode = right_child;
    
    UpdateHeight (right_child);
    UpdateHeight (pRoot);
    UpdateHeight (left_of_right_child);

    // new root is the right child of left child
    return left_of_right_child;
}

/**
* @brief Gets the height of a given AVL node.
* @param pNode The AVL node for which height is to be determined.
* @return The height of the AVL node or 0 if the node is nullptr.
*/
template<typename Type>
int AVL<Type>::GetHeight (tAVLNode<Type> * & pNode) const noexcept
{
    if (pNode == nullptr) {

        return 0;
    }

    return pNode->uHeight;
}

/**
* @brief Gets the balance factor of a given AVL node.
* @param pNode The AVL node for which to calculate the balance factor.
* @return The balance factor of the AVL node, representing the height difference
*         between the left and right subtrees. Returns 0 if the node is nullptr.
*/
template<typename Type>
int AVL<Type>::GetBalance (tAVLNode<Type> * & pNode) const noexcept
{
    if (pNode == nullptr) {

        return 0;
    }

    // return the balance of the height difference in the children subtrees
    return (GetHeight (pNode->uLeftNode) - GetHeight (pNode->uRightNode));
}

/**
* @brief Updates the height of a given AVL node based on its children's heights.
* @param pNode The AVL node for which to update the height.
*/
template<typename Type>
void AVL<Type>::UpdateHeight (tAVLNode<Type> * & pNode) noexcept
{
    // both child exists
    if (pNode->uLeftNode != nullptr && pNode->uRightNode != nullptr) {
        
        if (pNode->uLeftNode->uHeight > pNode->uRightNode->uHeight) {

            pNode->uHeight = 1 + pNode->uLeftNode->uHeight;
            return;
    
        } else {

            pNode->uHeight = 1 + pNode->uRightNode->uHeight;
            return;
        }

    } else if (pNode->uLeftNode != nullptr) {       // only left child exists

        pNode->uHeight = 1 + pNode->uLeftNode->uHeight;
        return;

    } else if (pNode->uRightNode != nullptr) {      // only right child exists

        pNode->uHeight = 1 + pNode->uRightNode->uHeight;
        return;
    }

    pNode->uHeight = 1;                             // no child exists
}

/**
* @brief Updates the replacement node during the deletion process.
* @param pNode The parent node from which the replacement node is being deleted.
* @param replacement The replacement node whose height needs to be updated.
* @param replacements_parent The parent of the replacement node.
* @note The method traverses the leftmost path in the right subtree of the replacement node
*       to find the last node for as a replacement for the node to be deleted, updating heights accordingly.
*       It also adjusts the link to the parent's left or right child as needed.
*/
template<typename Type>
void AVL<Type>::UpdateReplacements (tAVLNode<Type> * & pNode, tAVLNode<Type> * & replacement,
                                    tAVLNode<Type> * & replacements_parent) noexcept
{
    // get the last value in the leftmost node in the right sub tree for replacement of the node to be deleted
    while (replacement->uLeftNode != nullptr) {

        // update the height of the current node (replacement)
        if (replacement->uRightNode != nullptr) {

            // chack if left subtree's height after deletion is greater than right subtree's height
            if ((replacement->uLeftNode->uHeight - 1) > replacement->uRightNode->uHeight) {

                pNode->uHeight = pNode->uLeftNode->uHeight;
    
            } else {

                pNode->uHeight = 1 + pNode->uRightNode->uHeight;
            }
        
        } else {            // update height according to the left subtree, as no right subtree exists

            replacement->uHeight = replacement->uLeftNode->uHeight;
        }

        replacements_parent = replacement;
        replacement         = replacement->uLeftNode;
    }

    if (replacements_parent == pNode) {         // no leftmost node in the right subtree of pNode

        replacements_parent->uRightNode = replacement->uRightNode;

    } else {

        replacements_parent->uLeftNode = replacement->uRightNode;
    }
}
