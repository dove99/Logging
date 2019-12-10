#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>
#include <cstdarg>
#include <string.h>
#include <thread>

#include "utils.h"

#define LOG Logging::Logger::GetLog()

// Remove the fullpath just the filename
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define stringify( name ) # name
#define TOSTRING(x) stringify(x)
#define AT (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__ ":" TOSTRING(__LINE__))

namespace Logging
{
    enum LogSeverity
    {
        DEBUG=0, INFO, WARNING, ERROR, FATAL  // ...
    };

    enum LogTarget
    {
        OFF=0, ALL, TOFILE, TOCONSOLE
    };

    // singleton logger class
    class Logger
    {
    public:

        // enables logging
        //static bool logging_activated;

        void Log(const LogSeverity, const std::string&);
        void Log(const std::thread::id, const LogSeverity, const std::string&);
        void Log(const LogSeverity, const char * format, ...);

        Logger& operator << (const std::string&);
        static Logger* GetLog();

    private:

        Logger();
        Logger(const Logger& other){};
        Logger& operator=(const Logger&) {return *this;};

        static Logger* pThis;
        static const std::string sFilename;
        static std::ofstream mLogfile;
    };
}// end namespace Logging

#endif // LOGGER_H
