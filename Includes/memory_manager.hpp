#ifndef MEMORY_MANAGER_HPP
#define MEMORY_MANAGER_HPP

#include <memory>
#include "macro.hpp"
#include "memory_header.hpp"
#include "memory_footer.hpp"
#include "memory_chunk.hpp"

/** Time (speed) Based Approach
* Malloc:  O(n)    - first fit approach (allocation at first free memory)
* Free:    O(1)
* Could optimize the memory management with (best fit) but the Free will take O(n)
*  (allocate the memory with least possible memory size - by updating free nodes)
*  (by traversing the freed node and replace the prev freed address with the address of the node to be freed)
*/

// memory allocation from block
#define Malloc_(pBytes) \
        MemoryManager::GetInstance ()->Malloc (pBytes);

// memory allocation from block
#define Calloc_(pNum, pSize) \
        MemoryManager::GetInstance ()->Calloc (pNum, pSize);

// free memory from block
#define Free_(pPointer) \
        MemoryManager::GetInstance ()->Free (pPointer)

struct tMemoryHeader;
struct tMemoryFooter;
struct tMemoryChunk;

class MemoryManager {

  public:
            /**
            * @brief Memory Manager Distructor
            */
                            ~MemoryManager          ();

            /**
            * @brief Allocates a number of bytes of memory buffer
            * @return a pointer to dynamically allocated memory is allocated; otherwise nullptr
            */
            void *          Malloc              (size_t pBytes);

            /**
            * @brief Allocates a number of bytes of memory buffer with some default values
            * @return a pointer to dynamically allocated memory is allocated; otherwise nullptr
            */
            void *          Calloc              (size_t pObjectCount, size_t pObjectByte);

            /**
            * @brief free the a memory chunk from memory buffer
            * @return true if memory is freed; otherwise false
            */
            void            Free                (void * pSource);

            /**
            * @brief Checks for memory availablity in memory buffer
            * @return true of memory is available the initial block of memory; otherwise false
            */
            tMemoryHeader * GetAvailableBlock   (size_t pBytes, tMemoryHeader * & pPrevFreeHeader)  const;

            /**
            * @brief Get singleton object of MemoryManager
            * @return singleton object pointer if initialted; otherwise nullptr
            */
    static  MemoryManager * GetInstance         ();

  private:

            /**
            * @brief Memory Manager Constructor
            */
                            MemoryManager           (size_t pRequestedBytes = BYTES_1024);

            /**
            * @brief Add new Memory Chunk when more memory is required
            * @return pointer to free memory block if allocated; otherwise nullptr
            */
            void *          AddMemChunk             (tMemoryHeader * & pFreeHeader);

            /**
            * @brief Add Memory block for pBytes inside a memory block
            * @return pointer to allocated memory
            */
            void *          FragmentMemBlock        (size_t pBytes, tMemoryHeader * & pFreeHeader, tMemoryFooter * & pFreeFooter);

            /**
            * @brief Coalesce left memory block with a specific memory block if possible
            */
            void            LeftCoalesce            (tMemoryHeader * & pBlockHeader, tMemoryFooter * & pBlockFooter);

            /**
            * @brief Coalesce right memory block with a specific memory block if possible
            */
            void            RightCoalesce           (tMemoryHeader * & pBlockHeader, tMemoryFooter * & pBlockFooter);

            tMemoryHeader * vFreeListPtr;
            tMemoryHeader * vFreeListBreak;

            tMemoryChunk *  vChunks;
            tMemoryChunk *  vCurrentChunk;

    static  size_t          sBufferSize;
};

void * operator new (size_t pBytes);

void operator delete (void * pSource);

#endif // !MEMORY_MANAGER_HPP
