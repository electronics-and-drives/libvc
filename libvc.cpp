#include "include/libvc.h"

/* Ctor for the library. The resultBuffer array is created
 * and the file descriptors are set. */
LibVC::LibVC(size_t bs, int wfd, int rfd): bufSize(bs), writefd(wfd), readfd(rfd)
{
    resultBuffer = new char[bufSize]; // initialize buffer array with given size (2084 by default)
}

/* File descriptors need to be 
 * dealocated after use */
int LibVC::closeConnection()
{
    delete[] resultBuffer;
    int w = close(writefd);
    int r = close(readfd);
    return (w + r);
}

/* This function prints the <skillCommand> to the 
 * specified file descriptor <writefd> for virtuoso
 * to interpret, and reads the response */
int LibVC::writeSkillRequest(const std::string &skillCommand)
{
    status = -1;
    response = ""; // clear the response string
    const char *cmd = skillCommand.c_str(); // convert to standard C
    status = write(writefd, &cmd[0], strlen(cmd)); // see write(3) - Linux man page
    if(status != -1) // if the write function does not fail
    {
        do 
        {   // clear the memory to provide a clean slate
            memset(resultBuffer, 0, sizeof(resultBuffer));
            status = read(readfd, &resultBuffer[0], bufSize); // see read(3) - Linux man page
            if(status != -1)
            {   
                resultBuffer[status] = '\0';                // add termination to make valid string
                response.append(std::string(resultBuffer)); // append the results to the response string
            }
        } // do this while there is still unread data
        while((status >= bufSize));
    }
    else // if the write function did fail
        {response = "WRITE ERROR";}
    return status;// if all went well return > -1
}

/* This function returns the response Virtuoso gave
 * to the last writeSkillCommand(1) call */
std::string LibVC::readSkillResponse()
{
    return response;
}

/* This function sets a new file descriptor
 * to which will be written in the writeSkillRequest() function */
void LibVC::setWritefd(int &wfd)
{
    if(wfd >= 0)
        {writefd = wfd;}
}

/* This function returns the current file descriptor
 * which is used for writing purposes. */
int LibVC::getWritefd()
{
    return writefd;
}

/* This function sets a new file descriptor
 * from which will be read. */
void LibVC::setReadfd(int &rfd)
{
    if(rfd >= 0)
        {readfd = rfd;}
}

/* This function returns the current file descriptor
 * from which responses are beeing read. */
int LibVC::getReadfd()
{
    return readfd;
}

/* This function changes the buffer size, which 
 * in turn can influence the performance */
void LibVC::setBufSize(std::size_t &bs)
{
    bufSize = bs; // set the private member
    delete[] resultBuffer; // delete the old buffer
    resultBuffer = new char[bufSize]; // create new buffer
}

/* Returns the current buffer size,
 * which is 2048 by default*/
std::size_t LibVC::getBufSize()
{
    return bufSize;
}
