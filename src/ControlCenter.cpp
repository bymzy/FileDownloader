

#include <errno.h>
#include "HttpDownloader.hpp"
#include "FtpDownloader.hpp"
#include "ControlCenter.hpp"
#include "Worker.hpp"

int ControlCenter::Init(std::string url, std::string protoType)
{
    int err = 0;
    std::string fileName;

    do {
        mProtoType = protoType;
        mURL = url;

        /* new specific downloader according to proto type */
        if (mProtoType == "HTTP") {
            mDownloader = new HttpDownloader(mURL);
        } else if (mProtoType == "FTP") {
            mDownloader = new HttpDownloader(mURL);
        } else {
            err = EINVAL;
        }

        /* get file size */
        err = mDownloader->GetMetaData();
        if (0 != err) {
            break;
        }

        /* open file TODO */

    } while(0);

    return err;
}

uint32_t ControlCenter::GetWorkerCount()
{
    /* TODO get cpu count and determine it */
    uint64_t fileSize = mDownloader->GetFileSize();
    uint32_t count = 0;

    count = fileSize / ControlCenter::ChunkSize / MaxJobCountPerWorker;
    count += 1;

    return count;
}

int ControlCenter::CreateWorkers()
{
    int err = 0;
    uint32_t workerCount = GetWorkerCount();
    Worker *wk = NULL;
    off_t offset = 0;
    Job *job = NULL;
    std::deque<Job*> jobQ;
    FileInfo info;

    info.fd = mFD;
    for (uint32_t i = 0; i < workerCount; ++i) {
        jobQ.clear();
        wk = new Worker(this);
        mWorkers.push_back(wk);
        
        for (uint32_t j = 0; j < MaxJobCountPerWorker; ++j) {
            offset = i * ControlCenter::MaxJobCountPerWorker * ControlCenter::ChunkSize
                + j * ControlCenter::ChunkSize;
            info.offset = offset;
            info.size = ControlCenter::ChunkSize;

            job = new Job();
            job->SetFileInfo(info);
            jobQ.push_back(job);
        }
        wk->SetJobs(jobQ);
        err = wk->Start();
        if (0 != err) {
            break;
        }
    }

    return err;
}

void ControlCenter::WaitStop()
{
    for(uint32_t i = 0; i < mWorkers.size(); ++i) {
        mWorkers[i]->WaitStop();
        delete mWorkers[i];
    }
    mWorkers.clear();
}

int ControlCenter::StartWork()
{
    int err = 0;

    do {
        err = CreateWorkers();
        if (0 != err) {
            break;
        }

        WaitStop();

        err = GetExitCode();
        if (0 != err) {
            break;
        }
    } while(0);

    return err;
}


