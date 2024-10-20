#ifndef STACK_HXX
#define STACK_HXX
#include "stack.hpp"

template<typename DataType>
void Stack<DataType>::Push (DataType pData)
{
    Vector<DataType>::PushBack (pData);
}

template<typename DataType>
void Stack<DataType>::Pop ()
{
    Vector<DataType>::PopBack ();
}

template<typename DataType>
void Stack<DataType>::Clear ()
{
    Vector<DataType>::Clear ();
}

template<typename DataType>
size_t Stack<DataType>::Size () const
{
    return Vector<DataType>::Size ();
}

template<typename DataType>
bool Stack<DataType>::Empty () const
{
    return  Vector<DataType>::Empty ();
}

template<typename DataType>
void Stack<DataType>::Display () const
{
    Vector<DataType>::Display ();
}

template<typename DataType>
DataType Stack<DataType>::Top () const
{
    if (Vector<DataType>::Size() == 0) {
        return DataType ();
    }
    DataType data = Vector<DataType>::At (Vector<DataType>::Size () - 1);
    return data;
}

#endif // !STACK_HXX
