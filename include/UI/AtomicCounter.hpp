#ifndef UTIL_ATOMIC_COUNTER_H
#define UTIL_ATOMIC_COUNTER_H 1

#include <stdio.h>

#if __cplusplus >= 201103L
# define UTIL_HAVE_CXX_ATOMIC
# include <atomic>
#elif defined(__GNUC__)
# define UTIL_HAVE_GNUC_ATOMIC
#elif defined(_WIN32)
# define UTIL_HAVE_WIN32_ATOMIC
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
static bool isNewerThanWinXp() const
{
	OSVERSIONINFO vers = {0};
	vers.dwOsVersionInfoSize = sizeof(OSVERSIONINFO);
	if (!GetVersionEx(&vers))
		return true;
	if (vers.dwMajorVersion > 5 ||
		(vers.dwMajorVersion == 5 && vers.dwMajorVersion >= 2))
	{
		return true;
	}
	return false;
}
#endif

namespace util
{

template <class T>
class AtomicCounter
{

public:
	AtomicCounter(T startValue = 0) : cnt(startValue)
	{
	}

	T inc(T amount = 1)
	{
#if !defined(UTIL_HAVE_CXX_ATOMIC) && defined(UTIL_HAVE_GNUC_ATOMIC)
		T oldCount=0, newCount=0;
		do
		{
			oldCount = cnt;
			newCount = oldCount + amount;
			// TODO: check for overflow
		} while (!__sync_bool_compare_and_swap(&cnt, oldCount, newCount));
		return count();
#elif !defined(UTIL_HAVE_CXX_ATOMIC) && defined(UTIL_HAVE_WIN32_ATOMIC)
		if (isNewerThanWinXp())
			return (T) InterlockedIcrement64((LONGLONG)&cnt, (LONGLONG) (cnt + amount));
		else
			return (T) InterlockedIncrement((LONGLONG)&cnt, (LONGLONG) (cnt + amount));
#else
		return ++cnt;
#endif
	}

	T dec(T amount = 1)
	{
#if !defined(UTIL_HAVE_CXX_ATOMIC) && defined(UTIL_HAVE_GNUC_ATOMIC)
		T oldCount, newCount;
		do
		{
			oldCount = cnt;
			newCount = oldCount - amount;
			// TODO: check for underflow
		} while (!__sync_bool_compare_and_swap(&cnt, oldCount, newCount));
		return newCount;
#elif !defined(UTIL_HAVE_CXX_ATOMIC) && UTIL_HAVE_WIN32_ATOMIC
		// TODO: is this evil?
		if (isNewerThanWinXp())
			return (T) InterlockedIcrement64((LONGLONG)&cnt, (LONGLONG) (cnt - amount));
		else
			return (T) InterlockedIncrement((LONGLONG)&cnt, (LONGLONG) (cnt - amount));
#else
		return --cnt;
#endif
	}

	T count() const { return this->cnt; }

private:
#ifdef UTIL_HAVE_CXX_ATOMIC
	std::atomic<T> cnt;
#else
	T cnt;
#endif

};

} // namespace util

#endif // UTIL_ATOMIC_COUNTER_H
