#pragma once
#ifndef RENIK_HEADERS_H
#define RENIK_HEADERS_H

#if defined(_WIN32) || defined(_WIN64)
	#ifndef WIN32_LEAD_AND_MEAN
		#define WIN32_LEAN_AND_MEAN 1
	#endif

#ifndef NOMINMAX
	#define NOMINMAX
#endif

	#include <windows.h>
	#define RENIK_PLATFORM_WIN 1
#elif defined(__ANDROID__)
	#include <jni.h>
	#include <native_app_glue\android_native_app_glue.h>
	#if defined (__GNUC__) && __GNUC__ >= 4 || defined (__SUNPRO_C) && __SUNPRO_C == 0x590
		#define RENIK_API(type) __attribute__((visibility("default"))) type
	#endif
	#define RENIK_PLATFORM_ANDROID 1
	#define RENIK_API(type) JNIEXPORT type JNICALL
#elif defined(__linux__) || defined (__unix__) || defined(__APPLE__)
	#include <X11.h>
	#define RENIK_API(type) type
	#if defined(__APPLE__)
		#define RENIK_PLATFORM_APPLE 1
	#else
		#define RENIK_API(type) type
	#endif
#elif defined(__EMSCRIPTEN__)
	#if defined (__GNUC__) && __GNUC__ >= 4 || defined (__SUNPRO_C) && __SUNPRO_C == 0x590
		#define RENIK_API(type) __attribute__((visibility("default"))) type
	#endif
	#define RENIK_PLATFORM_WEBGL 1
#else
	#define RENIK_API(type) type
	#define RENIK_PLATFORM_UNKNOWN 1
#endif

#if defined(_DEBUG)
	#define RENIK_ENABLE_DEBUG 1
#else
	#define RENIK_ENABLE_DEBUG 0
#endif

#define RENIK_ENABLE_LOG 0
#define UNICODE 1

//include graphic
#if RENIK_PLATFORM_ANDROID || RENIK_PLATFORM_WEBGL || RENIK_ENABLE_WINGLES || RENIK_PLATFORM_WIN
	#ifdef RENIK_INCLUDE_GRAPHIC_GL
		#define RENIK_GL 1
		#pragma comment (lib, "OpenGL32.lib")
	#endif
	#ifdef RENIK_INCLUDE_GRAPHIC_GLES
		#define GL_GLEXT_PROTOTYPES 1
		#include <GL\glew.h>
		#pragma comment (lib, "libEGL.lib")
		#pragma comment (lib, "libGLESv2.lib")
		#define RENIK_GLES 4
	#endif
#endif

#if RENIK_PLATFORM_WIN
	#ifdef RENIK_INCLUDE_GRAPHIC_DX9
		#include <d3d9.h>
		#pragma comment (lib, "d3d9.lib")
		#define RENIK_DX9 1
	#endif
	#ifdef RENIK_INCLUDE_GRAPHIC_DX11
		#include <d3d11.h>
		#pragma comment (lib, "d3d11.lib")
		#define RENIK_DX11 2
	#endif
	#ifdef RENIK_INCLUDE_GRAPHIC_DX12
		#include <d3d12.h>
		#pragma comment (lib, "d3d12.lib")
		#define RENIK_DX12 3
	#endif
#endif

#if RENIK_INCLUDE_GRAPHIC_VULKAN
	#define RENIK_VULKAN
#endif


//include std library
#include <vector>
#include <string>
#include <unordered_map>
#include <map>

namespace renik {
#define byte unsigned char
#define ulong unsigned long
#define uint unsigned int
#define ullong unsigned long long
#define llong long long

typedef size_t id_t;

#define SAFE_DELETE(var) if(var != NULL) delete var
#define SAFE_DELETE_ARR(var) if(var != NULL) delete[] var;
}
#endif

