#ifndef LOG_H
#define LOG_H

#include <fstream>

class Log {
private:
    Log* instance;
    void initialize();
protected:
    ofstream fout;
public:
    ~Log();
    static void i(string flag, string message);
    static Log& getInstance();
};

#endif // LOG_H

