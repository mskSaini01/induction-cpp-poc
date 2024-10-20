#include "avl_node.hpp"

template<typename Type>
tAVLNode<Type>::tAVLNode (Type pData):
    uData (pData), uHeight (1), uLeftNode (nullptr), uRightNode (nullptr), uNextNode (nullptr), uPrevNode (nullptr)
{
}

template<typename Type>
tAVLNode<Type>::~tAVLNode ()
{
    uLeftNode  = nullptr;
    uRightNode = nullptr;
    uNextNode  = nullptr;
    uPrevNode  = nullptr;
}
