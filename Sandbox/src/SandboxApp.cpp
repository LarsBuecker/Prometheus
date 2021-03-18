#include "Prometheus.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public Prometheus::Layer {
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, false)
	{
		m_VertexArray.reset(Prometheus::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Prometheus::Ref<Prometheus::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Prometheus::VertexBuffer::Create(vertices, sizeof(vertices)));
		Prometheus::BufferLayout layout = {
			{ Prometheus::ShaderDataType::Float3, "a_Position" },
			{ Prometheus::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Prometheus::Ref<Prometheus::IndexBuffer> indexBuffer;
		indexBuffer.reset(Prometheus::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Prometheus::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,	1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Prometheus::Ref<Prometheus::VertexBuffer> squareVB;
		squareVB.reset(Prometheus::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Prometheus::ShaderDataType::Float3, "a_Position" },
			{ Prometheus::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Prometheus::Ref<Prometheus::IndexBuffer> squareIB;
		squareIB.reset(Prometheus::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Prometheus::Shader::Create("shader" ,vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;

			uniform vec3 u_Color;			

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Prometheus::Shader::Create("flatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		m_TextureShader = Prometheus::Shader::Create("assets/shaders/Texture.glsl");
	
		m_Texture = Prometheus::Texture2D::Create("assets/textures/Checkerboard.png");
		m_FlameTexture = Prometheus::Texture2D::Create("assets/textures/FlameLogo.png");

		std::dynamic_pointer_cast<Prometheus::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Prometheus::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Prometheus::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		Prometheus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Prometheus::RenderCommand::Clear();

		Prometheus::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Prometheus::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Prometheus::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.12f, y * 0.12f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Prometheus::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Prometheus::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_FlameTexture->Bind();
		Prometheus::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		//Prometheus::Renderer::Submit(m_Shader, m_VertexArray);

		Prometheus::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Prometheus::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}

private:
	Prometheus::Ref<Prometheus::Shader> m_Shader;
	Prometheus::Ref<Prometheus::VertexArray> m_VertexArray;

	Prometheus::Ref<Prometheus::Shader> m_FlatColorShader, m_TextureShader;
	Prometheus::Ref<Prometheus::VertexArray> m_SquareVA;

	Prometheus::Ref<Prometheus::Texture2D> m_Texture, m_FlameTexture;

	Prometheus::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Prometheus::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

Prometheus::Application* Prometheus::CreateApplication() {
	return new Sandbox();
}