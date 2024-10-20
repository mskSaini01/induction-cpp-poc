#include "shared_ptr.hpp"

/**
* @brief Shared Pointer Parameterised Constructor
* vPointer is assigned to source and memory is allocated for ref count with value 1 for the reference to source
* Without being Explicit, the source object will be created and destructed and then move to the shared pointer object
*/
template<typename Type>
SharedPtr<Type>::SharedPtr (Type * pPointer, Deleter<Type> pDeleter) noexcept
    : vPointer (pPointer),
      vDeleter (pDeleter),
      vRefCount (new (std::nothrow) size_t (1))
{
    if (pPointer == nullptr && vRefCount != nullptr) {
        *vRefCount = 0;
    }
}

/**
* @brief Shared Pointer Move Constructor
* All the members of source object are assigned to object
*/
template<typename Type>
SharedPtr<Type>::SharedPtr (SharedPtr && pSource) noexcept
{
    vPointer  = pSource.vPointer;
    vRefCount = pSource.vRefCount;
    vDeleter  = pSource.vDeleter;
    
    pSource.vPointer  = nullptr;
    pSource.vRefCount = nullptr;
    pSource.vDeleter  = nullptr;
}

/**
* @brief Shared Pointer Parameterised Constructor
* vPointer is assigned to source and memory is allocated for ref count with value 1 for the reference to source
*/
template<typename Type>
SharedPtr<Type>::SharedPtr (const SharedPtr & pSource)
{
    vPointer  = pSource.vPointer;
    vRefCount = pSource.vRefCount;
    vDeleter  = pSource.vDeleter;
    
    if (vRefCount != nullptr) {
        (*vRefCount)++;
    }
}

/**
* @brief Shared Pointer Distructor
* decrement the vRefCount and if the last reference is getting deleted, delete the source data;
*/
template<typename Type>
SharedPtr<Type>::~SharedPtr ()
{
    // cleanup any existing data
    Release ();
}

/**
* @brief Shared Pointer Reset
* decrement the vRefCount and if the last reference is getting deleted, delete the source data;
* assign the nullptr to the data members
*/
template<typename Type>
void SharedPtr<Type>::Reset (Type * pSource)
{
    if (vPointer == pSource) {
        return;
    }

    // cleanup any existing data
    Release ();

    vPointer  = pSource;
    vDeleter  = nullptr;
    vRefCount = new (std::nothrow) size_t (1);
}

/**
* @brief Get Data Pointer
* 
* @return Data Pointer
*/
template<typename Type>
Type * SharedPtr<Type>::Get () const noexcept
{
    return vPointer;
}

/**
* @brief Get Reference Count for source data
* 
* @return number of references to the source data if present; otherwise nullptr.
*/
template<typename Type>
size_t SharedPtr<Type>::UseCount () const noexcept
{
    if (vRefCount == nullptr) {
        return 0;
    }

    return *vRefCount;
}

/**
* @brief Get Deleter method
* 
* @return Pointer to Deleter method
*/
template<typename Type>
Deleter<Type> & SharedPtr<Type>::GetDeleter () const noexcept
{
    return vDeleter;
}

/**
* @brief Set Deleter Method
*/
template<typename Type>
void SharedPtr<Type>::SetDeleter (Deleter<Type> pDeleter) noexcept
{
    vDeleter = pDeleter;
}

/**
* @brief Arrow operator overloading
* 
* @return Data source pointer.
*/
template<typename Type>
Type * SharedPtr<Type>::operator -> () const noexcept
{
    return vPointer;
}

/**
* @brief Dereference operator overloading
* 
* @return Source Data.
*/
template<typename Type>
Type & SharedPtr<Type>::operator * () const
{
    return (*vPointer);
}

/**
* @brief Dereference operator overloading
* 
* @return Source Data.
*/
template<typename Type>
Type & SharedPtr<Type>::operator [] (size_t pIndex) const
{
    return *(vPointer + pIndex);
}

/**
* @brief Equality operator overloading
* 
* @return true, if the two pointers are pointing to the same source data; otherwise false.
*/
template<typename Type>
bool SharedPtr<Type>::operator == (const SharedPtr & pSource) noexcept
{
    return (vPointer == pSource.Get ());
}

/**
* @brief Assignment operator overloading for SharedPtr class
* Remove the pointed source data and reassign it with pSource data, when shared pointer is not assigned to itself
* 
* @return shared pointer of the object
*/
template<typename Type>
SharedPtr<Type> & SharedPtr<Type>::operator = (const SharedPtr<Type> & pSource)
{
    if (vPointer == pSource.vPointer) {
        return (*this);
    }

    // cleanup any existing data
    Release();
    
    // assign with pSource's data
    vPointer  = pSource.vPointer;
    vRefCount = pSource.vRefCount;

    if (vRefCount != nullptr) {
        (*vRefCount)++;
    }

    return (*this);
}

/**
* @brief Move Assignment operator overloading for SharedPtr class
* Remove the pointed source data and reassign it with pSource data, when shared pointer is not assigned to itself
* 
* @return shared pointer of the object
*/
template<typename Type>
SharedPtr<Type> & SharedPtr<Type>::operator = (SharedPtr && pSource)
{
    if (vPointer != pSource.vPointer) {
        // cleanup any existing data
        Release ();

        vPointer  = pSource.vPointer;
        vRefCount = pSource.vRefCount;
        vDeleter  = pSource.vDeleter;
    }
    
    pSource.vPointer   = nullptr;
    pSource.vRefCount  = nullptr;
    pSource.vDeleter   = nullptr;

    return (*this);
}

/**
* @brief Addition Assignment operator overloading
* Add pSize times of size of the data type to the source data
* 
* @return shared pointer of the object
*/
template<typename Type>
SharedPtr<Type> & SharedPtr<Type>::operator += (const size_t & pSize) noexcept
{
    vPointer += pSize;
    
    return (*this);
}

/**
* @brief Subtraction Assignment operator overloading
* Subtract pSize times of size of the data type from the source data
* 
* @return shared pointer of the object
*/
template<typename Type>
SharedPtr<Type> & SharedPtr<Type>::operator -= (const size_t & pSize) noexcept
{
    vPointer -= pSize;
    
    return (*this);
}

/**
* @brief Addition Assignment operator overloading
* Add pSize times of size of the data type to the source data
* 
* @return data source pointer
*/
template<typename Type>
Type * SharedPtr<Type>::operator + (const size_t & pSize) noexcept
{
    return (vPointer + pSize);
}

/**
* @brief Subtraction Assignment operator overloading
* Subtract pSize times of size of the data type from the source data
* 
* @return data source pointer
*/
template<typename Type>
Type * SharedPtr<Type>::operator - (const size_t & pSize) noexcept
{
    return (vPointer - pSize);
}

/**
* @brief decrement the ref count Release the source data of it's the last reference
*/
template<typename Type>
void SharedPtr<Type>::Release ()
{
    // Reference count existance check
    if (vRefCount == nullptr || vPointer == nullptr) {
        return;
    }

    (*vRefCount)--;
    
    // delete last referenced data
    if (*vRefCount == 0) {

        if (vDeleter != nullptr) {
            vDeleter (vPointer);

        } else {
            delete vPointer;
        }

        delete vRefCount;

        vPointer  = nullptr;
        vRefCount = nullptr;
        vDeleter  = nullptr;
    }
}
