#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "log.hpp"
#include "trace_func.hpp"

/**
*  @brief Structure of nodes in linked list 
*/
template <typename DataType>
struct tNode {
    
    // Default constructor
    tNode ();

    // Parameterised constructor 
    tNode (const DataType & pData);

    DataType      uData;
    tNode     *   uNext;
    tNode     *   uPrev;
};

/**
*  @brief A collection of nodes with data
*/
template <typename DataType>
class LinkedList {

  public:
                        LinkedList          ();
                        ~LinkedList         ();
    /**
    *  @brief Insert a Node with value pSouce at the end of the linked list 
    */
    void                PushBack            (DataType const & pSource);

    /**
    *  @brief Insert a Node pSouce at the end of the linked list 
    */
    void                PushBack            (tNode<DataType> & pSource);
    
    /**
    *  @brief Insert a Node with value pSouce at the begining of the linked list 
    */
    void                PushFront           (DataType const & pSource);

    /**
    *  @brief Insert a Node pSouce at the begining of the linked list 
    */
    void                PushFront           (tNode<DataType> & pSource);
    
    /**
    *  @brief Insert node pSouce after Node at index pIndex in the linked list 
    */
    void                InsertAfter         (size_t pIndex, tNode<DataType> & pSource);

    /**
    *  @brief Insert node pSouce before Node at index pIndex in the linked list 
    */
    void                InsertBefore        (size_t pIndex, tNode<DataType> & pSource);

    /**
    *  @brief Delete node at end of the linked list 
    */
    bool                PopBack             ();

    /**
    *  @brief Delete node at begining of the linked list 
    */
    bool                PopFront            ();

    /**
    *  @brief Delete node at a given index in linked list 
    */
    bool                PopAt               (size_t pIndex);
    
    /**
    *  @return  true if the list is empty; otherwise false.
    */
    bool                Empty               ()                                  const;
    
    /**
    *  @brief Delete all node elements 
    */
    void                Clear               ();
    
    /**
    *  @brief Display all elements in list 
    */
    void                Display             ()                                  const;

    /**
    *  @breif Iterator over elements 
    */
    void                ListIterator        (void (*pFuncPtr) (tNode<DataType> *, void *), void * pParams);
    
    /**
    *  @return Number of elements in list 
    */
    size_t              Size                ()                                  const;
    
    /**
    *  @return Head Element if exists; otherwise nullptr
    */
    tNode<DataType> *	GetHead				()                                  const;
    
    /**
    *  @return Tail Element if exists; otherwise nullptr
    */
    tNode<DataType> *	GetTail				()                                  const;

    /**
    *  @return Next element of pSource node if present except dummy head node; otherwise nullptr
    */
    tNode<DataType> *	GetNext				(tNode<DataType> & pSource)         const;

    /**
    *  @return Previous element of pSource node if present except dummy head node; otherwise nullptr
    */
	tNode<DataType> *	GetPrevious			(tNode<DataType> & pSource)         const;

    /**
    *  @return Element at a given index if present; otherwise nullptr
    */
	tNode<DataType> *	GetNodeAt			(size_t pIndex);

  private:
    
    /**
    *  @brief Insert node pSouce after Node pDestination in the linked list 
    */
    void                InsertAfter         (tNode<DataType> & pDestination, tNode<DataType> & pSource);
    
    /**
    *  @brief Insert node pSouce before Node pDestination in the linked list 
    */
    void                InsertBefore        (tNode<DataType> & pDestination, tNode<DataType> & pSource);

    size_t              vSize;              // Node count in list
    tNode<DataType> *   vHead;              // points to a dummy node
    tNode<DataType> *   vTail;              // vTails->next points to dummy node
};

#include "linked_list.hxx"

#endif // !LINKED_LIST_HPP
