#ifndef MEMORY_FOOTER_HPP
#define MEMORY_FOOTER_HPP

#include "macro.hpp"
#include "memory_manager.hpp"
#include "memory_header.hpp"

#define     MEMORY_FOOTER_SIZE      sizeof (tMemoryFooter)

struct tMemoryHeader;

struct tMemoryFooter {
                    /**
                    * @brief Memory Footer Constructor
                    */
                    tMemoryFooter  (tMemoryHeader * pPrevHeader = nullptr, tMemoryHeader * pBlockHeader = nullptr);

                    /**
                    * @brief Memory Footer Distructor
                    */
                    ~tMemoryFooter ();

    tMemoryHeader * uPrevHeader;    // available memory header before the current free memory
    tMemoryHeader * uBlockHeader;   // previous block of data in chunk for coalescing
};

#endif // !MEMORY_FOOTER_HPP
