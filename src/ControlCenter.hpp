

#ifndef __CONTROL_CENTER_HPP__
#define __CONTROL_CENTER_HPP__

#include <string>
#include <vector>
#include <stdint.h>
#include "Downloader.hpp"
#include "Worker.hpp"

class ControlCenter
{
public:
    enum Config{
        ChunkSize = 64 << 10,
        MaxJobCountPerWorker = 200,
    };

public:
    ControlCenter()
    {
        pthread_mutex_init(&mMutex, NULL);
        mFD = -1;
        mExitCode = 0;
    }
    ~ControlCenter()
    {
        if (mDownloader != NULL) {
            delete mDownloader;
            mDownloader = NULL;
        }
        
        for(uint32_t i = 0; i < mWorkers.size(); ++i) {
            mWorkers[i]->WaitStop();
            delete mWorkers[i];
        }
        mWorkers.clear();

        for (uint32_t i = 0; i < mDownLoaders.size(); ++i) {
            delete mDownLoaders[i];
        }
        mDownLoaders.clear();

        if (mFD != -1) {
            close(mFD);
            mFD = -1;
        }
        pthread_mutex_destroy(&mMutex);
    }

public:
    static ControlCenter* Instance()
    {
        static ControlCenter *cc = new ControlCenter();
        return cc;
    }

    int Init(std::string url, std::string protoType, std::string fileName);

    int StartWork();

    int GetFileSize();

    inline int GetExitCode()
    {
        int exitCode = 0;
        pthread_mutex_lock(&mMutex);
        exitCode = mExitCode;
        pthread_mutex_unlock(&mMutex);

        return exitCode;
    }

    inline void SetExitCode(int exitCode)
    {
        pthread_mutex_lock(&mMutex);
        mExitCode = exitCode;
        pthread_mutex_unlock(&mMutex);
    }

    inline bool IsSystemRunning()
    {
        bool ret = true;
        pthread_mutex_lock(&mMutex);
        if (0 != mExitCode) {
            ret = false;
        }
        pthread_mutex_unlock(&mMutex);

        return ret;
    }

private:
    int CreateWorkers();
    void WaitStop();
    uint32_t GetWorkerCount();
    Downloader *NewDownloader();

private:
    std::string mURL;
    std::string mProtoType;
    int mFD;
    size_t mFileSize;
    std::string mFileName;

    Downloader *mDownloader;
    int mExitCode;
    pthread_mutex_t mMutex;
    std::vector<Worker*> mWorkers;
    std::vector<Downloader*> mDownLoaders;
};

#endif


