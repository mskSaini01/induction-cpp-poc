#include "auto_ptr.hpp"

/**
* @brief Auto Pointer Parameterised Constructor
* vPointer is assigned to source
* Without being Explicit, the source object will be created and destructed and then move to the shared pointer object
*/
template<typename Type>
AutoPtr<Type>::AutoPtr (Type * pPointer, Deleter<Type> pDeleter) noexcept
    : vPointer (pPointer),
      vDeleter (pDeleter)
{
}

/**
* @brief Auto Pointer Move Constructor
* All the members of source object are assigned to object
*/
template<typename Type>
AutoPtr<Type>::AutoPtr (AutoPtr && pSource) noexcept
{
    vPointer           = pSource.vPointer;
    vDeleter           = pSource.vDeleter;

    pSource.vPointer   = nullptr;
    pSource.vDeleter   = nullptr;
}

/**
* @brief Auto Pointer Distructor
* delete the source data;
*/
template<typename Type>
AutoPtr<Type>::~AutoPtr ()
{
    Reset ();
}

/**
* @brief Auto Pointer Reset
* delete the source data and assign the nullptr to the data pointer
*/
template<typename Type>
void AutoPtr<Type>::Reset (Type * pSource, Deleter<Type> pDeleter)
{    
    if (vPointer != pSource) {

        // cleanup any existing data
        if (vDeleter != nullptr) {
            vDeleter (vPointer);

        } else {
            delete vPointer;
        }

        vPointer = pSource;
        vDeleter = pDeleter;
    }
}

/**
* @brief Auto Pointer Release
* delete the source data and assign the nullptr to the data pointer
*/
template<typename Type>
Type * AutoPtr<Type>::Release () noexcept
{
        Type * data_pointer = vPointer;

    vPointer = nullptr;
    vDeleter = nullptr;

    return data_pointer;
}

/**
* @brief Get Data Pointer
* 
* @return Data Pointer
*/
template<typename Type>
Type * AutoPtr<Type>::Get () const noexcept
{
    return vPointer;
}

/**
* @brief Get Deleter method
* 
* @return Pointer to Deleter method
*/
template<typename Type>
Deleter<Type> & AutoPtr<Type>::GetDeleter () const noexcept
{
    return vDeleter;
}

/**
* @brief Set Deleter Method
*/
template<typename Type>
void AutoPtr<Type>::SetDeleter (Deleter<Type> pDeleter) noexcept
{
    vDeleter = pDeleter;
}

/**
* @brief Arrow operator overloading
* 
* @return Data source pointer.
*/
template<typename Type>
Type * AutoPtr<Type>::operator -> () const noexcept
{
    return vPointer;
}

/**
* @brief Dereference operator overloading
* 
* @return Source Data.
*/
template<typename Type>
Type & AutoPtr<Type>::operator * () const
{
    return (*vPointer);
}

/**
* @brief Dereference operator overloading
* 
* @return Source Data.
*/
template<typename Type>
Type & AutoPtr<Type>::operator [] (size_t pIndex) const
{
    return *(vPointer + pIndex);
}

/**
* @brief Move Assignment operator overloading for AutoPtr class
* Remove the pointed source data and reassign it with pSource data, when auto pointer is not assigned to itself
* 
* @return auto pointer of the object
*/
template<typename Type>
AutoPtr<Type> & AutoPtr<Type>::operator = (AutoPtr && pSource) noexcept
{
    if (vPointer == pSource.vPointer) {
        return (*this);
    }

    // cleanup any existing data
    if (vDeleter != nullptr) {
        vDeleter (vPointer);

    } else {
        delete vPointer;
    }
    
    // assign with pSource's data
    vPointer = pSource.vPointer;
    vDeleter = pSource.vDeleter;

    pSource.vPointer = nullptr;
    pSource.vDeleter = nullptr;

    return (*this);
}

/**
* @brief Increment operator overloading
* Increment source pointer by size of data
* 
* @return Auto pointer of the object
*/
template<typename Type>
AutoPtr<Type> & AutoPtr<Type>::operator ++ () noexcept
{
    ++vPointer;
    
    return (*this);
}

/**
* @brief Decrement operator overloading
* Decrement source pointer by size of data
* 
* @return Auto pointer of the object
*/
template<typename Type>
AutoPtr<Type> & AutoPtr<Type>::operator -- () noexcept
{
    --vPointer;
    
    return (*this);
}

/**
* @brief Addition Assignment operator overloading
* Add pSize times of size of the data type to the source data
* 
* @return auto pointer of the object
*/
template<typename Type>
AutoPtr<Type> & AutoPtr<Type>::operator += (const size_t & pSize) noexcept
{
    vPointer += pSize;
    
    return (*this);
}

/**
* @brief Subtraction Assignment operator overloading
* Subtract pSize times of size of the data type from the source data
* 
* @return auto pointer of the object
*/
template<typename Type>
AutoPtr<Type> & AutoPtr<Type>::operator -= (const size_t & pSize) noexcept
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
Type * AutoPtr<Type>::operator + (const size_t & pSize) noexcept
{
    return vPointer + pSize;
}

/**
* @brief Subtraction Assignment operator overloading
* Subtract pSize times of size of the data type from the source data
* 
* @return data source pointer
*/
template<typename Type>
Type * AutoPtr<Type>::operator - (const size_t & pSize) noexcept
{
    return vPointer - pSize;
}

/**
* @brief Equality operator overloading
* 
* @return true, if the two pointers are pointing to the same source data; otherwise false.
*/
template<typename Type>
bool AutoPtr<Type>::operator == (const AutoPtr & pSource) noexcept
{
    return (vPointer == pSource.Get ());
}

/**
* @brief typecast operator overloading
*/
template<typename Type>
template<typename CastType>
AutoPtr<Type>::operator AutoPtr<CastType> ()
{
    return AutoPtr<CastType> ((CastType *) Release ());
}
