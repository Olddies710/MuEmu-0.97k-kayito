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
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <poll.h>
#include <semaphore.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/stat.h>
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
typedef uintptr_t ULONG_PTR;
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

struct WinHandle
{
	enum class Type
	{
		File,
		Thread,
		Semaphore,
		Event,
		Unknown
	};

	Type type = Type::Unknown;
	void* handle = nullptr;
	int socket = -1;
	long eventMask = 0;
	long lastEvents = 0;
};

using HANDLE = WinHandle*;
typedef void* HINSTANCE;
typedef void* HMODULE;
typedef void* HWND;
typedef void* HICON;
typedef void* HCURSOR;
typedef void* HBRUSH;
typedef void* HMENU;
typedef void* HFONT;
typedef void* LPVOID;
typedef const char* LPCSTR;
typedef char* LPSTR;
typedef const char* LPCTSTR;
typedef char* LPTSTR;
typedef const wchar_t* LPCWSTR;
typedef wchar_t* LPWSTR;
typedef char TCHAR;

#ifndef FAR
#define FAR
#endif

typedef void* LPQOS;
typedef unsigned long GROUP;

typedef struct _WSAOVERLAPPED
{
	ULONG_PTR Internal;
	ULONG_PTR InternalHigh;
	DWORD Offset;
	DWORD OffsetHigh;
	HANDLE hEvent;
} WSAOVERLAPPED, * LPWSAOVERLAPPED;

typedef struct _WSABUF
{
	ULONG len;
	char* buf;
} WSABUF, * LPWSABUF;

typedef struct tagRECT
{
	LONG left;
	LONG top;
	LONG right;
	LONG bottom;
} RECT;

inline void SetRect(RECT* rect, LONG left, LONG top, LONG right, LONG bottom)
{
	if (!rect)
	{
		return;
	}

	rect->left = left;
	rect->top = top;
	rect->right = right;
	rect->bottom = bottom;
}

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

typedef int SOCKET;

constexpr int INVALID_SOCKET = -1;
constexpr int SOCKET_ERROR = -1;

#define MAKEWORD(a, b) static_cast<WORD>(((a) & 0xff) | (((b) & 0xff) << 8))

#ifndef INFINITE
#define INFINITE 0xFFFFFFFF
#endif

#ifndef WAIT_OBJECT_0
#define WAIT_OBJECT_0 0x00000000L
#endif

#ifndef WAIT_FAILED
#define WAIT_FAILED 0xFFFFFFFF
#endif

#ifndef WAIT_TIMEOUT
#define WAIT_TIMEOUT 0x00000102L
#endif

#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE nullptr
#endif

#ifndef INVALID_SET_FILE_POINTER
#define INVALID_SET_FILE_POINTER 0xFFFFFFFF
#endif

#ifndef GENERIC_READ
#define GENERIC_READ 0x80000000
#endif

#ifndef GENERIC_WRITE
#define GENERIC_WRITE 0x40000000
#endif

#ifndef FILE_SHARE_READ
#define FILE_SHARE_READ 0x00000001
#endif

#ifndef FILE_SHARE_WRITE
#define FILE_SHARE_WRITE 0x00000002
#endif

#ifndef OPEN_EXISTING
#define OPEN_EXISTING 3
#endif

#ifndef OPEN_ALWAYS
#define OPEN_ALWAYS 4
#endif

#ifndef CREATE_ALWAYS
#define CREATE_ALWAYS 2
#endif

#ifndef FILE_ATTRIBUTE_NORMAL
#define FILE_ATTRIBUTE_NORMAL 0x00000080
#endif

#ifndef FILE_ATTRIBUTE_ARCHIVE
#define FILE_ATTRIBUTE_ARCHIVE 0x00000020
#endif

#ifndef FILE_BEGIN
#define FILE_BEGIN SEEK_SET
#endif

#ifndef FILE_CURRENT
#define FILE_CURRENT SEEK_CUR
#endif

#ifndef FILE_END
#define FILE_END SEEK_END
#endif

#ifndef GPTR
#define GPTR 0x0040
#endif

#ifndef FD_READ
#define FD_READ 0x00000001
#endif

#ifndef FD_WRITE
#define FD_WRITE 0x00000002
#endif

#ifndef FD_CLOSE
#define FD_CLOSE 0x00000020
#endif

#ifndef WSA_WAIT_FAILED
#define WSA_WAIT_FAILED WAIT_FAILED
#endif

#ifndef WSA_WAIT_TIMEOUT
#define WSA_WAIT_TIMEOUT WAIT_TIMEOUT
#endif

#ifndef WSA_WAIT_EVENT_0
#define WSA_WAIT_EVENT_0 WAIT_OBJECT_0
#endif

#ifndef WSA_INFINITE
#define WSA_INFINITE INFINITE
#endif

#ifndef WSA_INVALID_EVENT
#define WSA_INVALID_EVENT nullptr
#endif

typedef struct _SYSTEMTIME
{
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
} SYSTEMTIME;

inline void GetLocalTime(SYSTEMTIME* time)
{
	if (!time)
	{
		return;
	}

	struct timeval tv {};
	gettimeofday(&tv, nullptr);

	std::tm tm_value{};
	localtime_r(&tv.tv_sec, &tm_value);

	time->wYear = static_cast<WORD>(tm_value.tm_year + 1900);
	time->wMonth = static_cast<WORD>(tm_value.tm_mon + 1);
	time->wDay = static_cast<WORD>(tm_value.tm_mday);
	time->wDayOfWeek = static_cast<WORD>(tm_value.tm_wday);
	time->wHour = static_cast<WORD>(tm_value.tm_hour);
	time->wMinute = static_cast<WORD>(tm_value.tm_min);
	time->wSecond = static_cast<WORD>(tm_value.tm_sec);
	time->wMilliseconds = static_cast<WORD>(tv.tv_usec / 1000);
}

inline int wsprintf(char* buffer, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	int result = vsprintf(buffer, format, args);
	va_end(args);
	return result;
}

inline int strcpy_s(char* destination, const char* source)
{
	if (!destination || !source)
	{
		return -1;
	}

	std::strcpy(destination, source);
	return 0;
}

inline int strcpy_s(char* destination, size_t destinationSize, const char* source)
{
	if (!destination || !source)
	{
		return -1;
	}

	std::strncpy(destination, source, destinationSize);
	if (destinationSize > 0)
	{
		destination[destinationSize - 1] = '\0';
	}
	return 0;
}

inline int sprintf_s(char* buffer, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	int result = vsprintf(buffer, format, args);
	va_end(args);
	return result;
}

inline int sprintf_s(char* buffer, size_t, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	int result = vsprintf(buffer, format, args);
	va_end(args);
	return result;
}

inline int vsprintf_s(char* buffer, const char* format, va_list args)
{
	return vsprintf(buffer, format, args);
}

inline BOOL CreateDirectory(const char* path, void*)
{
	if (!path)
	{
		return FALSE;
	}

	if (mkdir(path, 0755) == 0 || errno == EEXIST)
	{
		return TRUE;
	}

	return FALSE;
}

inline void* GlobalAlloc(UINT flags, size_t bytes)
{
	if (flags & GPTR)
	{
		return std::calloc(1, bytes);
	}

	return std::malloc(bytes);
}

inline void GlobalFree(void* memory)
{
	std::free(memory);
}

inline HANDLE CreateFile(const char* filename, DWORD desiredAccess, DWORD, void*, DWORD creationDisposition, DWORD, void*)
{
	if (!filename)
	{
		return INVALID_HANDLE_VALUE;
	}

	bool wantRead = (desiredAccess & GENERIC_READ) != 0;
	bool wantWrite = (desiredAccess & GENERIC_WRITE) != 0;
	const char* mode = "rb";

	if (wantWrite)
	{
		if (creationDisposition == CREATE_ALWAYS)
		{
			mode = wantRead ? "w+b" : "wb";
		}
		else if (creationDisposition == OPEN_ALWAYS)
		{
			mode = wantRead ? "a+b" : "ab";
		}
		else
		{
			mode = wantRead ? "r+b" : "ab";
		}
	}

	FILE* file = std::fopen(filename, mode);
	if (!file)
	{
		return INVALID_HANDLE_VALUE;
	}

	auto* handle = new WinHandle();
	handle->type = WinHandle::Type::File;
	handle->handle = file;
	return handle;
}

inline BOOL ReadFile(HANDLE handle, void* buffer, DWORD bytesToRead, DWORD* bytesRead, void*)
{
	if (!handle || handle->type != WinHandle::Type::File || !buffer)
	{
		return FALSE;
	}

	auto* file = static_cast<FILE*>(handle->handle);
	size_t count = std::fread(buffer, 1, bytesToRead, file);
	if (bytesRead)
	{
		*bytesRead = static_cast<DWORD>(count);
	}
	return TRUE;
}

inline BOOL WriteFile(HANDLE handle, const void* buffer, DWORD bytesToWrite, DWORD* bytesWritten, void*)
{
	if (!handle || handle->type != WinHandle::Type::File || !buffer)
	{
		return FALSE;
	}

	auto* file = static_cast<FILE*>(handle->handle);
	size_t count = std::fwrite(buffer, 1, bytesToWrite, file);
	if (bytesWritten)
	{
		*bytesWritten = static_cast<DWORD>(count);
	}
	return count == bytesToWrite;
}

inline DWORD SetFilePointer(HANDLE handle, LONG distance, LONG*, DWORD moveMethod)
{
	if (!handle || handle->type != WinHandle::Type::File)
	{
		return INVALID_SET_FILE_POINTER;
	}

	auto* file = static_cast<FILE*>(handle->handle);
	if (std::fseek(file, distance, static_cast<int>(moveMethod)) != 0)
	{
		return INVALID_SET_FILE_POINTER;
	}

	long pos = std::ftell(file);
	return (pos < 0) ? INVALID_SET_FILE_POINTER : static_cast<DWORD>(pos);
}

inline BOOL CloseHandle(HANDLE handle)
{
	if (!handle)
	{
		return FALSE;
	}

	switch (handle->type)
	{
	case WinHandle::Type::File:
		if (handle->handle)
		{
			std::fclose(static_cast<FILE*>(handle->handle));
		}
		break;
	case WinHandle::Type::Thread:
		if (handle->handle)
		{
			auto* thread = static_cast<pthread_t*>(handle->handle);
			pthread_join(*thread, nullptr);
			delete thread;
		}
		break;
	case WinHandle::Type::Semaphore:
		if (handle->handle)
		{
			auto* semaphore = static_cast<sem_t*>(handle->handle);
			sem_destroy(semaphore);
			delete semaphore;
		}
		break;
	case WinHandle::Type::Event:
		break;
	default:
		break;
	}

	delete handle;
	return TRUE;
}

inline DWORD GetLastError()
{
	return static_cast<DWORD>(errno);
}

typedef DWORD(WINAPI* LPTHREAD_START_ROUTINE)(LPVOID);

struct ThreadStartContext
{
	LPTHREAD_START_ROUTINE routine;
	LPVOID param;
};

inline void* ThreadStartThunk(void* param)
{
	auto* ctx = static_cast<ThreadStartContext*>(param);
	DWORD result = ctx->routine(ctx->param);
	delete ctx;
	return reinterpret_cast<void*>(static_cast<uintptr_t>(result));
}

inline HANDLE CreateThread(void*, size_t, LPTHREAD_START_ROUTINE routine, LPVOID param, DWORD, DWORD*)
{
	if (!routine)
	{
		errno = EINVAL;
		return nullptr;
	}

	auto* thread = new pthread_t();
	auto* ctx = new ThreadStartContext{ routine, param };
	if (pthread_create(thread, nullptr, ThreadStartThunk, ctx) != 0)
	{
		delete thread;
		delete ctx;
		return nullptr;
	}

	auto* handle = new WinHandle();
	handle->type = WinHandle::Type::Thread;
	handle->handle = thread;
	return handle;
}

inline BOOL SetThreadPriority(HANDLE, int)
{
	return TRUE;
}

inline BOOL TerminateThread(HANDLE handle, DWORD)
{
	if (!handle || handle->type != WinHandle::Type::Thread || !handle->handle)
	{
		return FALSE;
	}

	auto* thread = static_cast<pthread_t*>(handle->handle);
	return pthread_cancel(*thread) == 0 ? TRUE : FALSE;
}

inline HANDLE CreateSemaphore(void*, LONG initialCount, LONG, const char*)
{
	auto* semaphore = new sem_t();
	if (sem_init(semaphore, 0, static_cast<unsigned int>(initialCount)) != 0)
	{
		delete semaphore;
		return nullptr;
	}

	auto* handle = new WinHandle();
	handle->type = WinHandle::Type::Semaphore;
	handle->handle = semaphore;
	return handle;
}

inline BOOL ReleaseSemaphore(HANDLE handle, LONG releaseCount, LONG*)
{
	if (!handle || handle->type != WinHandle::Type::Semaphore || !handle->handle)
	{
		return FALSE;
	}

	auto* semaphore = static_cast<sem_t*>(handle->handle);
	for (LONG i = 0; i < releaseCount; ++i)
	{
		sem_post(semaphore);
	}
	return TRUE;
}

inline DWORD WaitForSingleObject(HANDLE handle, DWORD milliseconds)
{
	if (!handle)
	{
		return WAIT_FAILED;
	}

	if (handle->type == WinHandle::Type::Semaphore && handle->handle)
	{
		auto* semaphore = static_cast<sem_t*>(handle->handle);
		if (milliseconds == INFINITE)
		{
			return sem_wait(semaphore) == 0 ? WAIT_OBJECT_0 : WAIT_FAILED;
		}

		struct timespec ts {};
		clock_gettime(CLOCK_REALTIME, &ts);
		ts.tv_sec += milliseconds / 1000;
		ts.tv_nsec += static_cast<long>((milliseconds % 1000) * 1000000);
		if (ts.tv_nsec >= 1000000000)
		{
			ts.tv_sec += 1;
			ts.tv_nsec -= 1000000000;
		}
		int result = sem_timedwait(semaphore, &ts);
		if (result == 0)
		{
			return WAIT_OBJECT_0;
		}
		if (errno == ETIMEDOUT)
		{
			return WAIT_TIMEOUT;
		}
		return WAIT_FAILED;
	}

	if (handle->type == WinHandle::Type::Thread && handle->handle)
	{
		auto* thread = static_cast<pthread_t*>(handle->handle);
		return pthread_join(*thread, nullptr) == 0 ? WAIT_OBJECT_0 : WAIT_FAILED;
	}

	return WAIT_FAILED;
}

struct WSANETWORKEVENTS
{
	long lNetworkEvents;
};

using WSAEVENT = HANDLE;

inline int WSAStartup(WORD, void*)
{
	return 0;
}

inline int WSACleanup()
{
	return 0;
}

inline WSAEVENT WSACreateEvent()
{
	auto* handle = new WinHandle();
	handle->type = WinHandle::Type::Event;
	return handle;
}

inline BOOL WSACloseEvent(WSAEVENT handle)
{
	return CloseHandle(handle);
}

inline int WSAEventSelect(SOCKET socket, WSAEVENT eventHandle, long mask)
{
	if (!eventHandle || eventHandle->type != WinHandle::Type::Event)
	{
		return SOCKET_ERROR;
	}

	eventHandle->socket = socket;
	eventHandle->eventMask = mask;
	return 0;
}

inline DWORD WSAWaitForMultipleEvents(DWORD eventCount, const WSAEVENT* events, BOOL, DWORD timeout, BOOL)
{
	if (eventCount == 0 || !events || !events[0])
	{
		return WSA_WAIT_FAILED;
	}

	auto* eventHandle = events[0];
	if (eventHandle->type != WinHandle::Type::Event || eventHandle->socket < 0)
	{
		return WSA_WAIT_FAILED;
	}

	struct pollfd pfd {};
	pfd.fd = eventHandle->socket;
	pfd.events = 0;

	if (eventHandle->eventMask & FD_READ)
	{
		pfd.events |= POLLIN;
	}
	if (eventHandle->eventMask & FD_WRITE)
	{
		pfd.events |= POLLOUT;
	}
	if (eventHandle->eventMask & FD_CLOSE)
	{
		pfd.events |= POLLHUP;
	}

	int pollTimeout = (timeout == WSA_INFINITE) ? -1 : static_cast<int>(timeout);
	int result = poll(&pfd, 1, pollTimeout);
	if (result < 0)
	{
		return WSA_WAIT_FAILED;
	}
	if (result == 0)
	{
		return WSA_WAIT_TIMEOUT;
	}

	long events = 0;
	if (pfd.revents & (POLLIN | POLLPRI))
	{
		events |= FD_READ;
	}
	if (pfd.revents & POLLOUT)
	{
		events |= FD_WRITE;
	}
	if (pfd.revents & (POLLHUP | POLLERR))
	{
		events |= FD_CLOSE;
	}

	eventHandle->lastEvents = events;
	return WSA_WAIT_EVENT_0;
}

inline int WSAEnumNetworkEvents(SOCKET, WSAEVENT eventHandle, WSANETWORKEVENTS* events)
{
	if (!eventHandle || eventHandle->type != WinHandle::Type::Event || !events)
	{
		return SOCKET_ERROR;
	}

	events->lNetworkEvents = eventHandle->lastEvents;
	eventHandle->lastEvents = 0;
	return 0;
}

#ifndef WSAEWOULDBLOCK
#define WSAEWOULDBLOCK EWOULDBLOCK
#endif

#ifndef WSA_IO_PENDING
#define WSA_IO_PENDING EINPROGRESS
#endif

#ifndef WSAENOTSOCK
#define WSAENOTSOCK ENOTSOCK
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
