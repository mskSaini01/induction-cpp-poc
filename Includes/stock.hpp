#ifndef STOCK_HPP
#define STOCK_HPP

#include "string.hpp"

struct tStock {
    
  public:

    // @name: Constructors 
                tStock (const char * pItem, size_t pQuantity);

    // @name: Data Memeber
    String      uStock;
    size_t      uQuantity;
};

#endif // !STOCK_HPP
