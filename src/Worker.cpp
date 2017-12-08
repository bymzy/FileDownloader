

#include <stdint.h>
#include <vector>
#include "Worker.hpp"
#include "ControlCenter.hpp"

int Worker::Start()
{
    int err = 0;

    do {
        err = pthread_create(&mThreadId, NULL, Worker::ThreadFunc, this);
        if (0 != err) {
            break;
        }

    } while(0);

    return err;
}

void Worker::WaitStop()
{
    pthread_join(mThreadId, NULL);
}

void Worker::Run()
{
    std::vector<Job*> jobVec;
    Job *job = NULL;
    int err = 0;
    uint32_t retryCount = 0;

    while (IsSystemRunning() &&mJobs.size() > 0) {
        job = mJobs.front();
        mJobs.pop_front();

        err = job->DoJob();
        while (err != 0 && job->GetMaxRetryCount() > retryCount) {
            err = job->DoJob();
            ++retryCount;
        }
        mExitCode = err;
        delete job;
        job = NULL;
#if 0
        pthread_mutex_lock(&mMutex);
        while (mJobs.size() <=0 && IsSystemRunning()) {
            pthread_cond_wait(&mCond, &mMutex);
        }

        if (!IsSystemRunning()) {
            pthread_mutex_unlock(&mMutex);
            break;
        }

        jobVec.assign(mJobs.begin(), mJobs.end());
        mJobs.clear();
        pthread_mutex_unlock(&mMutex);

        for (size_t i=0; i < jobVec.size(); ++i) {
            job = jobVec[i];
            delete job;
            job = NULL;
        }

        jobVec.clear();
#endif
    }

    /*mJobs may be not empty, release it in ~Worker() */

    if (0 != mExitCode) {
        mCC->SetExitCode(mExitCode);
    }
}

bool Worker::IsSystemRunning()
{
    bool ret = true;
    if (0 != mExitCode) {
        ret = false;
    } else if (!mCC->IsSystemRunning()) {
        ret = false;
    }
    return ret;
}


