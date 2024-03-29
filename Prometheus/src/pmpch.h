#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Prometheus/Core/Log.h"
#include "Prometheus/Debug/Instrumentor.h"

#ifdef PM_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // PM_PLATFORM_WINDOWS

