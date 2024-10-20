#include "memory_footer.hpp"

/**
* @brief Memory Footer Constructor
*/
tMemoryFooter::tMemoryFooter (tMemoryHeader * pPrevHeader, tMemoryHeader * pBlockHeader)
{
    uPrevHeader  = pPrevHeader;
    uBlockHeader = pBlockHeader;
}

/**
* @brief Memory Footer Distructor
*/
tMemoryFooter::~tMemoryFooter ()
{
    uPrevHeader  = nullptr;
    uBlockHeader = nullptr;
}
