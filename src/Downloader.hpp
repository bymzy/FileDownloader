

#ifndef __DOWNLOADER_HPP__
#define __DOWNLOADER_HPP__
#include <unistd.h>

class Downloader
{
public:
    Downloader(std::string url):mURL(url)
    {
    }
    ~Downloader()
    {
    }
public:
    virtual int GetMetaData() = 0;
    virtual int GetFileChunk(off_t offset, size_t size, char **data) = 0;

public:
    inline size_t GetFileSize()
    {
        return mFileSize;
    }

private:
    std::string mURL;
    size_t mFileSize;
};

#endif


