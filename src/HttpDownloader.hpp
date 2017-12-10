

#ifndef __HTTP_DOWNLOADER_HPP__
#define __HTTP_DOWNLOADER_HPP__

#include <sstream>
#include <string>
#include "Log.hpp"
#include "Downloader.hpp"
#include "Error.hpp"

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
    virtual int GetFileChunk(FileInfo *fileInfo) 
    {
        int err = 0;
        std::stringstream ss;
        ss << fileInfo->offset << "-" << (fileInfo->offset + fileInfo->size - 1) << std::endl;
        std::string rangeString;
        ss >> rangeString;
        long response_code = 0;

        CURLcode res;
        curl_easy_setopt(GetHandle(), CURLOPT_WRITEFUNCTION, Downloader::WriteData);
        curl_easy_setopt(GetHandle(), CURLOPT_WRITEDATA, (void*)fileInfo);
        curl_easy_setopt(GetHandle(), CURLOPT_RANGE, rangeString.c_str());
        curl_easy_setopt(GetHandle(), CURLOPT_NOSIGNAL, 1L);
        curl_easy_setopt(GetHandle(), CURLOPT_TIMEOUT, 10L);
        curl_easy_setopt(GetHandle(), CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(GetHandle(), CURLOPT_CUSTOMREQUEST, "GET");

        res = curl_easy_perform(GetHandle());
        if (CURLE_OK != res) {
            err = E_CURL_DOWNLOAD_FAILED;
            ERROR_LOG("curl_easy_perform failed, errstr: " << curl_easy_strerror(res));
        } else {
            err = (fileInfo->mErr == 0 ? err : fileInfo->mErr);
        }

        //DEBUG_LOG("GetFileChunk done, range: " << rangeString << ", error: " << err);
        return err;
    }
};

#endif


