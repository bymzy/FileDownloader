

#ifndef __HTTP_DOWNLOADER_HPP__
#define __HTTP_DOWNLOADER_HPP__

#include <stdint.h>
#include <sstream>
#include <string>
#include "Log.hpp"
#include "Downloader.hpp"
#include "Error.hpp"
#include "Util.hpp"

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
    virtual int GetFileSize(uint64_t &fileSize, bool &supportRange)
    {
        CURLcode ecode;
        double cl = 0;
        int err = 0;
        std::string header;

        do {
            curl_easy_setopt(GetHandle(), CURLOPT_HEADER, 1);
            curl_easy_setopt(GetHandle(), CURLOPT_NOBODY, 1);
            curl_easy_setopt(GetHandle(), CURLOPT_WRITEFUNCTION, GetHeader);
            curl_easy_setopt(GetHandle(), CURLOPT_WRITEDATA, &header);
            curl_easy_setopt(GetHandle(), CURLOPT_FOLLOWLOCATION, 1L);

            ecode = curl_easy_perform(GetHandle());
            if (ecode == CURLE_OK) {
                ecode = curl_easy_getinfo(GetHandle(), CURLINFO_CONTENT_LENGTH_DOWNLOAD, &cl);
                if (CURLE_OK != ecode) {
                    err = E_CURL_GET_FILE_SIZE;
                    break;
                }
                fileSize = cl;
            } else {
                err = E_CURL_GET_FILE_SIZE;
                break;
            }

            if (0 != err) {
                ERROR_LOG("GetFileSize, failed, error: " << curl_easy_strerror(ecode)); 
            }

            /* check if server support range download */
            if (header.find("Accept-Ranges: bytes") != std::string::npos) {
                DEBUG_LOG("Range Download is supported on file server!!!");
                supportRange = true;
            }
        } while(0);

        return err;
    }

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

        return err;
    }
};

#endif


