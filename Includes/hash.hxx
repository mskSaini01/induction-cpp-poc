#ifndef HASH_HXX
#define HASH_HXX

#include <type_traits>

#include "hash.hpp"

/**
* @brief Calculates the integral hash of a key
* if arithematic, use Modulo operation with Max Size
* if string value, use XOR of every character in string
* @return Intergral Hash value of the key
*/
template<typename KeyType, size_t Size>
size_t Hash<KeyType, Size>::GetHash (KeyType pKey)
{
	// Modulo operation for integral and floating values
	if constexpr (std::is_arithmetic_v<KeyType>) {
		return (size_t)pKey % Size;
	
	} else if constexpr (std::is_same_v<KeyType, char *> || std::is_same_v<KeyType, String>) {
			char * string;
			size_t res;
		
		// XOR of every character for string value
		if constexpr (std::is_same_v<KeyType, char*>) {
			string = pKey;

		} else {
			string = pKey.GetString ();
		}

		res = (size_t) string[0];
		
		for (size_t i = 1; string[i] != '\0'; i++) {
			res ^= string[i];
		}

		return res % Size;
	}
}

#endif // !HASH_HXX
