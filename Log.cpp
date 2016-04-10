#include "Log.h"
#include <fstream>
#include <ctime>

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
    fout.open("log.dat", ios::out | ios::app);
    if (!fout) {
        //TODO: can't open the file error
    }
}

void Log::i(string flag, string message) {
    if (fout) {
        // Getting current 'timestamp' for logging. time(0) means 'now'
        tm *ltm = localtime(time(0));

        string timestamp = tm->tm_mday + "." + tm->tm_mon + "." + tm->tm_year + " " + tm->tm_hour + ":" + tm->tm_min + ":" + tm->tm_sec;

        fout << timestamp + " " + flag + " " message + '\n';
    } else {
        //TODO: can't open the file error
    }
}
