#pragma once

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT _WIN32_WINNT_VISTA

#include <windows.h>
#include <dbghelp.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <atltime.h>

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"dbghelp.lib")

typedef unsigned __int64 QWORD;

#else

#include <arpa/inet.h>
#include <cerrno>
#include <cstdint>
#include <ctime>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef uint64_t QWORD;
typedef int BOOL;
typedef long LONG;
typedef unsigned long ULONG;
typedef long long __int64;
typedef unsigned int UINT;
typedef unsigned short ATOM;
typedef unsigned long DWORD_PTR;
typedef unsigned long WPARAM;
typedef long LPARAM;
typedef long LRESULT;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef WINAPI
#define WINAPI
#endif

#ifndef CALLBACK
#define CALLBACK
#endif

typedef void* HANDLE;
typedef void* HINSTANCE;
typedef void* HMODULE;
typedef void* HWND;
typedef void* HICON;
typedef void* HCURSOR;
typedef void* HBRUSH;
typedef void* HMENU;
typedef void* LPVOID;
typedef const char* LPCSTR;
typedef char* LPSTR;
typedef const char* LPCTSTR;
typedef char* LPTSTR;
typedef const wchar_t* LPCWSTR;
typedef wchar_t* LPWSTR;
typedef char TCHAR;

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

typedef int SOCKET;

constexpr int INVALID_SOCKET = -1;
constexpr int SOCKET_ERROR = -1;

#ifndef WSAEWOULDBLOCK
#define WSAEWOULDBLOCK EWOULDBLOCK
#endif

inline int WSAGetLastError()
{
	return errno;
}

inline int closesocket(SOCKET socket)
{
	return close(socket);
}

inline int ioctlsocket(SOCKET socket, long command, u_long* argp)
{
	return ioctl(socket, command, argp);
}

inline void Sleep(DWORD milliseconds)
{
	usleep(static_cast<useconds_t>(milliseconds * 1000));
}

inline DWORD GetTickCount()
{
	timeval tv{};
	gettimeofday(&tv, nullptr);
	return static_cast<DWORD>((static_cast<uint64_t>(tv.tv_sec) * 1000ULL) + (tv.tv_usec / 1000ULL));
}

typedef pthread_mutex_t CRITICAL_SECTION;

inline void InitializeCriticalSection(CRITICAL_SECTION* critical)
{
	pthread_mutex_init(critical, nullptr);
}

inline void DeleteCriticalSection(CRITICAL_SECTION* critical)
{
	pthread_mutex_destroy(critical);
}

inline void EnterCriticalSection(CRITICAL_SECTION* critical)
{
	pthread_mutex_lock(critical);
}

inline void LeaveCriticalSection(CRITICAL_SECTION* critical)
{
	pthread_mutex_unlock(critical);
}

class CTimeSpan
{
public:
	CTimeSpan(int days, int hours, int minutes, int seconds)
		: m_totalSeconds(((((static_cast<int64_t>(days) * 24) + hours) * 60) + minutes) * 60 + seconds)
	{
	}

	int64_t GetTotalSeconds() const
	{
		return m_totalSeconds;
	}

private:
	int64_t m_totalSeconds;
};

class CTime
{
public:
	CTime()
		: m_time(std::time(nullptr))
	{
	}

	CTime(int year, int month, int day, int hour, int minute, int second, int)
	{
		std::tm tm_value{};
		tm_value.tm_year = year - 1900;
		tm_value.tm_mon = month - 1;
		tm_value.tm_mday = day;
		tm_value.tm_hour = hour;
		tm_value.tm_min = minute;
		tm_value.tm_sec = second;
		tm_value.tm_isdst = -1;
		m_time = std::mktime(&tm_value);
	}

	static CTime GetTickCount()
	{
		return CTime();
	}

	int GetYear() const
	{
		return getTm().tm_year + 1900;
	}

	int GetMonth() const
	{
		return getTm().tm_mon + 1;
	}

	int GetDay() const
	{
		return getTm().tm_mday;
	}

	int GetHour() const
	{
		return getTm().tm_hour;
	}

	int GetMinute() const
	{
		return getTm().tm_min;
	}

	int GetSecond() const
	{
		return getTm().tm_sec;
	}

	int GetDayOfWeek() const
	{
		return getTm().tm_wday;
	}

	bool operator<(const CTime& other) const
	{
		return m_time < other.m_time;
	}

	bool operator>(const CTime& other) const
	{
		return m_time > other.m_time;
	}

	CTime& operator+=(const CTimeSpan& span)
	{
		m_time += span.GetTotalSeconds();
		return *this;
	}

	friend CTime operator+(const CTime& time, const CTimeSpan& span)
	{
		CTime result = time;
		result += span;
		return result;
	}

private:
	std::tm getTm() const
	{
		std::tm tm_value{};
		localtime_r(&m_time, &tm_value);
		return tm_value;
	}

	std::time_t m_time;
};

#endif
