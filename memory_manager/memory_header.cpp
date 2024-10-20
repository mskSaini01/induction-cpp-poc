#include "memory_header.hpp"

/**
* @brief Memory Header Constructor
*/
tMemoryHeader::tMemoryHeader (size_t pMemSize, tMemoryHeader * pPrevHeader)
{
    uMemSize    = pMemSize;
    uPrevHeader = pPrevHeader;
}

/**
* @brief Memory Header Distructor
*/
tMemoryHeader::~tMemoryHeader ()
{
    uMemSize    = 0;
    uPrevHeader = nullptr;
}
