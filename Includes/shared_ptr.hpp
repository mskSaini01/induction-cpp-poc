#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

template <typename Type>
using Deleter = void (*) (Type *);

/**
* @class Pointer wrapper for pointer handling
*       Automatically release the pointed data when the pointed data no longer referenced
*
* @ingroup SharedPointer
*/
template <typename Type>
class SharedPtr {

  public:

    // @name: Constructors
    explicit                    SharedPtr           (Type * pPointer = nullptr,
                                                     Deleter<Type> pDeleter = nullptr)      noexcept;

                                SharedPtr           (SharedPtr && pSource)                  noexcept;

                                SharedPtr           (const SharedPtr & pSource);

    // @name: Distructors 
                                ~SharedPtr          ();

    // @name: Utilities
                void            Reset               (Type * pSource = nullptr);
                
                size_t          UseCount            ()                              const   noexcept;

                Type *          Get                 ()                              const   noexcept;

                Deleter<Type> & GetDeleter          ()                              const   noexcept;

                void            SetDeleter          (Deleter<Type> pDeleter = nullptr)      noexcept;

    // @name: Overloaded Operators
                Type &          operator *          ()                              const;

                Type &          operator []         (size_t pIndex)                 const;

                Type *          operator ->         ()                              const   noexcept;

                Type *          operator +          (const size_t & pSize)                  noexcept;

                Type *          operator -          (const size_t & pSize)                  noexcept;

                SharedPtr &     operator +=         (const size_t & pSize)                  noexcept;

                SharedPtr &     operator -=         (const size_t & pSize)                  noexcept;

                SharedPtr &     operator =          (const SharedPtr & pSource);

                SharedPtr &     operator =          (SharedPtr && pSource);

                bool            operator ==         (const SharedPtr & pSource)             noexcept;

    // @name: New Operator Restrictions
                void *          operator new        (size_t pSize) = delete;

                void *          operator new []     (size_t pSize) = delete;

  private:

    // @name: Release Utilities
                void            Release             ();

    // @name: Data Members
                Type *          vPointer;       // Pointer to data
                size_t *        vRefCount;      // Total Number of references to pointed data
                Deleter<Type>   vDeleter;       // Custom delete for pointer
};

#include "shared_ptr.hxx"

#endif // !SHARED_PTR_HPP
