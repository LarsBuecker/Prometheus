#pragma once

#include "Prometheus.h"

class Sandbox2D : public Prometheus::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Prometheus::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Prometheus::Event& e) override;
private:
	Prometheus::OrthographicCameraController m_CameraController;

	// Temp
	Prometheus::Ref<Prometheus::VertexArray> m_SquareVA;
	Prometheus::Ref<Prometheus::Shader> m_FlatColorShader;
	Prometheus::Ref<Prometheus::Texture2D> m_Texture;
	// ----

	Prometheus::Ref<Prometheus::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f};
};
