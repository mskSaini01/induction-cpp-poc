#ifndef MEMORY_CHUNK_HPP
#define MEMORY_CHUNK_HPP

#include "macro.hpp"
#include "memory_manager.hpp"
#include "memory_header.hpp"

struct tMemoryChunk {
                    /**
                    * @brief Memory Chunk Constructor
                    */
                    tMemoryChunk  (size_t pChunkSize = BYTES_1024);

                    /**
                    * @brief Memory Chunk Distructor
                    */
                    ~tMemoryChunk ();

    void *          uBuffer;
    tMemoryHeader * uChunkHeader;
    tMemoryHeader * uChunkLastHeader;
    tMemoryChunk *  uNextChunk;
    tMemoryChunk *  uPrevChunk;
};

#endif // !MEMORY_CHUNK_HPP
