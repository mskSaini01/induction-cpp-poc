#include "trace_func.hpp"
#include "string.hpp"

#ifdef DEBUG

// Trace record initialization
Stack<String> TraceFunc::vTraces;

// Records Trace for every instance;
TraceFunc::TraceFunc (const char * pFunc, const char * pFile, size_t pLine)
{
        String trace;

    trace.Append (pFunc);
    trace.Append (",\t");
    trace.Append (pFile);
    trace.Append (",\t");
    trace.Append (pLine);
    
    vTraces.Push(trace);
}

// Pops the trace when the control goes out the scope for an instance
TraceFunc::~TraceFunc ()
{
    vTraces.Pop ();
}

// Display All Recorded Traces
void TraceFunc::DisplayTraces ()
{
        Stack<String> &   traces = vTraces;

    Printf ("Trace Stack: \n");
    
    while (!traces.Empty ()) {
        Printf (traces.Top ());
        Printf ("\n");
        traces.Pop ();
    }
}

#endif // DEBUG
