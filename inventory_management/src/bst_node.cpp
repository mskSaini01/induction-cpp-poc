#include "bst_node.hpp"

tBSTNode::tBSTNode (tStock * pStock)
{
    uData       = pStock;
    uLeftNode   = nullptr;
    uRightNode  = nullptr;
}

tBSTNode::~tBSTNode ()
{
    uData       = nullptr;
    uLeftNode   = nullptr;
    uRightNode  = nullptr;
}
