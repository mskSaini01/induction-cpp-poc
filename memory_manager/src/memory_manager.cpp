#include "memory_manager.hpp"

// static initializations
size_t          MemoryManager:: sBufferSize     = BYTES_1024;

/**
* @brief Memory Manager Distructor
*/
MemoryManager::~MemoryManager ()
{
        tMemoryChunk * curr_memory_chunk = vChunks;
        tMemoryChunk * next_memory_chunk = nullptr;

    while (curr_memory_chunk) {
        // Get The next node
        next_memory_chunk = curr_memory_chunk->uNextChunk;

        // free curr_memory_chunk's buffer;
        free (curr_memory_chunk->uBuffer);
        curr_memory_chunk->uBuffer = nullptr;

        // free curr_memory_chunk;
        free (curr_memory_chunk);

        curr_memory_chunk = next_memory_chunk;
    }

    vFreeListPtr = nullptr;
    vChunks      = nullptr;
}

/**
* @brief Allocates a number of bytes of memory buffer
* @return a pointer to dynamically allocated memory is allocated; otherwise nullptr
*/
void * MemoryManager::Malloc (size_t pBytes)
{
        tMemoryHeader * prev_free_header    = nullptr;  // the one who points to the free header
        tMemoryHeader * free_header         = nullptr;  // available memory's header
        tMemoryFooter * free_footer         = nullptr;  // available memory's footer

        tMemoryFooter * old_free_footer     = nullptr;

    // no memory chunk found
    if (!vChunks) {
        return nullptr;
    }

    pBytes += (MEMORY_HEADER_SIZE - (pBytes % MEMORY_HEADER_SIZE));

    if (pBytes > sBufferSize) {
        return nullptr;
    }

    // get the available block by the traversing free memory blocks and update the prev_free_header
    free_header = GetAvailableBlock (pBytes, prev_free_header);

    // extend memory buffer
    if (!free_header) {
        return AddMemChunk (prev_free_header);
    }

    // update the footer of the available memory block the new header
    free_footer = (tMemoryFooter *) ((char *) free_header +
                    (free_header->uMemSize * 3 * MEMORY_HEADER_SIZE) - MEMORY_FOOTER_SIZE);

    if (free_header->uMemSize > pBytes) {
        // allocate some memory in available block and return the pointer to the allocated memory's starting address
        return FragmentMemBlock (pBytes, free_header, free_footer);
    }

    // update the previous node to the address of the new header
    if (prev_free_header) {

        prev_free_header->uPrevHeader = free_header->uPrevHeader;

        // as whole free memory is occupied - remove the free_header's memory from the free list chain 
        old_free_footer = (tMemoryFooter *) ((char *) free_header +
                            (free_header->uPrevHeader->uMemSize * 3 * MEMORY_HEADER_SIZE) - MEMORY_FOOTER_SIZE);

        // update the footer of free header's next free memory with memory freed after free_header (prev_free_header)
        old_free_footer->uPrevHeader = prev_free_header;
    }

    // update free header's details
    free_header->uMemSize    = pBytes;
    free_header->uPrevHeader = nullptr;
    free_footer->uPrevHeader = nullptr;

    return (void *) (free_header + 1);
}

/**
* @brief Add new Memory Chunk when more memory is required
* @return pointer to free memory block if allocated; otherwise nullptr
*/
void * MemoryManager::AddMemChunk (tMemoryHeader * & pFreeHeader)
{
        tMemoryChunk *  new_buffer          = nullptr;

    new_buffer  = (tMemoryChunk *) malloc (sizeof (tMemoryChunk));

    if (!new_buffer) {
        return nullptr;
    }

    *new_buffer = tMemoryChunk (sBufferSize);

    vCurrentChunk->uNextChunk   = new_buffer;
    new_buffer->uPrevChunk      = vCurrentChunk;

    // update current chunk
    vCurrentChunk               = new_buffer;

    // update free list pointer with 1st header of the free memory block (NOTE - not the chunk header)
    pFreeHeader = (tMemoryHeader *) new_buffer->uChunkHeader;
    pFreeHeader++;

    pFreeHeader->uPrevHeader = vFreeListPtr;
    vFreeListPtr = pFreeHeader;

    return (void *) (vFreeListPtr + 1);
}

/**
* @brief Add Memory block for pBytes inside a memory block
* @return pointer to allocated memory
*/
void * MemoryManager::FragmentMemBlock (size_t pBytes, tMemoryHeader * & pFreeHeader, tMemoryFooter * & pFreeFooter)
{
        tMemoryHeader * new_header          = nullptr;
        tMemoryFooter * new_footer          = nullptr;

    // Get the new header address and add header for the remaining memory in available header block
    new_header  = (tMemoryHeader * ) ((char *) pFreeHeader +
                    (pFreeHeader->uMemSize * 3 * MEMORY_HEADER_SIZE) - (pBytes * 3 * MEMORY_HEADER_SIZE));

    *new_header = tMemoryHeader (pBytes);

    // Get the new footer address and add footer pointing to available header block
    new_footer  = (tMemoryFooter * ) ((char *) new_header - MEMORY_FOOTER_SIZE);
    *new_footer = tMemoryFooter (pFreeFooter->uPrevHeader, pFreeHeader);

    // update the old footer's header with new header build at the end of the free memory
    pFreeFooter->uBlockHeader = new_header;

    // update the old footer's previous header with nullptr as footer's associated memory is occupied
    pFreeFooter->uPrevHeader  = nullptr;

    // update free header's details
    pFreeHeader->uMemSize    -= pBytes;

    return (void *) (new_header + 1);
}

/**
* @brief Allocates a number of bytes of memory buffer with some default values
* @return a pointer to dynamically allocated memory is allocated; otherwise nullptr
*/
void * MemoryManager::Calloc (size_t pObjectCount, size_t pObjectByte)
{
        void * memory = Malloc (pObjectCount * pObjectByte);

    if (!memory) {
        return nullptr;
    }

    // set 0 as default value
    memset (memory, 0, pObjectCount * pObjectByte);

    return memory;
}

/**
* @brief Checks for memory availablity in memory buffer
* @return true of memory is available the initial block of memory; otherwise false
*/
tMemoryHeader * MemoryManager::GetAvailableBlock (size_t pBytes, tMemoryHeader * & pPrevFreeHeader) const
{
        tMemoryHeader * curr_header = vFreeListPtr;

    // iterate over memory chunks
    while (curr_header != vFreeListBreak) {
        if (curr_header->uMemSize >= pBytes) {
            return curr_header;
        }

        pPrevFreeHeader = curr_header;
        curr_header     = curr_header->uPrevHeader;
    }
    return nullptr;
}

/**
* @brief free the a memory chunk from memory buffer
* @return true if memory is freed; otherwise false
*/
void MemoryManager::Free (void * pSource)
{
        tMemoryHeader * block_header = nullptr;
        tMemoryFooter * block_footer = nullptr;
        tMemoryHeader * curr_header  = nullptr;

    if (pSource == nullptr) {
        return;
    }

    block_header = (tMemoryHeader *) ((char*) pSource - MEMORY_HEADER_SIZE);
    block_footer = (tMemoryFooter *) ((char *) block_header +
                    (block_header->uMemSize * 3 * MEMORY_HEADER_SIZE) - MEMORY_FOOTER_SIZE);

    curr_header = block_header;

    // double free
    if (block_header->uMemSize == 0) {
        return;
    }

    // coalesce left block if possible
    LeftCoalesce (block_header, block_footer);

    // coalesce right block if possible
    RightCoalesce (block_header, block_footer);

    curr_header->uMemSize = 0;
}

/**
* @brief Coalesce left memory block with a specific memory block if possible
*/
void MemoryManager::LeftCoalesce (tMemoryHeader * & pBlockHeader, tMemoryFooter * & pBlockFooter)
{
        tMemoryFooter * prev_footer       = (tMemoryFooter *) ((char *) pBlockHeader - MEMORY_FOOTER_SIZE);
        tMemoryFooter * free_list_footer  = (tMemoryFooter *) ((char *) vFreeListPtr +
                                             (vFreeListPtr->uMemSize * 3 * MEMORY_HEADER_SIZE) - MEMORY_FOOTER_SIZE);

    // check for previous block exists
    if (prev_footer->uBlockHeader == nullptr) {
        return;
    }

    // check for previous block availablility
    if (prev_footer->uBlockHeader->uPrevHeader != nullptr) {

        //update the size of the previous HEADER
        prev_footer->uBlockHeader->uMemSize += pBlockHeader->uMemSize;

        //update the block footer with the previous footer
        pBlockFooter->uPrevHeader  = prev_footer->uPrevHeader;
        pBlockFooter->uBlockHeader = prev_footer->uBlockHeader;

        // update block header
        pBlockHeader = prev_footer->uBlockHeader;

    } else {
        // update current free list pointer's footer
        free_list_footer->uPrevHeader = pBlockHeader;

        // update free list pointer
        pBlockHeader->uPrevHeader     = vFreeListPtr;
        vFreeListPtr                  = pBlockHeader;
    }
}

/**
* @brief Coalesce right memory block with a specific memory block if possible
*/
void MemoryManager::RightCoalesce (tMemoryHeader * & pBlockHeader, tMemoryFooter * & pBlockFooter)
{
        tMemoryHeader * next_header             = nullptr;
        tMemoryFooter * next_footer             = nullptr;
        tMemoryFooter * nexts_old_free_footer   = nullptr;

    next_header  = (tMemoryHeader *) ((char *) pBlockFooter + MEMORY_FOOTER_SIZE);

    // check for next block existance
    if (next_header->uPrevHeader == nullptr) {
        return;
    }

    pBlockHeader->uMemSize    += next_header->uMemSize;
    pBlockHeader->uPrevHeader = next_header->uPrevHeader;

    nexts_old_free_footer = (tMemoryFooter *) ((char *) vFreeListPtr +
                                (vFreeListPtr->uMemSize* 3 * MEMORY_HEADER_SIZE) - MEMORY_FOOTER_SIZE); 

    if (nexts_old_free_footer->uPrevHeader != nullptr) {
        nexts_old_free_footer->uPrevHeader = pBlockHeader;
    }

    next_footer = (tMemoryFooter *) ((char *) next_header +
                    (next_header->uMemSize * 3 * MEMORY_HEADER_SIZE) - MEMORY_FOOTER_SIZE);

    // update the footer block pointer
    next_footer->uBlockHeader = pBlockHeader;

    // update the block's prevHeader pointing to previous free memory to block header
    if (next_footer->uPrevHeader != nullptr) {
        next_footer->uPrevHeader->uPrevHeader = pBlockHeader;
    }

    // update free list pointer when vFreePtr points to the right memory block
    if (vFreeListPtr == next_header) {
        next_header->uPrevHeader = pBlockHeader;
        vFreeListPtr             = pBlockHeader;
    }
}

/**
* @brief Get singleton object of MemoryManager
* @return singleton object pointer if initialted; otherwise nullptr
*/
MemoryManager * MemoryManager::GetInstance ()
{
        static MemoryManager singleton_obj (sBufferSize);

    return &singleton_obj;
}

/**
* @brief Memory Manager Constructor
*/
MemoryManager::MemoryManager (size_t pRequestedBytes)
{
    vFreeListPtr = nullptr;
    vChunks      = nullptr;

    // Get a new big chunk of memory for pooling
    vChunks  = (tMemoryChunk *) malloc (sizeof (tMemoryChunk));

    if (vChunks) {
        // Initialize chunk
        *vChunks = tMemoryChunk (pRequestedBytes);

        // free memory is at Starting of the chunk
        vFreeListPtr   = ((tMemoryHeader *) vChunks->uChunkHeader) + 1;
        vFreeListBreak = (tMemoryHeader *) vChunks->uChunkHeader;

    } else {
        // used for check for memory manager initiation
        vFreeListPtr   = nullptr;
        vFreeListBreak = nullptr;
    }
    vCurrentChunk   = vChunks;
}

void * operator new (size_t pBytes)
{
    return MemoryManager::GetInstance ()->Malloc (pBytes);
}

void operator delete (void * pSource)
{
    return MemoryManager::GetInstance ()->Free (pSource);
}
