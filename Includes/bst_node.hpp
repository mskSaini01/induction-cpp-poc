#ifndef BST_NODE_HPP
#define BST_NODE_HPP

#include "stock.hpp"

struct tBSTNode {

  public:

    // @name: Constructors 
                    tBSTNode  (tStock * pStock);

    // @name: Destructors
                    ~tBSTNode ();

    // @name: Data Memeber
    tStock *        uData;
    tBSTNode *      uLeftNode;
    tBSTNode *      uRightNode;
};

#endif // !BST_NODE_HPP
