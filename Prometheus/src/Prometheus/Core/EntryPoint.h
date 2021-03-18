#pragma once

#ifdef PM_PLATFORM_WINDOWS

extern Prometheus::Application* Prometheus::CreateApplication();

int main(int argc, char** argv) {	

	Prometheus::Log::Init();

	PM_PROFILE_BEGIN_SESSION("Startup", "PrometheusProfile-Startup.json");
	auto app = Prometheus::CreateApplication();
	PM_PROFILE_END_SESSION();

	PM_PROFILE_BEGIN_SESSION("Runtime", "PrometheusProfile-Runtime.json");
	app->Run();
	PM_PROFILE_END_SESSION();

	PM_PROFILE_BEGIN_SESSION("Shutdown", "PrometheusProfile-Shutdown.json");
	delete app;
	PM_PROFILE_END_SESSION();
}

#endif // PM_PLATFORM_WINDOWS

