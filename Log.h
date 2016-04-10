#ifndef LOG_H
#define LOG_H

#include <fstream>

class Log {
private:
    static Log* instance;
    static void initialize();
protected:
    static std::ofstream fout;
public:
    ~Log();
    static void i(std::string flag, std::string message);
    static Log& getInstance();
};

#endif // LOG_H

