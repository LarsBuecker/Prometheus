#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Prometheus/Events/Event.h"
#include "Prometheus/Events/ApplicationEvent.h"

#include "Prometheus/Core/Timestep.h"

#include "Prometheus/ImGui/ImGuiLayer.h"

namespace Prometheus {

	class PROMETHEUS_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		
		void OnEvent(Event& e);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};
	
	// To be defined in CLIENT
	Application* CreateApplication();
}



