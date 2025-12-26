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
typedef uintptr_t UINT_PTR;
typedef unsigned short ATOM;
typedef unsigned long DWORD_PTR;
typedef uintptr_t ULONG_PTR;
typedef unsigned long WPARAM;
typedef long LPARAM;
typedef long LRESULT;
typedef intptr_t INT_PTR;
typedef int errno_t;
typedef unsigned long long ULONGLONG;
typedef void VOID;

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
		Mutex,
		Event,
		TimerQueue,
		Timer,
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
typedef void* HGDIOBJ;
typedef void* HDC;
typedef unsigned long COLORREF;
typedef void* PVOID;
typedef unsigned char BOOLEAN;
typedef void* LPVOID;
typedef const char* LPCSTR;
typedef char* LPSTR;
typedef const char* LPCTSTR;
typedef char* LPTSTR;
typedef char TCHAR;

#ifndef FAR
#define FAR
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef CALLBACK
#define CALLBACK
#endif

#ifndef WINAPI
#define WINAPI
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

typedef WSAOVERLAPPED OVERLAPPED;
typedef OVERLAPPED* LPOVERLAPPED;
typedef DWORD* LPDWORD;

typedef struct _WSABUF
{
	ULONG len;
	char* buf;
} WSABUF, * LPWSABUF;

typedef int (CALLBACK* LPCONDITIONPROC)(LPWSABUF, LPWSABUF, LPQOS, LPQOS, LPWSABUF, LPWSABUF, GROUP*, DWORD_PTR);
typedef void* LPWSAOVERLAPPED_COMPLETION_ROUTINE;
typedef VOID(CALLBACK* WAITORTIMERCALLBACK)(PVOID, BOOLEAN);

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
typedef sockaddr_in SOCKADDR_IN;
typedef sockaddr SOCKADDR;

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

#ifndef WSA_FLAG_OVERLAPPED
#define WSA_FLAG_OVERLAPPED 0x01
#endif

#ifndef CF_ACCEPT
#define CF_ACCEPT 0
#endif

#ifndef CF_REJECT
#define CF_REJECT 1
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

#ifndef ERROR_SEM_TIMEOUT
#define ERROR_SEM_TIMEOUT 121
#endif

#ifndef ERROR_NETNAME_DELETED
#define ERROR_NETNAME_DELETED 64
#endif

#ifndef ERROR_ALREADY_EXISTS
#define ERROR_ALREADY_EXISTS 183
#endif

#ifndef ERROR_CONNECTION_ABORTED
#define ERROR_CONNECTION_ABORTED 1236
#endif

#ifndef ERROR_OPERATION_ABORTED
#define ERROR_OPERATION_ABORTED 995
#endif

#ifndef WT_EXECUTEINTIMERTHREAD
#define WT_EXECUTEINTIMERTHREAD 0x00000020
#endif

#ifndef MB_OK
#define MB_OK 0x00000000L
#endif

#ifndef MB_OKCANCEL
#define MB_OKCANCEL 0x00000001L
#endif

#ifndef MB_YESNO
#define MB_YESNO 0x00000004L
#endif

#ifndef MB_ICONERROR
#define MB_ICONERROR 0x00000010L
#endif

#ifndef MB_ICONQUESTION
#define MB_ICONQUESTION 0x00000020L
#endif

#ifndef IDOK
#define IDOK 1
#endif

#ifndef IDCANCEL
#define IDCANCEL 2
#endif

#ifndef IDYES
#define IDYES 6
#endif

#ifndef IDNO
#define IDNO 7
#endif

#ifndef SW_HIDE
#define SW_HIDE 0
#endif

#ifndef SW_SHOW
#define SW_SHOW 5
#endif

#ifndef CW_USEDEFAULT
#define CW_USEDEFAULT 0x80000000
#endif

#ifndef WS_OVERLAPPEDWINDOW
#define WS_OVERLAPPEDWINDOW 0x00CF0000
#endif

#ifndef WS_THICKFRAME
#define WS_THICKFRAME 0x00040000
#endif

#ifndef CS_HREDRAW
#define CS_HREDRAW 0x0002
#endif

#ifndef CS_VREDRAW
#define CS_VREDRAW 0x0001
#endif

#ifndef COLOR_CAPTIONTEXT
#define COLOR_CAPTIONTEXT 9
#endif

#ifndef TRANSPARENT
#define TRANSPARENT 1
#endif

#ifndef DT_CENTER
#define DT_CENTER 0x00000001
#endif

#ifndef DT_VCENTER
#define DT_VCENTER 0x00000004
#endif

#ifndef DT_SINGLELINE
#define DT_SINGLELINE 0x00000020
#endif

#ifndef DEFAULT_CHARSET
#define DEFAULT_CHARSET 1
#endif

#ifndef OUT_DEFAULT_PRECIS
#define OUT_DEFAULT_PRECIS 0
#endif

#ifndef CLIP_DEFAULT_PRECIS
#define CLIP_DEFAULT_PRECIS 0
#endif

#ifndef DEFAULT_QUALITY
#define DEFAULT_QUALITY 0
#endif

#ifndef DEFAULT_PITCH
#define DEFAULT_PITCH 0
#endif

#ifndef FF_DONTCARE
#define FF_DONTCARE 0
#endif

#ifndef NONANTIALIASED_QUALITY
#define NONANTIALIASED_QUALITY 3
#endif

#ifndef FW_THIN
#define FW_THIN 100
#endif

#ifndef FW_NORMAL
#define FW_NORMAL 400
#endif

#ifndef THREAD_PRIORITY_HIGHEST
#define THREAD_PRIORITY_HIGHEST 2
#endif

#ifndef IDC_ARROW
#define IDC_ARROW ((LPCSTR)(uintptr_t)32512)
#endif

#ifndef MF_BYCOMMAND
#define MF_BYCOMMAND 0x00000000L
#endif

#ifndef MF_CHECKED
#define MF_CHECKED 0x00000008L
#endif

#ifndef MF_UNCHECKED
#define MF_UNCHECKED 0x00000000L
#endif

#ifndef WM_COMMAND
#define WM_COMMAND 0x0111
#endif

#ifndef WM_CLOSE
#define WM_CLOSE 0x0010
#endif

#ifndef WM_TIMER
#define WM_TIMER 0x0113
#endif

#ifndef WM_SIZE
#define WM_SIZE 0x0005
#endif

#ifndef WM_ACTIVATE
#define WM_ACTIVATE 0x0006
#endif

#ifndef WM_DESTROY
#define WM_DESTROY 0x0002
#endif

#ifndef WM_INITDIALOG
#define WM_INITDIALOG 0x0110
#endif

#ifndef WM_COMMAND
#define WM_COMMAND 0x0111
#endif

#ifndef LB_ADDSTRING
#define LB_ADDSTRING 0x0180
#endif

#ifndef LB_DELETESTRING
#define LB_DELETESTRING 0x0182
#endif

#ifndef LB_RESETCONTENT
#define LB_RESETCONTENT 0x0184
#endif

#ifndef LB_GETCURSEL
#define LB_GETCURSEL 0x0188
#endif

#ifndef LB_GETITEMDATA
#define LB_GETITEMDATA 0x0199
#endif

#ifndef LB_SETITEMDATA
#define LB_SETITEMDATA 0x019A
#endif

#ifndef LOWORD
#define LOWORD(l) (static_cast<WORD>((static_cast<DWORD_PTR>(l)) & 0xFFFF))
#endif

#ifndef HIWORD
#define HIWORD(l) (static_cast<WORD>(((static_cast<DWORD_PTR>(l)) >> 16) & 0xFFFF))
#endif

#ifndef LOBYTE
#define LOBYTE(w) (static_cast<BYTE>((static_cast<WORD>(w)) & 0xFF))
#endif

#ifndef HIBYTE
#define HIBYTE(w) (static_cast<BYTE>(((static_cast<WORD>(w)) >> 8) & 0xFF))
#endif

#ifndef LBN_SELCHANGE
#define LBN_SELCHANGE 1
#endif
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef INT_PTR(CALLBACK* DLGPROC)(HWND, UINT, WPARAM, LPARAM);

struct WNDCLASSEX
{
	UINT cbSize;
	UINT style;
	WNDPROC lpfnWndProc;
	int cbClsExtra;
	int cbWndExtra;
	HINSTANCE hInstance;
	HICON hIcon;
	HCURSOR hCursor;
	HBRUSH hbrBackground;
	LPCSTR lpszMenuName;
	LPCSTR lpszClassName;
	HICON hIconSm;
};

struct MSG
{
	HWND hwnd;
	UINT message;
	WPARAM wParam;
	LPARAM lParam;
	DWORD time;
	int pt_x;
	int pt_y;
};

struct WSADATA
{
	WORD wVersion;
	WORD wHighVersion;
	char szDescription[257];
	char szSystemStatus[129];
	unsigned short iMaxSockets;
	unsigned short iMaxUdpDg;
	char* lpVendorInfo;
};

inline ATOM RegisterClassEx(const WNDCLASSEX*)
{
	return 1;
}

inline HINSTANCE GetModuleHandle(const char*)
{
	return nullptr;
}

inline HICON LoadIcon(HINSTANCE, LPCSTR)
{
	return nullptr;
}

inline HCURSOR LoadCursor(HINSTANCE, LPCSTR)
{
	return nullptr;
}

inline HWND CreateWindow(LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID)
{
	return reinterpret_cast<HWND>(1);
}

inline BOOL ShowWindow(HWND, int)
{
	return TRUE;
}

inline BOOL UpdateWindow(HWND)
{
	return TRUE;
}

inline HWND GetConsoleWindow()
{
	return nullptr;
}

inline BOOL DestroyWindow(HWND)
{
	return TRUE;
}

inline UINT_PTR SetTimer(HWND, UINT_PTR, UINT, void*)
{
	return 1;
}

inline BOOL PostQuitMessage(int)
{
	return TRUE;
}

inline LRESULT DefWindowProc(HWND, UINT, WPARAM, LPARAM)
{
	return 0;
}

inline INT_PTR DialogBox(HINSTANCE, LPCSTR, HWND, DLGPROC)
{
	return 0;
}

inline BOOL EndDialog(HWND, INT_PTR)
{
	return TRUE;
}

inline HMENU GetMenu(HWND)
{
	return nullptr;
}

inline DWORD CheckMenuItem(HMENU, UINT, UINT)
{
	return 0;
}

inline int MessageBox(HWND, const char*, const char*, UINT type)
{
	if (type & MB_YESNO)
	{
		return IDYES;
	}

	return IDOK;
}

inline BOOL SetConsoleOutputCP(UINT)
{
	return TRUE;
}

inline BOOL GetMessage(MSG* msg, HWND, UINT, UINT)
{
	if (msg)
	{
		msg->wParam = 0;
	}
	return FALSE;
}

inline BOOL TranslateMessage(const MSG*)
{
	return TRUE;
}

inline LRESULT DispatchMessageA(const MSG*)
{
	return 0;
}

inline BOOL SetWindowText(HWND, const char*)
{
	return TRUE;
}

inline HWND SetFocus(HWND)
{
	return nullptr;
}

inline LRESULT SendMessage(HWND, UINT, WPARAM, LPARAM)
{
	return 0;
}

inline HWND GetDlgItem(HWND, int)
{
	return nullptr;
}

inline BOOL SetDlgItemText(HWND, int, const char*)
{
	return TRUE;
}

inline COLORREF RGB(BYTE red, BYTE green, BYTE blue)
{
	return static_cast<COLORREF>((red) | (static_cast<COLORREF>(green) << 8) | (static_cast<COLORREF>(blue) << 16));
}

inline HFONT CreateFont(int, int, int, int, int, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, const char*)
{
	return nullptr;
}

inline HBRUSH CreateSolidBrush(COLORREF)
{
	return nullptr;
}

inline BOOL DeleteObject(HGDIOBJ)
{
	return TRUE;
}

inline BOOL GetClientRect(HWND, RECT* rect)
{
	if (!rect)
	{
		return FALSE;
	}

	rect->left = 0;
	rect->top = 0;
	rect->right = 0;
	rect->bottom = 0;
	return TRUE;
}

inline HDC GetDC(HWND)
{
	return nullptr;
}

inline int ReleaseDC(HWND, HDC)
{
	return 0;
}

inline int SetBkMode(HDC, int mode)
{
	return mode;
}

inline COLORREF SetTextColor(HDC, COLORREF color)
{
	return color;
}

inline HGDIOBJ SelectObject(HDC, HGDIOBJ object)
{
	return object;
}

inline BOOL FillRect(HDC, const RECT*, HBRUSH)
{
	return TRUE;
}

inline int DrawText(HDC, const char*, int, RECT*, UINT)
{
	return 0;
}

inline COLORREF SetBkColor(HDC, COLORREF color)
{
	return color;
}

inline BOOL TextOut(HDC, int, int, const char*, int)
{
	return TRUE;
}

inline HANDLE CreateIoCompletionPort(HANDLE fileHandle, HANDLE existingCompletionPort, ULONG_PTR, DWORD)
{
	if (existingCompletionPort)
	{
		return existingCompletionPort;
	}

	auto* handle = new WinHandle();
	handle->type = WinHandle::Type::Unknown;
	handle->handle = fileHandle;
	return handle;
}

inline BOOL GetQueuedCompletionStatus(HANDLE, LPDWORD bytesTransferred, ULONG_PTR* completionKey, LPOVERLAPPED* overlapped, DWORD)
{
	if (bytesTransferred)
	{
		*bytesTransferred = 0;
	}
	if (completionKey)
	{
		*completionKey = 0;
	}
	if (overlapped)
	{
		*overlapped = nullptr;
	}
	errno = ENOSYS;
	return FALSE;
}

inline UINT GetPrivateProfileInt(const char*, const char*, int defaultValue, const char*)
{
	return static_cast<UINT>(defaultValue);
}

inline DWORD GetPrivateProfileString(const char*, const char*, const char* defaultValue, char* returnedString, DWORD size, const char*)
{
	if (!returnedString || size == 0)
	{
		return 0;
	}

	if (!defaultValue)
	{
		returnedString[0] = '\0';
		return 0;
	}

	std::strncpy(returnedString, defaultValue, size);
	returnedString[size - 1] = '\0';
	return static_cast<DWORD>(std::strlen(returnedString));
}

inline int _strcmpi(const char* left, const char* right)
{
	if (!left || !right)
	{
		return (left == right) ? 0 : (left ? 1 : -1);
	}

	return strcasecmp(left, right);
}

inline int _stricmp(const char* left, const char* right)
{
	return _strcmpi(left, right);
}

inline long long _atoi64(const char* input)
{
	if (!input)
	{
		return 0;
	}

	return std::strtoll(input, nullptr, 10);
}

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

typedef struct _SYSTEM_INFO
{
	DWORD dwNumberOfProcessors;
} SYSTEM_INFO;

inline void GetSystemInfo(SYSTEM_INFO* info)
{
	if (!info)
	{
		return;
	}

	long count = sysconf(_SC_NPROCESSORS_ONLN);
	info->dwNumberOfProcessors = (count > 0) ? static_cast<DWORD>(count) : 1;
}

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

inline int fopen_s(FILE** file, const char* filename, const char* mode)
{
	if (!file)
	{
		return EINVAL;
	}

	*file = std::fopen(filename, mode);
	return (*file) ? 0 : errno;
}

inline int strncpy_s(char* destination, size_t destinationSize, const char* source, size_t count)
{
	if (!destination || destinationSize == 0)
	{
		return -1;
	}

	if (!source)
	{
		destination[0] = '\0';
		return -1;
	}

	size_t toCopy = (count < destinationSize - 1) ? count : (destinationSize - 1);
	std::strncpy(destination, source, toCopy);
	destination[toCopy] = '\0';
	return 0;
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
	case WinHandle::Type::Mutex:
		if (handle->handle)
		{
			auto* mutex = static_cast<pthread_mutex_t*>(handle->handle);
			pthread_mutex_destroy(mutex);
			delete mutex;
		}
		break;
	case WinHandle::Type::Event:
	case WinHandle::Type::TimerQueue:
	case WinHandle::Type::Timer:
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

inline HANDLE CreateMutex(void*, BOOL, const char*)
{
	auto* mutex = new pthread_mutex_t();
	if (pthread_mutex_init(mutex, nullptr) != 0)
	{
		delete mutex;
		return nullptr;
	}

	errno = 0;

	auto* handle = new WinHandle();
	handle->type = WinHandle::Type::Mutex;
	handle->handle = mutex;
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

inline HANDLE CreateTimerQueue()
{
	auto* handle = new WinHandle();
	handle->type = WinHandle::Type::TimerQueue;
	return handle;
}

inline BOOL DeleteTimerQueue(HANDLE handle)
{
	return CloseHandle(handle);
}

inline BOOL CreateTimerQueueTimer(HANDLE* timerHandle, HANDLE, WAITORTIMERCALLBACK, PVOID, DWORD, DWORD, DWORD)
{
	if (!timerHandle)
	{
		return FALSE;
	}

	auto* handle = new WinHandle();
	handle->type = WinHandle::Type::Timer;
	*timerHandle = handle;
	return TRUE;
}

inline BOOL DeleteTimerQueueTimer(HANDLE, HANDLE timerHandle, HANDLE)
{
	return CloseHandle(timerHandle);
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

	if (handle->type == WinHandle::Type::Mutex && handle->handle)
	{
		auto* mutex = static_cast<pthread_mutex_t*>(handle->handle);
		if (milliseconds == INFINITE)
		{
			return pthread_mutex_lock(mutex) == 0 ? WAIT_OBJECT_0 : WAIT_FAILED;
		}

		if (pthread_mutex_trylock(mutex) == 0)
		{
			return WAIT_OBJECT_0;
		}

		return WAIT_TIMEOUT;
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

inline SOCKET WSASocketW(int af, int type, int protocol, void*, unsigned int, DWORD)
{
	return socket(af, type, protocol);
}

#ifndef WSASocketW
#define WSASocketW(af, type, protocol, lpProtocolInfo, g, flags) socket((af), (type), (protocol))
#endif

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

	long networkEvents = 0;
	if (pfd.revents & (POLLIN | POLLPRI))
	{
		networkEvents |= FD_READ;
	}
	if (pfd.revents & POLLOUT)
	{
		networkEvents |= FD_WRITE;
	}
	if (pfd.revents & (POLLHUP | POLLERR))
	{
		networkEvents |= FD_CLOSE;
	}

	eventHandle->lastEvents = networkEvents;
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

inline SOCKET WSAAccept(SOCKET socket, sockaddr* addr, int* addrlen, LPCONDITIONPROC, DWORD_PTR)
{
	if (!addrlen)
	{
		return accept(socket, addr, nullptr);
	}

	socklen_t length = static_cast<socklen_t>(*addrlen);
	SOCKET result = accept(socket, addr, &length);
	*addrlen = static_cast<int>(length);
	return result;
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

inline errno_t localtime_s(std::tm* result, const std::time_t* time)
{
	if (!result || !time)
	{
		return EINVAL;
	}

	return (localtime_r(time, result) == nullptr) ? EINVAL : 0;
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

	std::time_t GetTime() const
	{
		return m_time;
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
