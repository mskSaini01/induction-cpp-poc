#ifndef HASHMAP_HPP
#define HASHMAP_HPP

//#include "vector.hpp"
#include "linked_list.hpp"
#include "hash.hpp"

// Size of the Hashing list
#define HASH_MAP_MAX_SIZE 1024

/**
* @brief Key Value pair for hashing list
*/
template <typename Key, typename Value>
struct tKeyValuePair {
    Key     uKey;
    Value   uValue;
};

template <typename Key, typename Value>
class HashMap {

  public:
                                        HashMap             ();
                                        ~HashMap            ();

        /**
        * @brief Inserts a key value pair in hashing list if key does not exists; otherwise update its value
        */
        void                            Insert              (Key pKey, Value pValue);
        
        /**
        * @return Hash of the the key
        */
        size_t                          GetHash             (Key pKey)          const;

        /**
        * @return Number of pairs in hashmap
        */
        size_t                          GetEntryCount       ()                  const;
        
        /**
        * @brief Find the key using Hash of a key 
        * Checks if collision occurs, find in all the pairs with the same key hash in list of pairs
        * @return Value associated to a specific key
        */
        Value                           Find                (Key pKey)          const;
        
        /**
        * @brief Deletes the Key Value pair in the hashing list
        * @return true if the deletion was successful; otherwise false
        */
        bool                            Delete              (Key pKey);

  private:
      
        /**
        * @brief Search for key value pair in hashing list associated to a specific key
        * @return pointer to pair if found; otherwise nullptr
        */
        tKeyValuePair <Key, Value> *    Search              (Key & pKey)        const;

        LinkedList <tKeyValuePair <Key, Value>> *   vPairs;
	    size_t                                      vPairsCount;
};

#include "hashmap.hxx"

#endif // !HASHMAP_HPP
