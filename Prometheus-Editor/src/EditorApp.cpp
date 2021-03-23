#include "Prometheus.h"
#include "Prometheus/Core/EntryPoint.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EditorLayer.h"



class EditorApp : public Prometheus::Application {
public:
	EditorApp() 
		: Application("Prometheus Editor")
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new EditorLayer());
	}

	~EditorApp() 
	{
	}
};

Prometheus::Application* Prometheus::CreateApplication() {
	return new EditorApp();
}