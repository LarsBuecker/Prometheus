#include "Prometheus.h"
#include "Prometheus/Core/EntryPoint.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"



class Sandbox : public Prometheus::Application {
public:
	Sandbox() 
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() 
	{
	}
};

Prometheus::Application* Prometheus::CreateApplication() {
	return new Sandbox();
}