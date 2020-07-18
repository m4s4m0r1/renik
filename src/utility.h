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
		template<typename ... Args>
		inline std::string StringFormat(const std::string& format, Args ... args)
		{
			size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1;
			std::unique_ptr<char[]> buf(new char[size]);
			snprintf(buf.get(), size, format.c_str(), args ...);
			return std::string(buf.get(), buf.get() + size - 1);
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
