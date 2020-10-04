#pragma once

#ifdef PM_PLATFORM_WINDOWS
	#ifdef PM_BUILD_DLL
		#define PROMETHEUS_API __declspec(dllexport)
	#else
		#define PROMETHEUS_API __declspec(dllimport)
	#endif // PM_BUILD_DLL
#else
	#error Prometheus only supports Windows!
#endif // PM_PLATFORM_WINDOWS

#define BIT(x) (1 << x)
