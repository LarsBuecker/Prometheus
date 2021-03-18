#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	PM_PROFILE_FUNCTION();

	m_CheckerboardTexture = Prometheus::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	PM_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Prometheus::Timestep ts)
{
	PM_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	{
		PM_PROFILE_SCOPE("Renderer Prep");
		Prometheus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Prometheus::RenderCommand::Clear();
	}
	
	{
		PM_PROFILE_SCOPE("Renderer Draw");
		Prometheus::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Prometheus::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Prometheus::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Prometheus::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10, m_SquareColor);
		Prometheus::Renderer2D::DrawRotatedQuad({ -2.0f, -0.5f }, { 1.0f, 0.7f }, glm::radians(45.0f), { 0.6f, 0.1f, 0.8f, 1.0f });
		Prometheus::Renderer2D::EndScene();
	}
	
}

void Sandbox2D::OnImGuiRender()
{
	PM_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Prometheus::Event& e)
{
	m_CameraController.OnEvent(e);
}
