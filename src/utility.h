#pragma once
#ifndef RENIK_UTILITY_H
#define RENIK_UTILITY_H
#include <stdarg.h>
#include <string>

#if defined(_WIN32)
#include <Windows.h>
#endif

namespace renik {
	namespace Util {
		inline const char* Concat(const char* fmt, ...) {
			char buff[4096];
			va_list arg;
			va_start(arg, fmt);
			vsnprintf_s(buff, sizeof(buff), fmt, arg);
			va_end(arg);

			return buff;
		}
		inline const wchar_t* LastSysErr() {
#if defined(_WIN32)
			LPVOID lpMsgBuf;
			FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				GetLastError(),
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&lpMsgBuf,
				0, NULL);
			return (const wchar_t*)lpMsgBuf;
#else
			return std::wstring();
#endif
		}
	}
}
#endif // !RENIK_UTILITY_H
