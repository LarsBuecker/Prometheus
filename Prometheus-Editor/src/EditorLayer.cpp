#include "EditorLayer.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

EditorLayer::EditorLayer()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void EditorLayer::OnAttach()
{
	PM_PROFILE_FUNCTION();

	m_CheckerboardTexture = Prometheus::Texture2D::Create("assets/textures/Checkerboard.png");
	m_SpriteSheet = Prometheus::Texture2D::Create("assets/textures/RPGpack_sheet_2X.png");

	m_TextureBush = Prometheus::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 3 }, {1, 1}, {128, 128});

	Prometheus::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_Framebuffer = Prometheus::Framebuffer::Create(fbSpec);
}

void EditorLayer::OnDetach()
{
	PM_PROFILE_FUNCTION();

}

void EditorLayer::OnUpdate(Prometheus::Timestep ts)
{
	PM_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Prometheus::Renderer2D::ResetStats();
	{
		PM_PROFILE_SCOPE("Renderer Prep");
		m_Framebuffer->Bind();
		Prometheus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Prometheus::RenderCommand::Clear();
	}
	
	{

		PM_PROFILE_SCOPE("Renderer Draw");
		Prometheus::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Prometheus::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Prometheus::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Prometheus::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10, m_SquareColor);
		Prometheus::Renderer2D::DrawRotatedQuad({ -2.0f, -0.5f }, { 1.0f, 1.0f }, 45.0f, m_CheckerboardTexture, 5, { 0.6f, 0.1f, 0.8f, 1.0f });
		Prometheus::Renderer2D::EndScene();

		Prometheus::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.2f, (y + 5.0f) / 10.0f, 0.75f };
				Prometheus::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Prometheus::Renderer2D::EndScene();
		m_Framebuffer->Unbind();
#if 0
		Prometheus::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Prometheus::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.1f }, { 1.0f, 1.0f }, m_TextureBush);
		Prometheus::Renderer2D::EndScene();
#endif
	}
	
}

void EditorLayer::OnImGuiRender()
{
	PM_PROFILE_FUNCTION();

	static bool dockingEnabled = true;
	if (dockingEnabled)
	{
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Dockspace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit")) Prometheus::Application::Get().Close();
				ImGui::EndMenu();
			}
		}
		ImGui::EndMenuBar();
	}

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	auto stats = Prometheus::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("DrawCalls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("VertexCount: %d", stats.GetTotalVertexCount());
	ImGui::Text("IndexCount: %d", stats.GetTotalIndexCount());	
	ImGui::End();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	ImGui::Begin("Viewport");
	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	if (m_ViewportSize != *((glm::vec2*)&viewportPanelSize))
	{
		m_Framebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		m_CameraController.OnResize(viewportPanelSize.x, viewportPanelSize.y);
	}

	uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
	ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
	ImGui::End();
	ImGui::PopStyleVar();

	ImGui::End();
}

void EditorLayer::OnEvent(Prometheus::Event& e)
{
	m_CameraController.OnEvent(e);
}
