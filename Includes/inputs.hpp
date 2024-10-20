#ifndef INPUTS_HPP
#define INPUTS_HPP

#include "macro.hpp"

// Custom Input an Integer value
int                         GetInt                  ();

// Custom Input an Unsigned Integer value
unsigned int                GetUnsignedInt          ();

// Custom Input a Long Long Integer  value
long long int               GetLongLongInt          ();

// Custom Input an Unsigned Long Long Integer  value
unsigned long long int      GetUnsignedLongLongInt  ();

// Custom input a bool value
bool                        GetBool                 ();

//
float                       GetFloat                ();

// Custom input a Double value
double                      GetDouble               ();

// Custom input a character value
char                        GetChar                 ();

// Custom input a string
size_t                      GetString               (char pStr[], const size_t pLength);

#endif // INPUTS_HPP