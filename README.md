# Virtuoso Communication Library

This library acts as the C++ counterpart to ```ipcSkillProcess```.

## Dependencies

Building requries at least:
+ GCC version 4.8.5
+ GNU Make 3.82

## Getting Started

### Building

Run the included _Makefile_

```bash
$ make
```

### Example

To use the library link against ```libvc.so``` and don't forget to include
```libvc.h```. If your compiler doesn't find the library make sure it is
added to the LD\_LIBRARY\_PATH environment variable.

To use the functions defined in this library a class must be derived from
```LibVC```. For example:

```c++
class VirtuosoInterface: public LibVC
{
    explicit VirtuosoInterface(size_t bs, int wfd, int rfd): LibVC(bs, wfd, rfd)
    {
        //...
    }
}
```
An Object of this class is now capable of communicating with Virtuoso if it
is launched as a child process with ```ipcSkillProcess```.

## Function Reference

### writeSkillRequest
```int writeSkillRequest(const std::string &skillCommand)```

This function writes the given string _skillCommand_ to the file descriptor
_wfd_ defined in the ctor. On success this function returns the amount of bytes
written, otherwise -1 is returned. The response given by Virtuoso to the _skillCommand_
is buffered and available for reading with ```readSkillResponse```. If it is not
read before executing another ```writeSkillRequest``` the response will be overriten.

### readSkillResponse
```std::string readSkillResponse()```

This function returns the response to the last ```writeSkillRequest``` call.

### setWritefd
```void setWritefd(int &wfd)```

With this function the file descriptor to which ```writeSkillRequest``` writes 
can be manually changed. This is necessary if the _x\_cmdDesc_ in the initial
```ipcSkillProcess``` call is set to something different.

### getWritefd
```int getWritefd()```

Returns the current file descriptor to which SKILL commands are written.

### setReadfd
```void setReadfd(int &rfd)```

This function changes the current file descriptor from which the SKILL response
is read and buffered. This is necessary if the _x\_resDesc_ in the initial
```ipcSkillProcess``` call is set to something different.

### getReadfd
```int getReadfd()```

Returns the current file descriptor from which the SKILL response is read.

### setBufSize
```void setBufSize(std::size_t &bs)```

With this function the size of the buffer for SKILL responses can be adjusted.

### getBufSize
```std::size_t getBufSize()```

Returns the current size of the buffer holding the SKILL response.

### closeConnection
```int closeConnection()```

Closes the connection to the SKILL parent process.
