

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

    virtual int GetFileChunk(FileInfo *fileInfo) 
    {
        int err = 0;
        CURLcode res;
        curl_easy_setopt(GetHandle(), CURLOPT_WRITEFUNCTION, Downloader::WriteData);
        curl_easy_setopt(GetHandle(), CURLOPT_WRITEDATA, (void*)fileInfo);

        res = curl_easy_perform(GetHandle());

        if (CURLE_OK != res) {
            err = 1;
        }

        err = fileInfo->mErr == 0 ? err : fileInfo->mErr;

        return err;
    }
};

#endif


