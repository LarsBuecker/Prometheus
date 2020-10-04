#include "Prometheus.h"

class Sandbox : public Prometheus::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Prometheus::Application* Prometheus::CreateApplication() {
	return new Sandbox();
}