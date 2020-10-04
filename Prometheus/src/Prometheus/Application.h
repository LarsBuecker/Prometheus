#pragma once

#include "Core.h"

namespace Prometheus {

	class PROMETHEUS_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};
	
	// To be defined in CLIENT
	Application* CreateApplication();
}



