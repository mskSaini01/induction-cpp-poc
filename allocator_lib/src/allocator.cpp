#include "allocator.hpp"

// static initializations
size_t      Allocator:: sBufferSize     = 0;
bool        Allocator:: sIsInitiated      = false;
Allocator * Allocator:: sUniqueInstance = nullptr;

/**
* @brief Deallocates memory buffer
*/
Allocator::~Allocator ()
{
    // release all buffer's memory
    for (int i = 0; i < vTotalBufferCount; i++) {
        delete vBuffers [0];
        
        vBuffers[0] = nullptr;
    }
    delete [] vBuffers;

    vBuffers            = nullptr;
    vTotalBufferCount   = 0;
    vCurrBlock          = 0;
}

/**
* @brief Allocates a number of bytes of memory buffer
* @return a pointer to dynamically allocated memory is allocated; otherwise nullptr
*/
void * Allocator::Malloc (size_t pBytes)
{
        void *          begining_address = nullptr;
        tMemoryBlock *  new_buffer       = nullptr;
    
    if (vCurrBlock == 0) {
        vCurrBlock++;
    }

    if (!vBuffers[vCurrBlock - 1]->uBuffer) {
        return nullptr;
    }

    // check memory availabilty
    if (!CheckAvalability (pBytes)) {
            tMemoryBlock ** new_buffers = ReallocateBuffers ();
        
        // expand vBuffer pointer array for new buffer
        if (new_buffers) {
            new_buffer = new (std::nothrow) tMemoryBlock (sBufferSize);

            if (!new_buffer) {
                return nullptr;
            }

            vBuffers[vTotalBufferCount++] = new_buffer;
            ++vCurrBlock;
            
            new_buffer = nullptr;
        }
    }
    
    // set begining address at unused memory starting address
    begining_address = vBuffers[vCurrBlock - 1]->uMemoryEnd;

    vBuffers[vCurrBlock - 1]->uMemoryEnd  = static_cast<char *> (vBuffers[vCurrBlock - 1]->uMemoryEnd) + pBytes;
    
    return begining_address;
}

/**
* @brief Checks for memory availablity in memory buffer
* @return true of memory is available the initial block of memory; otherwise false
*/
bool Allocator::CheckAvalability (size_t pBytes) const
{
    // check for memory availability
    if ((size_t) ((char *) vBuffers[vCurrBlock - 1]->uBufferEnd - (char *) vBuffers[vCurrBlock - 1]->uMemoryEnd) < pBytes) {
        return false;
    }
    return true;
}

/**
* @brief free the a memory chunk from memory buffer
* @return true if memory is freed; otherwise false
*/
bool Allocator::Free (void * pSource)
{
    if (pSource < vBuffers[vCurrBlock - 1]->uBuffer || pSource > vBuffers[vCurrBlock - 1]->uMemoryEnd) {
        return false;
    }

    // allocate the memory break to the starting address of pSoucre
    vBuffers[vCurrBlock - 1]->uMemoryEnd = pSource;

    // Whole Chunk is free
    if (vBuffers[vCurrBlock - 1]->uBuffer == vBuffers[vCurrBlock - 1]->uMemoryEnd) {

        if (!vCurrBlock) {
            return false;
        
        } else {
            // update cuurent block
            --vCurrBlock;
        }
    }

    return true;
}

/**
* @brief Get singleton object of Allocator
* @return singleton object pointer if initialted; otherwise nullptr
*/
Allocator * Allocator::GetInstance ()
{
    if (Allocator::sUniqueInstance == nullptr) {
        // creating a new instance
        Allocator::sUniqueInstance = new (std::nothrow) Allocator (sBufferSize);
    }
    
    // returning instance with unique
    return Allocator::sUniqueInstance;
}

/**
* @brief Set the default size for new buffer
*/
void Allocator::SetBufferSize (size_t pBytes) 
{
    sBufferSize = pBytes;
}

/**
* @brief Check if the allocator is initiated or not
* @return true if allocator is initialted; otherwise false
*/
bool Allocator::IsInitiated ()
{
    return Allocator::sIsInitiated;
}
    
/**
* @brief set flag for initiation of allocator
*/
void Allocator::SetInitiated (bool pFlag) 
{
    Allocator::sIsInitiated = pFlag;
}

/**
* @brief Allocates memory buffer
*/
Allocator::Allocator (size_t pBytes)
{
    vCurrBlock          = 0;
    vTotalBufferCount   = 0;

    // Get a new big chunk of memory for pooling
    vBuffers    = (tMemoryBlock **) malloc (sizeof (tMemoryBlock *));
    sBufferSize = pBytes;
    
    if (vBuffers) {
        vBuffers[0] = new (std::nothrow) tMemoryBlock (pBytes);

        if (vBuffers[0]) {
            ++vCurrBlock;
            ++vTotalBufferCount;
        }
    }
}

// Reallocates the memory to chunk buffer array
tMemoryBlock ** Allocator::ReallocateBuffers ()
{
        tMemoryBlock ** new_buffers = nullptr;

    new_buffers = new tMemoryBlock * [vTotalBufferCount + 1];
    
    if (!new_buffers) {
        return nullptr;
    }
    
    // Moving the buffers from previous memory to new memory
    for (size_t i = 0; i < vTotalBufferCount; ++i) {
        new_buffers[i] = vBuffers[i];
    }

    delete[] vBuffers;

    vBuffers = new_buffers;
    
    return vBuffers;
}

tMemoryBlock::tMemoryBlock (size_t pBytes)
{
    uBuffer = malloc (pBytes);

    // Memory Allocation failure
    if (!uBuffer) {
        uBufferEnd  = nullptr;
        uMemoryEnd = nullptr;
    
    } else {    
        // initialize buffer end break
        uBufferEnd = (void *)(static_cast<char *> (uBuffer) + pBytes);

        // initialize Used Memory end
        uMemoryEnd = uBuffer;
    }
}

tMemoryBlock::~tMemoryBlock ()
{
    if (uBuffer) {
        // free the memory buffer
        free (uBuffer);
        uBuffer = nullptr;
    }

    uBufferEnd = nullptr;
    uMemoryEnd = nullptr;
}
