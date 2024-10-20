#include <filesystem>
#include "profiler.hpp"
#include "string.hpp"

size_t   Profiler::sCallFrequency = 0;
clock_t  Profiler::sTimeElapsed   = 0;
clock_t  Profiler::sStartTime     = 0;
clock_t  Profiler::sEndTime       = 0;
String   Profiler::sFileName      = "";


void Profiler::SetFileName (const char * pFileName)
{
        String path;

    // Set File Path Bin's Executables Project Folder
    path = (std::filesystem::current_path ().parent_path ().string ()).c_str ();
    path.Append ("\\Bin\\Executables\\");
    path.Append ((std::filesystem::current_path ().filename ().string ()).c_str ());
    path.Append (MODE_PATH);

    // Set File name according to user
    sFileName = path;
    sFileName.Append (pFileName);
}

void Profiler::Reset ()
{
    sTimeElapsed    = 0;
    sCallFrequency  = 0;
}

String Profiler::GetFilePath ()
{
    return sFileName;
}

Profiler::Profiler ()
{
    //start timer
    sStartTime = clock ();
    
    //increment call frequency
    ++sCallFrequency;
}

Profiler::~Profiler ()
{
    // Start timer
    sEndTime = clock ();
    
    // Add to profiler's Elapsed Time
    sTimeElapsed += sEndTime-sStartTime;
}

void Profiler::WriteProfile (String pFilePath, const char * pSource)
{
        FILE * file_handle;
        String profile = pSource;

    errno_t err = fopen_s (&file_handle, pFilePath.GetString (), "a+");
    
    // file couldn't opened
    if (err) {
        return;
    }
    
    // Write the data on file 
    profile.Append ("\nFrequency : ");
    profile.Append (sCallFrequency);
    profile.Append ("\nTime Elapsed: ");
    profile.Append (sTimeElapsed);
    profile.Append ("ms\n\n");
    fputs (profile.GetString (), file_handle);
    
    fclose (file_handle);
}
