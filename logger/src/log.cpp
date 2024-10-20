#include <filesystem>
#include "log.hpp"
#include "string.hpp"

String Logger::sFilePath;

String Logger::sFileName;

String Logger::sMasterFileName = "master_log.txt";

void Logger::Write (String pFilePath, String pSource) 
{
        FILE * file_handle;

    errno_t err = fopen_s (&file_handle, pFilePath.GetString (), "a+");
    
    // file couldn't opened
    if (err) {
        return;
    }
    
    // Write the data on file 
    pSource.Append ("\n");
    fputs (pSource.GetString (), file_handle);
    
    fclose (file_handle);
}

void Logger::LogWrite (String pSource)
{
        String log_master_file  = sFilePath;
        
    // Write on severity files 
    Write (sFileName,       pSource);

    log_master_file.Append (MODE_PATH);
    log_master_file.Append (sMasterFileName);
    
    //Write on master log
    Write (log_master_file, pSource);
}

void Logger::AddLog (eConfigurationMode pMode, eLogType pLogType, String pInfo, String pDetails)
{
        String log_entry;
    
    sFileName = sFilePath;
    
    // update log entry and path according to configuration mode
    switch (pMode) {

        case DEBUG_MODE:
            sFileName.Append("\\Debug\\");
            break;
        case RELEASE_MODE:  
            sFileName.Append("\\Release\\");
            break;

        default:break;
    }

    // update log entry and path according to severity of the log
    switch (pLogType) {

        case ERROR_TYPE:
            log_entry.Append("[ERROR]  ");
            sFileName.Append ("error_");
            break;
        case WARNING_TYPE:
            log_entry.Append("[WARNING]  ");
            sFileName.Append ("warning_");
            break;
        case INFO_TYPE:
            log_entry.Append("[INFO]  ");
            sFileName.Append ("info_");
            break;
        default:
            break;
    }

    sFileName.Append (sMasterFileName);
    
    // add message
    log_entry.Append (pInfo);

    // add additional detail as per users instuctions
    log_entry.Append (pDetails);

    LogWrite (log_entry);
}

String Logger::GetDetail (const char * pFunc, const char * pFile, size_t pLine)
{
        String info;
    
    // Add Date and Time
    info.Append ("\n\tDate and Time: ");
    info.Append (GetDateTime ());

    // Add Function Name
    info.Append ("\tFuntion: ");
    info.Append (pFunc);
    
    // Add File Name
    info.Append ("\n\tFile: ");
    info.Append (pFile);
    
    // Add Line Number
    info.Append ("\n\tLine: ");
    info.Append (pLine);
    
    return info;
}

void Logger::SetFileName (const char * pFileName)
{
    // Set File name according to user
    sMasterFileName = pFileName;
}

void Logger::SetFilePath ()
{
    // Set File Path Bin's Executables Project Folder
    sFilePath = (std::filesystem::current_path ().parent_path ().string ()).c_str ();

    sFilePath.Append ("\\Bin\\Executables\\");
    sFilePath.Append ((std::filesystem::current_path ().filename ().string ()).c_str ());
}

String Logger::GetDateTime()
{
        time_t curr_time = time (nullptr);
        char   date_time [26] = {};

    ctime_s (date_time, 26, &curr_time);
    
    return String (date_time);
}
