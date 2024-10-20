#ifndef LOG_HPP
#define LOG_HPP

#include "string.hpp"

enum eConfigurationMode {
    DEBUG_MODE,
    RELEASE_MODE
};

enum eLogType{
    ERROR_TYPE,
    WARNING_TYPE,
    INFO_TYPE
};

#ifdef DEBUG
#define MODE_PATH "\\Debug\\"
#else
#define MODE_PATH "\\Release\\"
#endif // !DEBUG


// Set Log file path
#define Log_File(pFileName) \
            Logger::SetFileName (pFileName); \
            Logger::SetFilePath ();

// Log macro for user
#define Log(pMode,pType,pMsg,pAddDetails) \
            if (pAddDetails) { \
                Logger::AddLog (pMode, pType, pMsg, Logger::GetDetail (__FUNCTION__, __FILE__, __LINE__)); \
            } else { \
                Logger::AddLog (pMode, pType, pMsg); \
            }

class Logger {
  public:
      
	/**
	* @brief Write the source string on file 
	*/
    static void         Write           (String pFilePath, String pSource);
    
	/**
	* @brief Write the source string on master log and severity log files 
	*/
    static void         LogWrite        (String pSource);

	/**
	* @brief add log based on configuration mode, log type, and additional file based on users choice  
	*/
    static void         AddLog          (eConfigurationMode pMode, eLogType pLogType, String pModeInfo, String pDetails = "");
    
	/**
	* @brief Get additional Details based on users choice  
	*/
    static String       GetDetail       (const char * pFunc, const char * pFile, size_t pLine);
    
	/**
	* @brief Set Files name as specified by the user  
	*/
    static void         SetFileName     (const char * pFileName);
    
	/**
	* @brief Set Files path to Bin's executables
	*/
    static void         SetFilePath     ();
    
	/**
	* @brief Get Date and Time
	*/
    static String       GetDateTime     ();

  private:

    static String       sFilePath;
    static String       sMasterFileName;
    static String       sFileName;
};

#endif // !LOG_HPP
