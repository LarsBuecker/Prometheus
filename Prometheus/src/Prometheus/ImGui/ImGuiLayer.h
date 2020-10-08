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
		virtual void OnImGuiRender() override;	

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}

