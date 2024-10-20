#ifndef TEMPLATE_VECTOR_HPP
#define TEMPLATE_VECTOR_HPP

#include "string.hpp"
#include <iostream>

using namespace std;

template <typename T>
using SortComparator = bool (*) (const T &, const T &);

template <typename T>
using ReadIterator = void (*) (T &, void *);

template <typename T>
using WriteIterator = void (*) (T &, void *);

template <class T>
class Vector
{
	static_assert (std::is_integral_v<T> 
                || std::is_same_v<String, T>
                || is_vector_of_strings_or_integrals<T>::value, 
                   "Vector Type must be an Integral, String, or a Vector of these two types.");

  public:
        
                                Vector              ();
                                Vector              (size_t  pSize);
                                Vector              (Vector &  pSource);
                                Vector              (Vector && pSource);
                              ~ Vector              ();
        
        /**
        * @brief Returns true the vector is empty; Otherwise false
        */
                bool            Empty               ()                                                      const;

        /**
        * @brief Push an object of Type <T> at the end of the Vector
        * 
        * @param pSource The sourse object to copy from.
        */
                bool            PushBack            (T & pSource);

                bool            PushBack            (T && pSource);
                
        /**
        * @brief Pop an object from the end of the vector
        */
                bool            PopBack             ();
                
        /**
        * @brief Deletes an object at an index
        * 
        * @param pIndex  The Index to erase source object
        */
                bool            Erase               (size_t pIndex);

        /**
        * @brief Deletes an objects from start index to end index
        * 
        * @param pIndexStart Starting Index of subvector to be eraseed
        * @param pIndexEnd   Ending Index of subvector to be eraseed (exclusive)
        */
                bool            Erase               (size_t pIndexStart, size_t pIndexEnd);
                
        /**
        * @brief Swap Objects at index pIndexA and index pIndexB
        * 
        * @param pIndexA Index of 1st object to be swapped
        * @param pIndexB Index of 1st object to be swapped
        */
                bool            Swap                (size_t pIndexA, size_t pIndexB);

        /**
        * @brief Swap two vectors.
        * 
        * @param pOther Other Vector to be swapped with.
        */
                void            Swap                (Vector<T> & pOther);

        /**
        * @brief Returns the size of the vector
        */
                size_t          Size                ()                                                      const;

        /**
        * @brief Returns the object at an index
        * 
        * @param pIndex Index of the desired object
        */
                T         &     At                  (size_t pIndex)                                         const;

        /**
        * @brief Overloaded operator [] which returns the object at an index
        * 
        * @param pIndex Index of the desired object
        */
                T         &     operator     []     (size_t pIndex)                                         const;
        
        /**
        * @brief Overloaded assignment operator to copy one object data from other object
        * 
        * @param pSource The sourse object to copy data from.
        */
                Vector<T> &     operator     =      (Vector<T> const & pSource);

                Vector<T> &     operator     =      (Vector<T> && pSource)                                  noexcept;

        /**
        * @brief Removes all the objects from the vector and leaves vector with size 0.
        */
                void            Clear               ();

                void            Display             ();
                
        /**
        * @brief Sort the vector based on a comparator method 
        * 
        * @param pComparatorFunc Pointer to comparator method based on which sorting is performed.
        */
                void            Sort                (SortComparator<T> pCopmaratorFunc = nullptr);

        /**
        * @brief Read each element of vector according to ReadIterator Method 
        * 
        * @param pReader Pointer to method according to which reading is performed.
        * @param pParams parameters to method according to which reading is performed.
        */
                void            Read                (ReadIterator <T> pReader, void * pParams = nullptr)    const;

        /**
        * @brief Write each element of vector according to WriteIterator Method 
        * 
        * @param pWriter Pointer to method according to which writing is performed.
        * @param pParams parameters to method according to which writing is performed.
        */
                void            Write               (WriteIterator<T> pWriter, void * pParams = nullptr);

        /**
        * @brief comparator for integral values
        */
        static  bool            IntComparator       (const T      & pIntA, const T      & pIntB);

        /**
        * @brief comparator for String values
        */
        static  bool            StringComparator    (const String & pStrA, const String & pStrB);
        
  private:
        
        /**
        * @brief Allocates memory for new elements
        */
                bool            AllocateMemory      ();

        /**
        * @brief Format Specifier for display elements
        */
        const   char     *      GetFormatSpecifier  ()                                                      const;

                T        *      vElements;
                size_t          vSize;
                size_t          vCapacity;
};


template <typename T>
std::ostream &  operator << (std::ostream & os, Vector<T> const & pSource);

#include "vector.hxx"

#endif // !TEMPLATE_VECTOR_HPP
