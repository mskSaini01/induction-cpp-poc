#ifndef BST_NODE_HPP
#define BST_NODE_HPP

/**
* @class Node of Self Balancing Tree
*/
template <typename Type>
struct tAVLNode {

  public:

    // @name: Constructors 
                            tAVLNode    (Type pData);

    // @name: Destructors
                            ~tAVLNode   ();

    // @name: Data Memeber
    int                     uHeight;
    Type                    uData;
    tAVLNode<Type> *        uLeftNode;          // Left Child of the Node
    tAVLNode<Type> *        uRightNode;         // Right Child of the Node
    tAVLNode<Type> *        uPrevNode;          // Predecessor Node
    tAVLNode<Type> *        uNextNode;          // Successor Node
};

#include "avl_node.hxx"

#endif // !BST_NODE_HPP
