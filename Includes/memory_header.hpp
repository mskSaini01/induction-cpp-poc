#ifndef MEMORY_HEADER_HPP
#define MEMORY_HEADER_HPP

#include "macro.hpp"
#include "memory_manager.hpp"

#define     MEMORY_HEADER_SIZE      sizeof (tMemoryHeader)

struct tMemoryHeader {
                    /**
                    * @brief Memory Header Constructor
                    */
                    tMemoryHeader  (size_t pMemSize = BYTES_1024, tMemoryHeader * pPrevHeader = nullptr);

                    /**
                    * @brief Memory Header Distructor
                    */
                    ~tMemoryHeader ();

    size_t          uMemSize;       // possible requested memory
    tMemoryHeader * uPrevHeader;    // previous block of data in chunk for coalescing
};

#endif // !MEMORY_HEADER_HPP
