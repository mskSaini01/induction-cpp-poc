#ifndef STRING_HPP
#define STRING_HPP

#include <iostream>
#include "macro.hpp"

class String {

  public:
        
    // Initialize String with "", and length with 0
                                String                  ();
    
    // Initialize String with constant string literal
                                String                  (const char * pStr);

    // Initialize String with String object
                                String                  (const String & pSource);

    // Initialize String with String object using move constructor
                                String                  (String && pSource)         noexcept;

    // Destruct String Object
                                ~String                 ();

    // @return String Value
            char *              GetString               ()                          const;

    // @return true if string is empty, otherwise false
            bool                Empty                   ()                          const;
    
    // @return String Length
            size_t              GetLength               ()                          const;

    // @return The first occurance (index) of a given character, otherwise -1
            size_t              Find                    (const char pChar)          const;
    
    // @return The character at a given index
            char                CharAt                  (size_t index)              const;

    // Displays the String Value and String Length
            void                Display                 ()                          const;
    
    // Inputs a dynamic string from terminal
            void                InputStr                ();

    // Swaps two strings
            void                Swap                    (String & pStr);

    // Clear All the characters from the string 
            void                Clear                   ();

    // Reverse a string 
            void                Reverse                 ();
    
    // Append a constant character literal at the end
            void                PushBack                (const char pSource);

    // Pop a string from the end
            void                PopBack                 ();

    // Append a constant string literal at the end
            void                Append                  (const char * substr);

    // Append a string at the end
            void                Append                  (String const & pSource);

    // Appends an size_t integer 
            void                Append                  (size_t pSource);

    // Copies a constant string literal to a string
            void                StrCpy                  (const char * pSource);

    // Copies a string
            void                StrCpy                  (const String & pSource);

    /* Overloaded operator ( = ) with Constant String Literal
        @return Assigned String Object*/
            String &            operator =              (const char * pSource);

    /* Overloaded operator ( = ) with String Object
        @return Assigned String Object*/
            String &            operator =              (String const & pSource);
    
    /* Overloaded operator ( = ) with move operations on String Object
        @return Assigned String Object*/
            String &            operator =              (String && pSource) noexcept;
    
    /* Overloaded operator ( +) with Constant String Literal
        @return Assigned String Object*/
            String              operator +              (const char * pSource);
    
    /* Overloaded operator ( + ) with String Object
        @return Assigned String Object*/
            String              operator +              (String const & pSource);
    
    /* Overloaded operator ( [] ) with index
        @return Character at a given index*/
            char &              operator []             (size_t pIndex);
    
    /* Overloaded operator ( + ) with String Object
        @return true if both Stings are equal, otherwise false*/
            bool                operator ==             (const String & pSource);

            /* Overloaded insertion operator ( << ) with String Object
                    Prints the string value in string object */
    friend  std::ostream &      operator <<             (std::ostream & os, String const & pSource);

private:

    // @return Constant String literal length
    size_t      GetStrLength    (const char * pStr);

    // Adds a character to a string at a given index
    void        AddChar         (char * pStr, char & pInput, size_t & pIndex);

    // Reallocate the string to size of pSize number of characters
    void        Allocate        (size_t pSize);

    char *      vString;
    size_t      vLength;
};

#endif // !STRING_HPP
