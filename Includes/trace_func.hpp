#ifndef TRACE_FUNC_HPP
#define TRACE_FUNC_HPP

#include "stack.hpp"
#include "printf.hpp"

#ifdef DEBUG

// recoding the metadata of a haulted control at a line 
#define TRACEFUNC \
        TraceFunc trace (__FUNCTION__, __FILE__, __LINE__)

// Display Traces if the condition is false and terminate the execution; otherwise do nothing
#define ASSERT(condition); \
        if (!(condition)) { \
            TraceFunc::DisplayTraces(); \
            std::terminate(); \
        }

class TraceFunc {

  public:
                    TraceFunc     (const char* pFunc, const char* pFile, size_t pLine);
                    ~TraceFunc    () ;
    
        // Used for displaying Function traces
        static void DisplayTraces () ;

  private:
        // Trace record of functions
        static Stack<String> vTraces;
};

#else // !DEBUG

#define TRACEFUNC  
#define ASSERT(consition)  

#endif // !NDEBUG

#endif // !TRACE_FUNC_HPP
