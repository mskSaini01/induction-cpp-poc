#ifndef LINKED_LIST_HXX
#define LINKED_LIST_HXX

#include <new>
#include <assert.h>
#include "linked_list.hpp"
#include "printf.hpp"
#include "trace_func.hpp"
#include "profiler.hpp"

/**
*  @brief Default Constructor of Data Node
*/
template<typename DataType>
tNode<DataType>::tNode ()
{
    uNext = nullptr;
    uPrev = nullptr;
}

/**
*  @brief Parameterised Constructor of Data Node
*/
template<typename DataType>
tNode<DataType>::tNode (DataType const & pData)
{
    uData = pData;
    uNext = nullptr;
    uPrev = nullptr;
}

template <typename DataType>
LinkedList<DataType>::LinkedList ()
{
    vSize   = 0;
    vHead   = new (std::nothrow) tNode<DataType> (DataType ());
    
    // Memory allocation failure
    ASSERT (vHead);
    
    vTail   = vHead;

    // Head points to dummy
    vHead->uNext    = vHead;
    vHead->uPrev    = vHead;
}

template <typename DataType>
LinkedList<DataType>::~LinkedList ()
{
    Clear ();

    delete  vHead;

    vHead       = nullptr;
    vTail       = nullptr;
    vSize       = 0;
}

/**
*  @brief Insert a Node with value pSouce at the end of the linked list 
*/
template<typename DataType>
void LinkedList<DataType>::PushBack (DataType const & pSource)
{
        TRACEFUNC;

        tNode<DataType> * new_node = new (std::nothrow) tNode<DataType> (pSource);
            
    if (!new_node) {
        Log (DEBUG_MODE, INFO_TYPE, "Memory Allocation Failiure!", false);
        ASSERT(new_node);
    }
    
    PushBack (* new_node);
}

/**
*  @brief Insert a Node pSouce at the end of the linked list 
*/
template<typename DataType>
void LinkedList<DataType>::PushBack (tNode<DataType> & pSource)
{
        TRACEFUNC;

    // Bridge pSource on nodes inter-connections (next, prev)
    pSource.uPrev  = vTail;
    pSource.uNext  = vHead;
    
    // Break old inter-connections (next, prev) between Tail and Head
    vTail->uNext   = &pSource;
    vHead->uPrev   = &pSource;

    // Update Tail
    vTail          = &pSource;

    ++vSize;
    
    Log (DEBUG_MODE, INFO_TYPE, "New Node Inserted At the End.", true);
}
    
/**
*  @brief Insert a Node with value pSouce at the begining of the linked list 
*/
template<typename DataType>
void LinkedList<DataType>::PushFront(DataType const & pSource)
{
        TRACEFUNC;

        tNode<DataType> * new_node = new (std::nothrow) tNode<DataType> (pSource);
    
    if (!new_node) {
        Log (DEBUG_MODE, ERROR_TYPE, "Memory Allocation Failiure!", false);
        ASSERT(new_node);
    }
    
    PushFront (* new_node);
}

/**
*  @brief Insert a Node pSouce at the begining of the linked list 
*/
template<typename DataType>
void LinkedList<DataType>::PushFront (tNode<DataType> & pSource)
{
        TRACEFUNC;

    // Bridge pSource on nodes inter-connections (next, prev)
    pSource.uNext             = vHead->uNext;
    pSource.uPrev             = vHead;
    
    // Break old inter-connections (next, prev) between Head and Head->next
    vHead->uNext              = &pSource;
    (pSource.uNext)->uPrev    = &pSource;

    ++vSize;
    
    Log (DEBUG_MODE, ERROR_TYPE, "New Node Inserted At the Front.", false);
}

/**
*  @brief Insert node pSouce after Node at index pIndex in the linked list 
*/
template<typename DataType>
void LinkedList<DataType>::InsertAfter(size_t pIndex, tNode<DataType> & pSource)
{
        TRACEFUNC;

        tNode <DataType> * curr_node = GetNodeAt (pIndex);
        
    if (!curr_node) {
        Log (DEBUG_MODE, WARNING_TYPE, "Data Not Found!", false);
        return;
    }
    
    InsertAfter (*curr_node, pSource);
}

/**
*  @brief Insert node pSouce before Node at index pIndex in the linked list 
*/
template<typename DataType>
void LinkedList<DataType>::InsertBefore (size_t pIndex, tNode<DataType> & pSource)
{
        TRACEFUNC;

        tNode <DataType> * curr_node = GetNodeAt (pIndex);
        
    if (!curr_node) {
        Log (DEBUG_MODE, WARNING_TYPE, "Data Not Found!", false);
        return;
    }

    InsertBefore (*curr_node, pSource);
}

/**
*  @brief Delete node at end of the linked list 
*/
template<typename DataType>
bool LinkedList<DataType>::PopBack ()
{
        TRACEFUNC;

        tNode <DataType> * curr_node = vTail->uPrev;

    if (vHead != vTail) {
        // Bypass an inter-connections (next, prev) between curr_node (vTail->uPrev) and vHead
        curr_node->uNext = vHead;
        vHead->uPrev    = curr_node;

        // Delete last node
        delete vTail;

        // Update last node
        vTail = curr_node;

        --vSize;
        
        Log (DEBUG_MODE, INFO_TYPE, "Last Node Deleted.", false);
        return true;
    }
    Log (DEBUG_MODE, WARNING_TYPE, "Data Not Found!", false);
    
    return false;
}

/**
*  @brief Delete node at begining of the linked list 
*/
template<typename DataType>
bool LinkedList<DataType>::PopFront ()
{
        TRACEFUNC;

        tNode <DataType> * curr_node = vHead->uNext;

    if (vHead != vTail) {
        // Bypass an inter-connections (next, prev) between curr_node (vTail->uPrev) and vHead
        vHead->uNext                 = curr_node->uNext;
        (curr_node->uNext)->uPrev   = vHead;

        // Delete last node
        delete curr_node;

        curr_node = nullptr;

        // Update Tail  -> when (vSize == 1) -> (curr_node == vTail) (extra computation when vSize > 1)
        vTail = vHead->uPrev;

        --vSize;
        
        Log (DEBUG_MODE, INFO_TYPE, "1st Node Deleted.", false);

        return true;
    }
    
    Log (DEBUG_MODE, WARNING_TYPE, "Data Not Found!", false);
    
    return false;
}

/**
*  @brief Delete node at a given index in linked list 
*/
template<typename DataType>
bool LinkedList<DataType>::PopAt (size_t pIndex)
{
        TRACEFUNC;

        tNode <DataType> * curr_node = GetNodeAt(pIndex);

    if (!curr_node) {
        Log (DEBUG_MODE, WARNING_TYPE, "Data Not Found!", false);
        return false;
    }

    // prev node's next to next node (in ref to curr_node)
    (curr_node->uPrev)->uNext = curr_node->uNext;

    // next node's prev to next node (in ref to curr_node)
    (curr_node->uNext)->uPrev = curr_node->uPrev;

    // Delete current node
    delete curr_node;

    curr_node = nullptr;
    
    // Update Tail -> when (vSize == 1) -> (curr_node =was= vTail) (extra computation when vTail is not deleted)
    vTail = vHead->uPrev;

    --vSize;
    
    Log (DEBUG_MODE, INFO_TYPE, "Deleted Node at an Index.", false);

    return true;
}

/**
*  @brief Delete all node elements 
*/
template<typename DataType>
void LinkedList<DataType>::Clear ()
{
        TRACEFUNC;

        // Get first element 
        tNode <DataType> * curr_node = vHead->uNext;
        tNode <DataType> * next_node = curr_node;

    while (curr_node != vHead) {
        //Get next node of current element 
        next_node = curr_node->uNext;
        
        // free current node 
        delete curr_node;

        // update current node
        curr_node = next_node;
    }

    vSize = 0;
    vHead->uNext = vHead;
    vHead->uPrev = vHead;
    vTail        = vHead;
    
    Log (DEBUG_MODE, INFO_TYPE, "Linked List Cleared.", false);
}

/**
*  @return  true if the list is empty; otherwise false.
*/
template<typename DataType>
bool LinkedList<DataType>::Empty () const
{
        TRACEFUNC;

    return (vSize == 0);
}

/**
*  @brief Display all elements in list 
*/
template<typename DataType>
void LinkedList<DataType>::Display ()   const
{
        TRACEFUNC;

        tNode<DataType> * curr = vHead->uNext;

    Printf ("{");
    while (curr != vHead) {
        Printf ("% ", curr->uData);
        curr = curr->uNext;

        if (curr != vHead) {
            Printf (", ");
        }
    }
    Printf ("}");
    
    Log (DEBUG_MODE, INFO_TYPE, "Linked List Displayed.", false);
}

template<typename DataType>
inline void LinkedList<DataType>::ListIterator (void (* pFuncPtr) (tNode<DataType> *, void *), void * pParams)
{
        TRACEFUNC;

        tNode<DataType> * curr_node = vHead->uNext;

    while (curr_node != vHead) {
        pFuncPtr (curr_node, pParams);
        curr_node = curr_node->uNext;
    }
}
/**
*  @return Number of elements in list 
*/
template <typename DataType>
size_t LinkedList<DataType>::Size ()    const
{
        TRACEFUNC;

    return vSize;
}

template<typename DataType>
inline tNode<DataType>* LinkedList<DataType>::GetHead() const
{
        TRACEFUNC;

    if (vSize == 0) {
        Log (DEBUG_MODE, WARNING_TYPE, "Data Not Found!", false);
        return nullptr;
    }

    return vHead->uNext;
}

template<typename DataType>
inline tNode<DataType>* LinkedList<DataType>::GetTail() const
{
        TRACEFUNC;

    if (vSize == 0) {
        Log (DEBUG_MODE, WARNING_TYPE, "Data Not Found!", false);
        return nullptr;
    }

    return vTail;
}

/**
*  @return Next element of pSource node if present; otherwise alert when it is last element
*/
template<typename DataType>
tNode<DataType> * LinkedList<DataType>::GetNext (tNode<DataType> & pSource) const
{
        TRACEFUNC;

    // pDestination is last element
    if (pSource.uNext == vHead) {
        Log (DEBUG_MODE, ERROR_TYPE, "Data Not Found!", false);
        ASSERT (pSource.uNext != vHead);
    }

    return pSource.uNext;
}

/**
*  @return Previous element of pSource node if present; otherwise alert when it is first element
*/
template<typename DataType>
tNode<DataType> * LinkedList<DataType>::GetPrevious (tNode<DataType> & pSource) const
{
        TRACEFUNC;

    // nullptr if pDestination is the first element
    if (pSource->uPrev == vHead) {
        Log (DEBUG_MODE, ERROR_TYPE, "Data Not Found!", false);
        ASSERT (pSource->uPrev != vHead);
    }

    return pSource.uPrev;
}

/**
*  @return Element at a given index if present; otherwise nullptr
*/
template<typename DataType>
tNode<DataType> * LinkedList<DataType>::GetNodeAt (size_t pIndex)
{
        TRACEFUNC;

        // Get first element 
        tNode <DataType> * curr_node = vHead->uNext;

    // check for out of index, ()
    if ((vSize == 0) || (pIndex > vSize - 1)) {
        Log (DEBUG_MODE, INFO_TYPE, "Index Out Of Bound!", false);
        return nullptr;
    }

    while (pIndex != 0) {
        curr_node = curr_node->uNext;
        pIndex--;
    }

    return curr_node;
}

/**
*  @brief Insert node pSouce after Node pDestination in the linked list 
*/
template<typename DataType>
void LinkedList<DataType>::InsertAfter (tNode<DataType> & pDestination, tNode<DataType> & pSource)
{
        TRACEFUNC;

    // Bridge pSource on nodes inter-connections (next, prev)
    pSource.uNext          = pDestination.uNext;
    pSource.uPrev          = &pDestination;
    
    // Break old inter-connections (next, prev) between pDestination and pSource
    pDestination.uNext     = &pSource;
    (pSource.uNext)->uPrev = &pSource;

    ++vSize;
    
    Log (DEBUG_MODE, INFO_TYPE, "Inserted a node after a destination node!", false);
}

/**
*  @brief Insert node pSouce before Node pDestination in the linked list 
*/
template<typename DataType>
void LinkedList<DataType>::InsertBefore(tNode<DataType> & pDestination, tNode<DataType> & pSource)
{
        TRACEFUNC;

    // Bridge pSource on nodes inter-connections (next, prev)
    pSource.uPrev          = pDestination->uPrev;
    pSource.uNext          = &pDestination;

    // Break old inter-connections (next, prev) between pDestination and pSource
    (pDestination.uPrev)->uNext    = &pSource;
    pDestination.uPrev             = &pSource;

    ++vSize;

    Log (DEBUG_MODE, INFO_TYPE, "Inserted a node before a destination node!", false);
}

#endif // !LINKED_LIST_HXX
