#ifndef HASHMAP_HXX
#define HASHMAP_HXX

#include "hashmap.hpp"
#include "vector.hpp"
#include "linked_list.hpp"

template <typename Key, typename Value>
HashMap<Key, Value>::HashMap ()
{
    vPairsCount   = 0;
    vPairs = new LinkedList <tKeyValuePair <Key, Value>> [HASH_MAP_MAX_SIZE];
}

template<typename Key, typename Value>
HashMap<Key, Value>::~HashMap ()
{
    vPairsCount   = 0;

    delete [] vPairs;
    vPairs = nullptr;
}

template<typename Key, typename Value>
size_t HashMap<Key, Value>::GetHash (Key pKey) const
{
    return Hash<Key, HASH_MAP_MAX_SIZE>::GetHash (pKey);
}

template<typename Key, typename Value>
size_t HashMap<Key, Value>::GetEntryCount() const
{
    return vPairsCount;
}

template<typename Key, typename Value>
void HashMap<Key, Value>::Insert (Key pKey, Value pValue)
{
        size_t                      hash    = GetHash (pKey);
        tKeyValuePair<Key, Value> * element = Search  (pKey);

    if (!element) {
            tKeyValuePair<Key, Value> new_pair (pKey, pValue);

        vPairs[hash].PushBack (new_pair);
        ++vPairsCount;
        return;
    }

    element->uValue = pValue;
}

template<typename Key, typename Value>
Value HashMap<Key, Value>::Find (Key pKey) const
{
        tKeyValuePair <Key, Value> * element = Search (pKey);

    if (!element) {
        return Value ();
    }

    return element->uValue;
}

template<typename Key, typename Value>
bool HashMap<Key, Value>::Delete (Key pKey)
{
        size_t                                      count       = 0;
        size_t                                      hash        = GetHash (pKey);
        LinkedList <tKeyValuePair <Key, Value>> &   list        = vPairs[hash];
        tNode <tKeyValuePair <Key, Value>> *        curr_pair   = list.GetHead ();

    if (!curr_pair) {
        return false;
    }

    while (curr_pair != list.GetTail ()->uNext) {

        if (pKey == curr_pair->uData.uKey) {
            list.PopAt (count);
            return true;
        }
        count++;
        curr_pair = curr_pair->uNext;
    }

   return false;
}

template<typename Key, typename Value>
tKeyValuePair<Key, Value> * HashMap<Key, Value>::Search (Key & pKey) const
{
        size_t                                            hash       = GetHash (pKey);
        LinkedList <tKeyValuePair <Key, Value>> &         list       = vPairs[hash];
        tNode <tKeyValuePair <Key, Value>> *              curr_node  = list.GetHead ();

    if (!list.Size()) {
        return nullptr;
    }

    while (curr_node != list.GetTail ()->uNext) {

        if (pKey == curr_node->uData.uKey) {
            return &curr_node->uData;
        }
        curr_node = curr_node->uNext;
    }

    return nullptr;
}

#endif