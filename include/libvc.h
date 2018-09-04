#ifndef LIBVC
#define LIBVC

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

class LibVC
{
private:
    int writefd;
    int readfd;
    int status;
    std::size_t bufSize;
    char *resultBuffer;
    std::string response;

public:
    LibVC(size_t bs = 2048, int wfd = 3, int rfd = 4);
protected:
    int writeSkillRequest(const std::string &skillCommand);
    std::string readSkillResponse();
    void setWritefd(int &wfd);
    int getWritefd();
    void setReadfd(int &rfd);
    int getReadfd();
    void setBufSize(std::size_t &bs);
    std::size_t getBufSize();
    int closeConnection();
};

#endif // LIBVC
