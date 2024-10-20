#include <stdio.h>
#include <iostream>
#include "string.hpp"
#include "vector.hpp"

/**
 * @brief Type trait to determine if a type is an array of strings or integrals when wrapped in the 'Array' template.
 */
template <typename T>
struct is_vector_of_strings_or_integrals : std::false_type {};

/**
 * @brief Specialization of the 'is_array_of_strings_or_integrals' trait for 'Array<T>'.
 */
template <typename T>
struct is_vector_of_strings_or_integrals<Vector<T>> :
    std::disjunction<
        std::is_same<T, String>,
        std::is_integral<T>,
		is_vector_of_strings_or_integrals<T>
    >
{};

template <typename T>
Vector<T>::Vector ()
{
    vElements = nullptr;
    vCapacity = 0;
    vSize     = 0;
}

template <typename T>
Vector<T>::Vector (size_t pSize)
{
    vElements = new (std::nothrow) T [pSize];

    if (vElements == nullptr) {
        vCapacity   = 0;
        vSize       = 0;
        vElements   = nullptr;

    } else {
		vSize       = pSize;
		vCapacity	= pSize;
	}
}

template<typename T>
Vector<T>::Vector (Vector & pSource)
{
    vElements	= new (std::nothrow) T [pSource.vSize];
	vCapacity	= pSource.vCapacity;
	vSize		= pSource.vSize;

    if (vElements == nullptr) {
        vElements = pSource.vElements;

    } else {

        for (int i = 0; i < vSize; i++) {
            vElements[i] = pSource.vElements[i];
        }
	}
}

template <typename T>
Vector<T>::Vector (Vector && pSource)
{
	vElements				= pSource.vElements;
	vSize					= pSource.vSize;
	vCapacity				= pSource.vCapacity;

	pSource.vElements		= nullptr;
}

template <typename T>
Vector<T>::~Vector ()
{
    if (vElements == nullptr) {
		return;
	}

    delete [] vElements;
    
    vElements   = nullptr;
    vCapacity   = 0;
    vSize       = 0;
}

// Returns weather the vector is empty or not
template<typename T>
bool Vector<T>::Empty() const
{
    return (vSize == 0);
}

// Returns number of objects in vector
template <typename T>
size_t Vector<T>::Size ()   const
{
    return vSize;
}

// Push an object at the Back of the Vector
template <typename T>
bool Vector<T>::PushBack (T & pSource)
{
	if (vCapacity == vSize) {
		if (!AllocateMemory()) {
			return false;
		}
	}
	
	vElements[vSize++] = pSource;
	return true;
}

// Push an object at the Back of the Vector
template <typename T>
bool Vector<T>::PushBack (T && pSource)
{
	if (vCapacity == vSize) {
		if (!AllocateMemory()) {
			return false;
		}
	}
	
	vElements[vSize++] = std::move (pSource);
	return true;
}

// Pop an object from the Back of the Vector
template <typename T>
bool Vector<T>::PopBack ()
{
    if (vSize == 0) {
        return false;
    }

    --vSize;
    return true;
}

// Assignment Operator Overload for Vector assignment 
template <typename T>
Vector<T> & Vector<T>::operator = (Vector<T> const & pSource)
{
	if (vElements != nullptr) {
		delete [] vElements;
		vElements = nullptr;
	}

	vSize			= pSource.vSize;
	vCapacity		= pSource.vCapacity;
	vElements		= new (std::nothrow) T [vSize];

	if (vElements == nullptr) {
		vElements = pSource.vElements;

	} else {

		for (size_t i = 0; i < vSize; ++i) {
			vElements[i] = pSource.vElements[i];
		}
	}

	return (* this);
}

// Assignment Operator Overload for Vector assignment 
template <typename T>
Vector<T> & Vector<T>::operator = (Vector<T> && pSource) noexcept
{
	if (vElements != nullptr) {
		delete [] vElements;
		vElements = nullptr;
	}

	vSize			    = pSource.vSize;
	vCapacity		    = pSource.vCapacity;
	vElements		    = pSource.vElements;

	pSource.vElements   = nullptr;

	return (* this);
}

// Deletes an element (String Object) at an index
template <typename T>
bool Vector<T>::Erase (size_t pIndex)
{
    if (pIndex >= vSize) {
        
        return false;
    }

    // move the strings one step ahead till pIndex
    for (size_t index = (pIndex + 1); index < vSize - 1; index++) {

        Swap (index, index - 1);
    }

    --vSize;
    
    return true;
}

// Deletes an Object from one index to another index (exclusive)
template <typename T>
bool Vector<T>::Erase (size_t pIndexStart, size_t pIndexEnd)
{
    // invalid index check
	if (pIndexStart >= vSize) {
        
        return false;
    }

    if (pIndexStart > pIndexEnd) {
        
        return false;
    }

    if (pIndexStart == pIndexEnd) {
        
        if (Erase (pIndexStart)) {
            
            return true;
        }
        else {

            return false;
        }
    }

    if (pIndexStart >= vSize) {

        pIndexEnd = vSize - 1;
    }

    // move the strings remaining right part after pIndexStart
    for (size_t index = (pIndexEnd); index < vSize; index++) {

        Swap (index, (pIndexStart + (index - pIndexEnd)));
    }

    vSize -= (pIndexEnd - pIndexStart);
            
    return true;
}

// Return the object at an index by overloading operator []
template <typename T>
T & Vector<T>::operator [] (size_t pIndex) const
{
    if (pIndex < vSize) {
        return vElements[pIndex];
    }
    return (* new T ());
}

// Returns the object at an index
template <typename T>
T & Vector<T>::At (size_t pIndex) const
{
	return vElements[pIndex];
}

// Removes all elements from vector and leaves array size with 0.
template <typename T>
void Vector<T>::Clear ()
{
    vSize		= 0;
	vCapacity	= 0;

	if (vElements == nullptr) {
		return;
	}

	delete [] vElements;
	vElements = nullptr;
}

template<typename T>
void Vector<T>::Display()
{
    printf ("{");

	for (size_t i = 0; i < vSize; ++i) {

		if constexpr (std::is_integral<T>::value) {
			printf (GetFormatSpecifier(), vElements[i]);

		} else if constexpr (std::is_same<T, String>::value) {
			vElements[i].Display ();

		} else {
			vElements[i].Display ();
		}

		if (i != vSize - 1) {
			printf (",");
		}
	}

	printf ("}");
}

// Swap the objects at index pIndexA and index pIndexB
template <typename T>
bool Vector<T>::Swap (size_t pIndexA, size_t pIndexB)
{
        T intr_element;

    // invalid index check
	if (pIndexA >= vSize) {
        
        return false;
    }

    if (pIndexB >= vSize) {
        
        return false;
    }

    intr_element        = vElements[pIndexB];
    vElements[pIndexB]  = vElements[pIndexA];
    vElements[pIndexA]  = intr_element;
    
    return true;
}

// Swap the objects at index pIndexA and index pIndexB
template <typename T>
void Vector<T>::Swap (Vector<T> & pOther)
{
        T		*	intr_velements	    = nullptr;
        size_t		intr_vsize		    = 0;
		size_t		intr_vcapacity	    = 0;

    intr_velements      = vElements;
    intr_vcapacity      = vCapacity;
    intr_vsize          = vSize;

    vElements           = pOther.vElements;
    vCapacity           = pOther.vCapacity;
    vSize               = pOther.vSize;

    pOther.vElements    = intr_velements;
    pOther.vCapacity    = intr_vcapacity;
    pOther.vSize        = intr_vsize;
}

// Sort the array of strings based on a comparator method pFuncPtr
template <typename T>
void Vector<T>::Sort (SortComparator<T> pCopmaratorFunc)
{
    if constexpr (std::is_same_v<T, String>){
		
        if (pCopmaratorFunc == nullptr) {
			pCopmaratorFunc = StringComparator;
		}

	} else if constexpr (std::is_integral_v<T>) {
		
        if (pCopmaratorFunc == nullptr) {
			pCopmaratorFunc = IntComparator;
		}

	} else if (pCopmaratorFunc == nullptr) {
		return;
	}

	for (size_t i = 0; i < vSize - 1; i++) {

		for (size_t j = i + 1; j < vSize; j++) {
			
            if (pCopmaratorFunc (vElements[i], vElements[j])) {
                Swap (i, j);
			}
		}
	}
}

// Comparator for integeral values
template<typename T>
bool Vector<T>::IntComparator (const T & pIntA, const T & pIntB)
{
	return pIntA > pIntB;
}

// Comparator for string objects
template<typename T>
bool Vector<T>::StringComparator (const String & pStrA, const String & pStrB)
{
	return (pStrA.GetString () > pStrB.GetString ());
}

/**
* @brief Read each element of vector according to ReadIterator Method 
* 
* @param pReader Pointer to method according to which reading is performed.
* @param pParams parameters to method according to which reading is performed.
*/
template<typename T>
void Vector<T>::Read (ReadIterator<T> pReader, void* pParams) const
{
	for (size_t index = 0; index < vSize; index++) {
		pReader (vElements[index], pParams);
	}
}

/**
* @brief Write each element of vector according to WriteIterator Method 
* 
* @param pWriter Pointer to method according to which writing is performed.
* @param pParams parameters to method according to which writing is performed.
*/
template<typename T>
void Vector<T>::Write (WriteIterator<T> pWriter, void * pParams)
{
	for (size_t index = 0; index < vSize; index++) {
		pWriter (vElements[index], pParams);
	}
}

// Allocates memory for new elements
template <typename T>
bool Vector<T>::AllocateMemory ()
{
		T * new_elements;

	if (vCapacity == 0) {
		vCapacity = 1;

	} else {
		vCapacity *= 2;
	}

	new_elements =	new (std::nothrow) T [vCapacity];

	if (new_elements == nullptr) {
		return false;
	}

	for (size_t i = 0; i < vSize; i++) {
		new_elements[i] = vElements[i];
	}

	delete[] vElements;

	vElements       = nullptr;
	vElements       = new_elements;
    new_elements    = nullptr;

	return true;
}

// Returns Format specifier for the data type T
template <typename T>
const char * Vector<T>::GetFormatSpecifier () const {

    if constexpr (std::is_same_v<T, bool>) {
        return "%d";

    } else if constexpr (std::is_same_v<T, char> || std::is_same_v<T, char16_t> || std::is_same_v<T, char32_t>) {
        return "%c";

    } else if constexpr (std::is_same_v<T, wchar_t>) {
        return "%lc";

    } else if constexpr (std::is_signed<T>::value) {

        if constexpr (std::is_same_v<T, signed char>) {
            return "%hhd";

        } else if constexpr (std::is_same_v<T, short int>) {
            return "%hd";

        } else if constexpr (std::is_same_v<T, int>) {
            return "%d";

        } else if constexpr (std::is_same_v<T, long int>) {
            return "%ld";

        } else if constexpr (std::is_same_v<T, long long int>) {
            return "%lld";
        }
    } else if constexpr (std::is_unsigned<T>::value) {

        if constexpr (std::is_same_v<T, unsigned char>) {
            return "%hhu";

        } else if constexpr (std::is_same_v<T, unsigned short int>) {
            return "%hu";

        } else if constexpr (std::is_same_v<T, unsigned int>) {
            return "%u";

        } else if constexpr (std::is_same_v<T, unsigned long int>) {
            return "%lu";

        } else if constexpr (std::is_same_v<T, unsigned long long int>) {
            return "%llu";
        }
    }
}

// Operator overloading for <<
template <typename T>
std::ostream& operator     <<     (std::ostream& os, Vector<T> const & pSource)
{
    os << "{";

    for (int i = 0; i < pSource.Size(); i++) {
        os << pSource[i] << " ";
    }
    os << "}";
    
    os << "\n";

    return os;
}
