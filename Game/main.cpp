#include "utils.h"
#include "logger.h"
#include <string>
#include <thread>
#include <chrono>

using namespace Logging;
using namespace utils;

extern const std::string CurrentDateTime();

void safe_function(const std::string msg, int s)
{
    std::this_thread::sleep_for(std::chrono::seconds(s));

    LOG->Log(INFO, msg);
}

int main()
{
    std::cout << "Log testing\n";

    std::string msg1 = "log message 1 ...";
    std::string msg2 = "log message 2 ...";
    std::string msg3 = "log message 3 ...";
    std::string msg4 = "log message 4 ...";
    std::string msg5 = "log message 5 ...";

    //enable logging
    //Logger::logging_activated = true;

    // Set default level. Does not output above this level
    //extern LogSeverity loglevel;

    int num{0};
    LOG->Log(INFO, msg1);
    LOG->Log(DEBUG, msg2);
    LOG->Log(FATAL, msg3);
    *LOG << utils::CurrentDateTime() << " " << "[WARNING]" << "\t" << msg4 << "\n";

    LOG->Log(INFO,"Beware the ides of March. %s %s %d",  AT, msg5.c_str(), num);

    std::thread t1(safe_function,"Hallo", 1);
    std::thread t2(safe_function,"Goodbye", 2);

    t1.join();
    t2.join();

    return 0;
}

