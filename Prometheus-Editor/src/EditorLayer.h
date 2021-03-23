#pragma once

#include "Prometheus.h"

class EditorLayer : public Prometheus::Layer
{
public:
	EditorLayer();
	virtual ~EditorLayer() = default;

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
	Prometheus::Ref<Prometheus::Framebuffer> m_Framebuffer;
	// ----

	Prometheus::Ref<Prometheus::Texture2D> m_CheckerboardTexture;
	Prometheus::Ref<Prometheus::Texture2D> m_SpriteSheet;
	Prometheus::Ref<Prometheus::SubTexture2D> m_TextureBush;

	glm::vec4 m_SquareColor = { 1.0f, 1.0f, 1.0f, 1.0f};
};
