#include "memory_chunk.hpp"

/**
* @brief Memory Chunk Constructor
*/
tMemoryChunk::tMemoryChunk (size_t pRequestedBytes)
{
        // worst case (allocations of 1 byte data)
        // -> chunk header + chunk footer + (memory header + data for 1 bytes + memory footer) * requested bytes
        size_t          chunk_memory_size   = ((2 * MEMORY_HEADER_SIZE) + (MEMORY_HEADER_SIZE * 3 * pRequestedBytes));

        void *          chunk_end           = nullptr;

        tMemoryHeader * free_memory_header  = nullptr;
        tMemoryFooter * free_memory_footer  = nullptr;

    uBuffer = malloc (chunk_memory_size);

    // Memory Allocation failure
    if (!uBuffer) {
        uChunkHeader        = nullptr;
        uChunkLastHeader    = nullptr;
        uNextChunk          = nullptr;
        uPrevChunk          = nullptr;

    } else {

        // Add Chunk Header at beginning
        uChunkHeader  = (tMemoryHeader *) uBuffer;
        *uChunkHeader = tMemoryHeader (pRequestedBytes);

        // Set Chunk End
        chunk_end = (void *)((char *) (uBuffer) + chunk_memory_size);

        uChunkLastHeader  = (tMemoryHeader *) ((char *) (chunk_end) - MEMORY_FOOTER_SIZE);
        *uChunkLastHeader = tMemoryHeader (0);

        // Assign the first header for the free memory in chunk
        free_memory_header  = (tMemoryHeader *) ((char *) (uBuffer) + MEMORY_HEADER_SIZE);
        *free_memory_header = tMemoryHeader (pRequestedBytes, uChunkHeader);

        // Assign the first footer for the free memory in chunk
        free_memory_footer  = (tMemoryFooter *) ((char *) (chunk_end) - MEMORY_FOOTER_SIZE);
        *free_memory_footer = tMemoryFooter (free_memory_header);

        uNextChunk = nullptr;
        uPrevChunk = nullptr;
    }
}

/**
* @brief Memory Chunk Distructor
*/
tMemoryChunk::~tMemoryChunk ()
{
    uChunkHeader = nullptr;
    uNextChunk   = nullptr;
    uPrevChunk   = nullptr;
}