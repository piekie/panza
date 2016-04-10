#include "Log.h"

#include <fstream>
#include <ctime>
#include <sstream>

std::ofstream Log::fout;
Log* Log::instance;

Log::~Log() {
    fout.close();
    delete instance;
}

Log& Log::getInstance() {
    if(!instance)     {
        instance = new Log();

        initialize();
    }
    return *instance;
}

void Log::initialize() {
    fout.open("log.dat", std::ios::out | std::ios::app);
    if (!fout) {
        //TODO: can't open the file error
    }
}

void Log::i(std::string flag, std::string message) {
    if (fout) {
        // Getting current 'timestamp' for logging
        time_t now = time(0);
        struct tm *tm = localtime(&now);

        std::stringstream ss;
        ss << tm->tm_mday << ".";
        ss << tm->tm_mon + 1 << ".";
        ss << tm->tm_year + 1900 << " ";
        ss << tm->tm_hour << ":";
        ss << tm->tm_min << ":";
        ss << tm->tm_sec;

        std::string timestamp = ss.str();

        fout << timestamp + " " + flag + " | " + message + '\n';
    } else {
        //TODO: can't open the file error
    }
}
