#ifndef PRINTF_HPP
#define PRINTF_HPP

/**
* Handled cases:
*   Use of Escape sequence '\n'
*   Passed too few or too many argument
*   use of Custom class 'String' as argument 
*   Passed only string without specifier - no values
* 
* Unhandled Case :
*   when user wants to print '%'
*/

#include "macro.hpp"

/**
* @brief Returns specifier (%) count
*/
inline size_t SpecifierCount (const char * pFormat);

/**
* @return The respective specifier of the pValue
*/
template <typename DataType>
void Display (DataType & pSource);

/**
* @brief Display the pValue
*/
template <typename DataType>
void Printf (DataType pSource);

/**
* @brief Display according to specified format
* Checks for data type of values
* Only allows for integrals, pointer const char * and custom class String
*/
template <typename DataType, typename ...Args>
void Printf (char const * pFormat, DataType pFirstValue, Args... pValues);

/**
* @brief Display according to specified format
* Links the % specifier with respective values
*/
template <typename DataType, typename ...Args>
void OperatePrint (char const * pFormat, DataType pFirstValue, Args... pValues);

#include "printf.hxx"

#endif // !PRINTF_HPP
