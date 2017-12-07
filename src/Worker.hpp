

#ifndef __WORKER_HPP__
#define __WORKER_HPP__


#include <pthread.h>
#include <deque>
#include "Job.hpp"

class ControlCenter;

class Worker
{
public:
    Worker(ControlCenter *cc):mCC(cc)
    {
        mExitCode = 0;
        pthread_mutex_init(&mMutex, NULL);
        pthread_cond_init(&mCond, NULL);
    }
    ~Worker()
    {
        pthread_mutex_destroy(&mMutex);
        pthread_cond_destroy(&mCond);

        if (mJobs.size() > 0) {
            for (size_t i=0; i < mJobs.size(); ++i) {
                delete mJobs[i];
            }
            mJobs.clear();
        }
    }

public:
    static void *ThreadFunc(void *arg)
    {
        Worker *wk = (Worker*)arg;
        wk->Run();
    }

public:
    int Start();
    void WaitStop();
    void Run();
    bool IsSystemRunning();

    void SetJobs(std::deque<Job*>& jobQ)
    {
        mJobs.swap(jobQ);
    }

    inline int GetExitCode()
    {
        return mExitCode;
    }

private:
    pthread_t mThreadId;
    std::deque<Job*> mJobs;
    pthread_mutex_t mMutex;
    pthread_cond_t mCond;
    int mExitCode;
    ControlCenter *mCC;
};

#endif


