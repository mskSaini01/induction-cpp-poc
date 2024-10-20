#ifndef HASH_HPP
#define HASH_HPP

#include <type_traits>
#include "string.hpp"

/**
* @brief Templatized class for hashing
*/
template <typename KeyType, size_t Size>
class Hash {

  public:
	/**
	* @brief Calculates the integral hash of a key
	* if arithematic, use Modulo operation with Max Size
	* if string value, use XOR of every character in string
	* @return Intergral Hash value of the key
	*/
	static		size_t		GetHash		(KeyType pKey);
};

#include "hash.hxx"

#endif // !HASH_HPP
