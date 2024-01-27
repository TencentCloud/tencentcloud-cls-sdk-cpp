#include "thread_rwlock.h"
#include <iostream>
#include <cassert>

namespace tencent_log_sdk_cpp_v2
{
ThreadRWLocker::ThreadRWLocker()
{
    int ret = ::pthread_rwlock_init(&m_sect, NULL);
    assert(ret == 0);

    if(ret != 0)
    {
        cerr<<"[TC_ThreadRWLocker::TC_ThreadRWLocker] pthread_rwlock_init error:"<<ret<<endl;;
    }
}

ThreadRWLocker::~ThreadRWLocker()
{
    int ret = ::pthread_rwlock_destroy(&m_sect);
    if(ret != 0)
    {
        cerr<<"[TC_ThreadRWLocker::~TC_ThreadRWLocker] pthread_rwlock_destroy error:"<<ret<<endl;;
    }

}

void ThreadRWLocker::ReadLock() const
{
    int ret = ::pthread_rwlock_rdlock(&m_sect);
    if(ret != 0)
    {
        if(ret == EDEADLK)
        {
            cerr<<"[TC_ThreadRWLocker::ReadLock] pthread_rwlock_rdlock dead lock error:"<<ret<<endl;
        }
        else
        {
            cerr<<"[TC_ThreadRWLocker::ReadLock] pthread_rwlock_rdlock error:"<<ret<<endl;
        }
    }
}

void ThreadRWLocker::WriteLock() const
{
    int ret = ::pthread_rwlock_wrlock(&m_sect);
    if(ret != 0)
    {
        if(ret == EDEADLK)
        {
            cerr<<"[TC_ThreadRWLocker::WriteLock] pthread_rwlock_wrlock dead lock error:"<<ret<<endl;
        }
        else
        {
            cerr<<"[TC_ThreadRWLocker::WriteLock] pthread_rwlock_wrlock error:"<<ret<<endl;
        }
    }

}

void ThreadRWLocker::TryReadLock() const
{
    int ret = ::pthread_rwlock_tryrdlock(&m_sect);
    if(ret != 0)
    {
        if(ret == EDEADLK)
        {
            cerr<<"[TC_ThreadRWLocker::TryReadLock] pthread_rwlock_tryrdlock dead lock error:"<<ret<<endl;
        }
        else
        {
            cerr<<"[TC_ThreadRWLocker::TryReadLock] pthread_rwlock_tryrdlock error:"<<ret<<endl;
        }
    }

}

void ThreadRWLocker::TryWriteLock() const
{
    int ret = ::pthread_rwlock_trywrlock(&m_sect);
    if(ret != 0)
    {
        if(ret == EDEADLK)
        {
            cerr<<"[TC_ThreadRWLocker::TryWriteLock] pthread_rwlock_trywrlock dead lock error:"<<ret<<endl;
        }
        else
        {
            cerr<<"[TC_ThreadRWLocker::TryWriteLock] pthread_rwlock_trywrlock error:"<<ret<<endl;
        }
    }

}

void ThreadRWLocker::Unlock() const
{
    int ret = ::pthread_rwlock_unlock(&m_sect);
    if(ret != 0)
    {
        cerr<<"[TC_ThreadRWLocker::Unlock] pthread_rwlock_unlock error:"<<ret<<endl;
    }
}
}// namespace tencent_log_sdk_cpp_v2
