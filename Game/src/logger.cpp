#include "utils.h"
#include "logger.h"
#include <mutex>
#include <chrono>
#include <string>
#include <thread>
#include <chrono>

namespace Logging
{
    const char* myErrorValueNames[] =
    {
        stringify( DEBUG ),
        stringify( INFO ),
        stringify( WARNING ),
        stringify( ERROR ),
        stringify( FATAL )
    };

    // Set LOGGING level. Does not output above this level
    LogSeverity loglevel = FATAL;
    LogTarget LogDest = ALL;
    std::mutex myMutex;
    const std::string Logger::sFilename = "Log.txt";
    std::ofstream Logger::mLogfile;
    Logger* Logger::pThis = nullptr;

    Logger::Logger()
    {
        //ctor
    }

    //bool Logger::logging_activated = true;

    Logger* Logger::GetLog()
    {
        // Need to add a mutex here
        std::lock_guard<std::mutex> myLock(myMutex);
        if (pThis == nullptr)
        {
            pThis = new Logger();
            mLogfile.open(sFilename.c_str(), std::ios_base::out | std::ios_base::app);
        }
        // mutex is automatically released when lock goes out of scope
        return pThis;
    }

    Logger& Logger::operator<< (const std::string& logMsg)
    {
        if (LogDest == ALL)
        {
            std::cout << logMsg;
            mLogfile  << logMsg;
         }
        return *this;
    }

    void Logger::Log(const LogSeverity severity, const std::string& logMsg)
    {

        if (severity <= loglevel)
        {
            std::thread::id this_id = std::this_thread::get_id();

            mLogfile    << utils::CurrentDateTime() << " "
                        << __FILENAME__ << " [" << __LINE__ << "] "
                        << "[" << myErrorValueNames [severity]<< "] "
                        << "Thread [" << this_id << "] \t"
                       << logMsg << std::endl;

            std::cout   << utils::CurrentDateTime() << " "
                        << __FILENAME__ << " [" << __LINE__ << "] "
                        << "[" << myErrorValueNames [severity]<< "] "
                        << "Thread [" << this_id << "] \t"
                       << logMsg << std::endl;
        }

    }
/*
    void Logger::Log(const std::thread::id this_id, const LogSeverity severity, const std::string& logMsg)
    {
        if (severity <= loglevel)
        {
            mLogfile    << utils::CurrentDateTime() << " "
                        << __FILENAME__ << " [" << __LINE__ <<  "] "
                        << "[" << myErrorValueNames [severity] << "] "
                        << "Thread [" << this_id << "] \t"
                        << logMsg << std::endl;

            std::cout   << utils::CurrentDateTime() << " "
                        << __FILENAME__ << " [" << __LINE__ << "] "
                        << "[" << myErrorValueNames [severity]<< "] "
                        << "Thread [" << this_id << "] \t"
                       << logMsg << std::endl;

        }
    }
*/
   void Logger::Log(const LogSeverity severity, const char * format, ...)
    {
        char* sMessage = NULL;
        int nLength = 0;
        va_list args;
        va_start(args, format);
        //  Return the number of characters in the string referenced the list of arguments.
        // _vscprintf doesn't count terminating '\0' (that's why +1)
        nLength = _vscprintf(format, args) + 1;
        sMessage = new char[nLength];
        vsprintf_s(sMessage, nLength, format, args);
        //vsprintf(sMessage, format, args);
        std::cout << utils::CurrentDateTime() << " "
                 << __FILENAME__ << " [" << __LINE__ <<  "] "
                 << "[" << myErrorValueNames [severity]<< "] \t"
                 << sMessage << "\n";
        mLogfile << utils::CurrentDateTime() << " "
                 << __FILENAME__ << " [" << __LINE__ <<  "] : "
                 << "[" << myErrorValueNames [severity]<< "] \t"
                 << sMessage << "\n";
        va_end(args);

        delete [] sMessage;
    }
}// end namespace Logging
