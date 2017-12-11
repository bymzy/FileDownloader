

#ifndef __JOB_HPP__
#define __JOB_HPP__

#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include "Downloader.hpp"

class Job
{
public:
    Job(Downloader *dl, uint32_t retryCount = 5): mDownloader(dl), mRetryCount(retryCount)
    {
    }
    ~Job()
    {
    }

public:
    int DoJob()
    {
        int err = 0;
        err = mDownloader->GetFileChunk(&mFileInfo);

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


