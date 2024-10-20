#ifndef PROFILER_HPP
#define PROFILER_HPP

#include "string.hpp"

#ifdef DEBUG
#define MODE_PATH "\\Debug\\"
#else
#define MODE_PATH "\\Release\\"
#endif // !DEBUG

// Set Log file path
#define PROFILER_FILE(pFileName) \
            Profiler::SetFileName (pFileName) \

// End Profiler
#define START_PROFILER \
            Profiler::Reset ()

// End Profiler (writes to profiler file)
#define END_PROFILER(pMsg) \
            Profiler::WriteProfile (Profiler::GetFilePath (), pMsg)

// Initialte Profiler

#define INIT_PROFILER \
            Profiler profiler_obj
            
class Profiler {

  public:
                        Profiler            ();
                        ~Profiler           ();
	
    /**
	* @brief Write the source string on master log and severity log files 
	*/
    static void         WriteProfile        (String pFilePath, const char * pSource);

	/**
	* @brief Set Files name as specified by the user  
	*/
    static void         SetFileName         (const char * pFileName);

    /**
	* @brief Reset total Time elapsed to 0
	*/
    static void         Reset               ();
    
    /**
	* @return file path of profiler file
	*/
    static String       GetFilePath         ();

  private:

    static size_t       sCallFrequency;
    static clock_t      sTimeElapsed;
    static clock_t      sStartTime;
    static clock_t      sEndTime;

    static String       sFilePath;
    static String       sFileName;
};

#endif // !PROFILER_HPP
