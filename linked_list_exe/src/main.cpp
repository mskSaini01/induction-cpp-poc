#include <stdio.h>
#include "linked_list.hpp"
#include "printf.hpp"
#include "log.hpp"
#include "profiler.hpp"

struct tParams {

            tParams () : uNode (nullptr) {};

    void * uNode;
};

template<typename T>
void IterateMethod (tNode<T> * pNode, void *) 
{
    Printf ("% ", pNode->uData);
}

int main()
{
        LinkedList<int>     list;
        tNode     <int> *   node_holder;
        tParams             params;
    
    Log_File ("logs.txt");

    list.PushBack (2);
    list.PushFront (1);
    list.PushBack (3);
    
    Printf ("\nList Values\n");
    params.uNode = list.GetHead (); 
    list.ListIterator (IterateMethod, &params);

    Printf ("\nIs List Empty = %\n", list.Empty ());
    
    LINE_BREAK;

    list.PushFront (0);
    Printf ("\nList Values after poping from front\n");
    list.Display  ();

    LINE_BREAK;

    list.PopAt (1);
    Printf ("\nList Values after poping index 1\n");
    list.Display  ();

    LINE_BREAK;

    list.PopAt (1);
    Printf ("\nList Values after poping index 1\n");
    list.Display  ();
    
    LINE_BREAK;

    node_holder = list.GetTail ();
    Printf ("\n\nTail Node = %", node_holder->uData);

    node_holder = list.GetNodeAt(0);
    Printf ("\n\nNode at 0 = %", node_holder->uData);

    Printf ("\n\nIs node Tail = %", (node_holder == list.GetTail ()));

    node_holder = list.GetNext (* node_holder);
    Printf ("\n\nNext Node = %", node_holder->uData);

    LINE_BREAK;

    list.PopFront ();
    Printf ("\nList Values after poping front\n");
    list.Display  ();

    list.Clear ();
    Printf ("\n\nList Values after clearing\n");
    list.Display  ();

    PROFILER_FILE ("profiler.txt");

    START_PROFILER;
    for (int i = 0; i < 1000; i++) {
        INIT_PROFILER;
        list.PushBack (1);
    }
    END_PROFILER ("Profile for PushBacks in list");
    
    START_PROFILER;
    for (int i = 0; i < 1000; i++) {
        INIT_PROFILER;
        list.PopBack ();
    }
    END_PROFILER ("Profile for PopBacks in list");
    
    START_PROFILER;
    {
        INIT_PROFILER;
        list.PushFront (1);
    }
    END_PROFILER ("Profile for PushFront in list");

    
    START_PROFILER;
    {
        INIT_PROFILER;
        list.PushBack (1);
    }
    END_PROFILER ("Profile for PushFront in list");
    
    tNode<int> * node = new tNode<int> (1);
    
    START_PROFILER;
    {
        INIT_PROFILER;
        list.InsertAfter (1, *node);
    }
    END_PROFILER ("Profile for insert at index 1 in list");
}
