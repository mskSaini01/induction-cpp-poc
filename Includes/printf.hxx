#ifndef PRINTF_HXX
#define PRINTF_HXX

#include <type_traits>
#include <assert.h>
#include <iostream>
#include "printf.hpp"

class String;

/**
* @brief Returns specifier (%) count
*/
inline size_t SpecifierCount (const char * pFormat)
{
        size_t percent_count   = 0;

    for (int i = 0; pFormat[i] != NULL_CHAR; i++) {
        
        if (pFormat[i] == '%') {
            ++percent_count;
        }
    }
    return percent_count;
}

/**
* @brief Returns the respective specifier of the pValue
*/
template <typename DataType>
void Display (DataType & pSource) 
{
    if constexpr (std::is_same_v<DataType,bool>) {
        printf ("%d", pSource);

    } else if constexpr (std::is_same_v<DataType, char const *>) {
        printf ("%s", pSource);

    } else if constexpr (std::is_same_v<DataType, char> || std::is_same_v<DataType, char16_t> || std::is_same_v<DataType, char32_t>) {
        printf ("%c", pSource);

    } else if constexpr (std::is_same_v<DataType, wchar_t>) {
        printf ("%lc", pSource);

    } else if constexpr (std::is_signed_v<DataType>) {

        if constexpr (std::is_same_v<DataType, signed char>) {
            printf ("%hhd", pSource);

        } else if constexpr (std::is_same_v<DataType, short int>) {
            printf ("%hd", pSource);

        } else if constexpr (std::is_same_v<DataType, int>) {
            printf ("%d", pSource);

        } else if constexpr (std::is_same_v<DataType, long int>) {
            printf ("%ld", pSource);

        } else if constexpr (std::is_same_v<DataType, long long int>) {
            printf ("%lld", pSource);
        }

    } else if constexpr (std::is_unsigned_v<DataType>) {

        if constexpr (std::is_same_v<DataType, unsigned char>) {
            printf ("%hhu", pSource);

        } else if constexpr (std::is_same_v<DataType, unsigned short int>) {
            printf ("%hu", pSource);

        } else if constexpr (std::is_same_v<DataType, unsigned int>) {
            printf ("%u", pSource);

        } else if constexpr (std::is_same_v<DataType, unsigned long int>) {
            printf ("%lu", pSource);

        } else if constexpr (std::is_same_v<DataType, unsigned long long int>) {
            printf ("%llu", pSource);
        }

    } else if constexpr (std::is_same_v<DataType, String>) {
        // Custom class 'String' Handled
        std::cout << pSource;
    } 
}

/**
* @brief Display pValue as per its respective specifier
*/
template <typename DataType>
void Printf (DataType pSource)
{
    if constexpr (std::is_same_v<DataType, const char *>) {
        assert (SpecifierCount (pSource) == 0);
    }

    Display (pSource);
}

/**
* @brief Display according to specified format 
* Checks for data type of values 
* Only allows for integrals, pointer const char * and custom class String
*/
template <typename DataType, typename ...Args>
void Printf (char const * pFormat, DataType pFirstValue,  Args... pValues) 
{
	static_assert (std::is_same_v<DataType, bool>       || std::is_same_v<DataType, char>
                || std::is_same_v<DataType, wchar_t>    || std::is_same_v<DataType, String>
                || std::is_unsigned_v<DataType>         || std::is_signed_v<DataType>,
                "Used for invalid data type");

    // Alert if the argument count is different
    assert ((SpecifierCount (pFormat) == 1 + sizeof ...(pValues)));
    
    OperatePrint (pFormat, pFirstValue, pValues...);
}

/**
* @brief Display according to specified format 
* Links the % specifier with respective values
*/
template <typename DataType, typename ...Args>
void OperatePrint (char const * pFormat, DataType pFirstValue, Args... pValues) 
{
    while (*pFormat != NULL_CHAR) {
        
        if (*pFormat == '%') {

            Printf (pFirstValue);
                
            ++pFormat;
                
            if constexpr (sizeof...(pValues)) {
                OperatePrint (pFormat, pValues...);
                return;

            } else {
                return;
            }
        }
        else {
            Printf (*pFormat);
            ++pFormat;
        }
    }
}

#endif // !PRINTF_HXX
