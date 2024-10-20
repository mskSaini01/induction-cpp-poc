#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <memory>           // malloc
#include "profiler.hpp"     // INIT_PROFILER, START_PROFILER, END_PROFILER;

// Initiates Memory Manager
#define InitMemManager(pBytes) \
        if (Allocator::IsInitiated ()) { \
            exit (0); \
        } \
        Allocator::SetBufferSize (pBytes); \
        Allocator obj = *Allocator::GetInstance (); \
        Allocator::SetInitiated (true);
        
// memory allocation from block
#define Malloc_(pBytes) \
        obj.Malloc (pBytes);

// free memory from block
#define Free_(pPointer) \
        obj.Free (pPointer)

struct tMemoryBlock {
            /**
            * @brief Allocates buffer pages info
            */
            tMemoryBlock  (size_t pBytes);
            
            /**
            * @brief Deallocates buffer pages info
            */
            ~tMemoryBlock ();

    void *  uBuffer;
    void *  uMemoryEnd;
    void *  uBufferEnd;
};

class Allocator {

  public:
            /**
            * @brief Deallocates memory buffer
            */
                            ~Allocator          ();

            /**
            * @brief Allocates a number of bytes of memory buffer
            * @return a pointer to dynamically allocated memory is allocated; otherwise nullptr
            */
            void *          Malloc              (size_t pBytes);
            
            /**
            * @brief free the a memory chunk from memory buffer
            * @return true if memory is freed; otherwise false
            */
            bool            Free                (void * pSource);
            
            /**
            * @brief Checks for memory availablity in memory buffer
            * @return true of memory is available the initial block of memory; otherwise false
            */
            bool            CheckAvalability    (size_t pBytes)                         const;
            
            /**
            * @brief Get singleton object of Allocator
            * @return singleton object pointer if initialted; otherwise nullptr
            */
    static  Allocator *     GetInstance         ();

            /**
            * @brief Set the default size for new buffer
            */
    static  void            SetBufferSize       (size_t pBytes);
    
            /**
            * @brief Check if the allocator is initiated or not
            * @return true if allocator is initialted; otherwise false
            */
    static  bool            IsInitiated         ();
    
            /**
            * @brief set flag for initiation of allocator
            */
    static  void            SetInitiated        (bool pflag);

  private:
      
            /**
            * @brief Allocates memory buffer
            */
                            Allocator           (size_t pBytes);

            /**
            * @brief Allocates memory for new buffer chunk in buffer pool
            * @return pointer to buffer pool
            */
            tMemoryBlock ** ReallocateBuffers   ();

            int             vCurrBlock;
            int             vTotalBufferCount;
            tMemoryBlock ** vBuffers;
    static  Allocator *     sUniqueInstance;
    static  size_t          sBufferSize;
    static  bool            sIsInitiated;
};

#endif // !ALLOCATOR_HPP
