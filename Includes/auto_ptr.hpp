#ifndef AUTO_PTR_HPP
#define AUTO_PTR_HPP

template <typename Type>
using Deleter = void (*) (Type *);

/**
* @class Pointer Wrapper for pointer with only unique reference
*       Automatically release the pointed data when the pointed data no longer referenced
*
* @ingroup SharedPointer
*/
template <typename Type>
class AutoPtr {

  public:

    // @name: Constructors 
    explicit                    AutoPtr                     (Type * pPointer = nullptr,
                                                             Deleter<Type> pDeleter = nullptr)              noexcept;
    
                                AutoPtr                     (const AutoPtr & pSource) = delete;
    
                                AutoPtr                     (AutoPtr && pSource)                            noexcept;
    
    // @name: Destructors
                                ~AutoPtr                    ();
    
    // @name: Utilities
            void                Reset                       (Type * pSource = nullptr,
                                                             Deleter<Type> pDeleter = nullptr);
    
            Type *              Release                     ()                                              noexcept;
    
            Type *              Get                         ()                                      const   noexcept;
    
            Deleter<Type> &     GetDeleter                  ()                                      const   noexcept;
    
            void                SetDeleter                  (Deleter<Type> pDeleter = nullptr)              noexcept;
    
    // @name: Overloaded Operators
            Type &              operator *                  ()                                      const;
                    
            Type &              operator []                 (size_t pIndex)                         const;
                    
            Type *              operator ->                 ()                                      const   noexcept;
                    
            Type *              operator +                  (const size_t & pSize)                          noexcept;
                    
            Type *              operator -                  (const size_t & pSize)                          noexcept;
    
            bool                operator ==                 (const AutoPtr<Type> & pSource)                 noexcept;
    
            AutoPtr<Type> &     operator +=                 (const size_t & pSize)                          noexcept;
    
            AutoPtr<Type> &     operator ++                 ()                                              noexcept;
    
            AutoPtr<Type> &     operator --                 ()                                              noexcept;
    
            AutoPtr<Type> &     operator -=                 (const size_t & pSize)                          noexcept;
    
            AutoPtr<Type> &     operator =                  (AutoPtr<Type> && pSource)                      noexcept;
    
            AutoPtr<Type> &     operator =                  (const AutoPtr<Type> & pSource) = delete;
    
            template<typename CastType>
                                operator AutoPtr<CastType>  ();
                    
    private:
                    
    // @name: Data Memeber
            Type *             vPointer;       // Pointer to data
            Deleter<Type>      vDeleter;       // Custom delete for pointer
};

#include "auto_ptr.hxx"

#endif // !AUTO_PTR_HPP
