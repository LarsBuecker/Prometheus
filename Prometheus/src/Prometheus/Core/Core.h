#pragma once

#include <memory>

#ifdef PM_PLATFORM_WINDOWS
	#ifdef PM_DYNAMIC_LINK
		#ifdef PM_BUILD_DLL
			#define PROMETHEUS_API __declspec(dllexport)
		#else
			#define PROMETHEUS_API __declspec(dllimport)
		#endif // PM_BUILD_DLL
	#else
		#define PROMETHEUS_API
	#endif
#else
	#error Prometheus only supports Windows!
#endif // PM_PLATFORM_WINDOWS

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