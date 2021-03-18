#pragma once

#include <memory>

#ifdef _WIN32
	// Windows x64/x86
	#ifdef _WIN64
		// Windows x64
		#define PM_PLATFROM_WINDWOS
	#else
		// Windows x86
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define PM_PLATFROM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define PM_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#define PROMETHEUS_API __declspec(dllimport)
		#error "Unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#define PM_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define PM_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	#error "Unknown plattform!"
#endif

// DLL support
#ifdef PM_PLATFORM_WINDOWS
	#if PM_DYNAMIC_LINK
		#ifdef PM_BUILD_DLL
			#define PROMETHEUS_API __declspec(dllexport)
		#else
			#define PROMETHEUS_API __declspec(dllimport)
		#endif
	#else	
		#define PROMETHEUS_API
	#endif
#else
	#error "Prometheus only supports Windows!"
#endif


#ifdef PM_ENABLE_ASSERTS
	#define PM_ASSERT(x, ...) { if(!(x)) { PM_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define PM_CORE_ASSERT(x, ...) { if(!(x)) { PM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define PM_ASSERT(x, ...)
	#define PM_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define PM_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Prometheus {
	
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}