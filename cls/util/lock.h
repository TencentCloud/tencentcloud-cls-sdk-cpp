#ifndef _LOCK_H
#define _LOCK_H

#include <string>
#include <stdexcept>
#include <cerrno>

using namespace std;
namespace tencent_log_sdk_cpp_v2
{
template <typename T>
class RW_RLockT
{
public:
    RW_RLockT(T& lock)
    : _rwLock(lock),_acquired(false)
    {
        _rwLock.ReadLock();
        _acquired = true;
    }
    ~RW_RLockT()
    {
        if (_acquired)
        {
            _rwLock.Unlock();
        }
    }
private:
    const T& _rwLock;
    mutable bool _acquired;
    RW_RLockT(const RW_RLockT&);
    RW_RLockT& operator=(const RW_RLockT&);
};

template <typename T>
class RW_WLockT
{
public:
    RW_WLockT(T& lock)
    : _rwLock(lock),_acquired(false)
    {
        _rwLock.WriteLock();
        _acquired = true;
    }
    ~RW_WLockT()
    {
        if(_acquired)
        {
            _rwLock.Unlock();
        }
    }
private:
    const T& _rwLock;
    mutable bool _acquired;
    RW_WLockT(const RW_WLockT&);
    RW_WLockT& operator=(const RW_WLockT&);
};
}// namespace tencent_log_sdk_cpp_v2
#endif

