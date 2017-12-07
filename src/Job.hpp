

#ifndef __JOB_HPP__
#define __JOB_HPP__

#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include "Downloader.hpp"

typedef struct _FileInfo{
    int fd;
    off_t offset;
    size_t size;
}FileInfo;

class Job
{
public:
    typedef enum _JobType{
        JT_sync,
        JT_exit,
        JT_http,
        JT_ftp,
    }JobType;

public:
    Job(uint32_t retryCount = 5):mRetryCount(retryCount)
    {
    }
    ~Job()
    {
    }

public:
    int WriteData(char *data)
    {
        size_t toWrite = mFileInfo.size;
        size_t writed = 0;
        ssize_t ret = 0;
        int err = 0;

        while (toWrite > 0) {
            ret = pwrite(mFileInfo.fd, data + writed, toWrite, mFileInfo.offset + writed);
            if (ret < 0) {
                err = errno;
                break;
            }

            toWrite -= ret;
            writed += ret;
        }

        return err;
    }

    int DoJob()
    {
        char *data = NULL;
        int err = 0;
        do {
            err = mDownloader->GetFileChunk(mFileInfo.offset, mFileInfo.size, &data);
            if (0 != err) {
                break;
            }
            assert(NULL != data);

            err = WriteData(data);
            if (0 != err) {
                break;
            }
        } while(0);

        if (NULL != data) {
            free(data);
        }

        return err;
    }

    void SetFileInfo(FileInfo info)
    {
        mFileInfo = info;
    }

    uint32_t GetMaxRetryCount()
    {
        return mRetryCount;
    }

private:
    uint32_t mRetryCount;
    Downloader *mDownloader;
    FileInfo mFileInfo;
};

#endif


