

#ifndef __HTTP_DOWNLOADER_HPP__
#define __HTTP_DOWNLOADER_HPP__

#include <string>
#include "Downloader.hpp"

class HttpDownloader : public Downloader
{
public:
    HttpDownloader(std::string url):Downloader(url)
    {
    }
    ~HttpDownloader()
    {
    }
   
public:
    virtual int GetMetaData()
    {
    }
    virtual int GetFileChunk(off_t offset, size_t size, char **data) 
    {
    }
};

#endif


