#pragma once

#include "Prometheus/Core/Layer.h"

#include "Prometheus/Events/KeyEvent.h"
#include "Prometheus/Events/MouseEvent.h"
#include "Prometheus/Events/ApplicationEvent.h"


namespace Prometheus {

	class PROMETHEUS_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& event);
		virtual void OnImGuiRender() override;	

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}

