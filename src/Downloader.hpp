

#ifndef __DOWNLOADER_HPP__
#define __DOWNLOADER_HPP__
#include <unistd.h>
#include <curl/curl.h>
#include <errno.h>
#include <string>

#include "Log.hpp"
#include "Error.hpp"
#include "string.h"

typedef struct _FileInfo{
    int fd;
    off_t offset;
    size_t size;
    int mErr;
}FileInfo;

class Downloader
{
public:
    Downloader(std::string url):mURL(url)
    {
        mCURL = NULL;
    }
    ~Downloader()
    {
        if (mCURL != NULL) {
            curl_easy_cleanup(mCURL);
            mCURL = NULL;
        }
    }
public:
    static size_t WriteData(char *ptr, size_t blockCount, size_t memBlockSize, void *arg)
    {
        FileInfo *info = (FileInfo*)arg;

        size_t toWrite = blockCount * memBlockSize;
        size_t writed = 0;
        ssize_t ret = 0;
        off_t offset = info->offset;

        while (toWrite >0) {
            ret = pwrite(info->fd, ptr + writed, toWrite, offset);
            if (ret < 0) {
                info->mErr = errno;
                ERROR_LOG("pwrite failed, error: " << errno
                        << ", errstr: " << strerror(errno));
                break;
            }

            toWrite -= ret;
            writed += ret;
            offset += ret;
        }

        info->offset = offset;

        return blockCount * memBlockSize;
    }

    /* Get whole file */
    virtual int GetWholeFile(FileInfo* fileInfo) = 0;

    /* Get chunk of file */
    virtual int GetFileChunk(FileInfo* fileInfo) = 0;

    /* Get file total size */
    virtual int GetFileSize(uint64_t &fileSize, bool &supportRange) = 0;

public:
    CURL *GetHandle()
    {
        return mCURL;
    }

    virtual int Init()
    {
        mCURL = curl_easy_init();
        if (mCURL == NULL) {
            return E_CURL_EASY_INIT;
        }

        curl_easy_setopt(mCURL, CURLOPT_URL, mURL.c_str());
        return 0;
    }
    
private:
    std::string mURL;
    size_t mFileSize;
    CURL *mCURL;
};

#endif


