#ifndef __THREAD_RWLOCK_H
#define __THREAD_RWLOCK_H

#include <pthread.h>
#include "lock.h"

#if !defined(linux) && (defined(__linux) || defined(__linux__))
#define linux
#endif

using namespace std;
#if !defined(linux) || (defined __USE_UNIX98 || defined __USE_XOPEN2K)
namespace tencent_log_sdk_cpp_v2
{
class ThreadRWLocker
{
public:
    ThreadRWLocker();
    ~ThreadRWLocker();
    void ReadLock() const;
    void WriteLock() const;
    void TryReadLock() const;
    void TryWriteLock() const ;
    void Unlock() const;

private:
    mutable pthread_rwlock_t m_sect;
    ThreadRWLocker(const ThreadRWLocker&);
    ThreadRWLocker& operator=(const ThreadRWLocker&);
};

typedef RW_RLockT<ThreadRWLocker> ThreadRLock;
typedef RW_WLockT<ThreadRWLocker> ThreadWLock;
} // namespace tencent_log_sdk_cpp_v2
#endif
#endif


