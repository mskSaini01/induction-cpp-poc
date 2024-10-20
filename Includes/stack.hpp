#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

template <typename DataType>
class Stack: protected Vector<DataType> {

  public:

        void          Push            (DataType pData);
        void          Pop             ();
        void          Clear           ();
        void          Display         ()                      const;
        size_t        Size            ()                      const;
        bool          Empty           ()                      const;
        DataType      Top             ()                      const;
};

#include "stack.hxx"

#endif // !STACK_HPP
