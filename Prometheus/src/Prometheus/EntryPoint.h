#pragma once

#ifdef PM_PLATFORM_WINDOWS

extern Prometheus::Application* Prometheus::CreateApplication();

int main(int argc, char** argv) {	

	Prometheus::Log::Init();
	PM_CORE_WARN("Initialized Log!");
	PM_INFO("Hello!");

	auto app = Prometheus::CreateApplication();
	app->Run();
	delete app;
}

#endif // PM_PLATFORM_WINDOWS

