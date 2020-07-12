#pragma once
#ifndef RENIK_BASE_H
	#if defined(_WIN32) || defined(_WIN64)
		#define RENIK_API(type) __declspec(dllexport) type
	#elif defined(__ANDROID__) ||  defined(__EMSCRIPTEN__)
		#if defined (__GNUC__) && __GNUC__ >= 4 || defined (__SUNPRO_C) && __SUNPRO_C == 0x590
			#define RENIK_API(type) __attribute__((visibility("default"))) type
		#endif
	#elif defined(__linux__) || defined (__unix__) || defined(__APPLE__)
		#define RENIK_API(type) type
	#else
		#define RENIK_API(type) type
	#endif
#endif // !RENIK_BASE_H

