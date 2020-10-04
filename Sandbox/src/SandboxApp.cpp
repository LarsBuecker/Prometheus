#include "Prometheus.h"

class ExampleLayer : public Prometheus::Layer {
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		PM_INFO("ExampleLayer::Update");
	}

	void OnEvent(Prometheus::Event& event) override
	{
		PM_TRACE("{0}", event);
	}
};

class Sandbox : public Prometheus::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

Prometheus::Application* Prometheus::CreateApplication() {
	return new Sandbox();
}