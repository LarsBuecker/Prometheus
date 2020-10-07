#include "Prometheus.h"

class ExampleLayer : public Prometheus::Layer {
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPostion(0.0f)
	{
		m_VertexArray.reset(Prometheus::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Prometheus::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Prometheus::VertexBuffer::Create(vertices, sizeof(vertices)));
		Prometheus::BufferLayout layout = {
			{ Prometheus::ShaderDataType::Float3, "a_Position" },
			{ Prometheus::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Prometheus::IndexBuffer> indexBuffer;
		indexBuffer.reset(Prometheus::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Prometheus::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Prometheus::VertexBuffer> squareVB;
		squareVB.reset(Prometheus::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Prometheus::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Prometheus::IndexBuffer> squareIB;
		squareIB.reset(Prometheus::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			uniform mat4 u_ViewProjection;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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

		m_Shader.reset(new Prometheus::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Prometheus::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate() override
	{
		if (Prometheus::Input::IsKeyPressed(PM_KEY_LEFT))
			m_CameraPostion.x -= m_CameraSpeed;

		if (Prometheus::Input::IsKeyPressed(PM_KEY_RIGHT))
			m_CameraPostion.x += m_CameraSpeed;

		if (Prometheus::Input::IsKeyPressed(PM_KEY_DOWN))
			m_CameraPostion.y -= m_CameraSpeed;

		if (Prometheus::Input::IsKeyPressed(PM_KEY_UP))
			m_CameraPostion.y += m_CameraSpeed;

		Prometheus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Prometheus::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPostion);
		m_Camera.SetRotation(0.0f);

		Prometheus::Renderer::BeginScene(m_Camera);

		Prometheus::Renderer::Submit(m_BlueShader, m_SquareVA);
		Prometheus::Renderer::Submit(m_Shader, m_VertexArray);

		Prometheus::Renderer::EndScene();
	}

	void OnEvent(Prometheus::Event& event) override
	{

	}

private:
	std::shared_ptr<Prometheus::Shader> m_Shader;
	std::shared_ptr<Prometheus::VertexArray> m_VertexArray;

	std::shared_ptr<Prometheus::Shader> m_BlueShader;
	std::shared_ptr<Prometheus::VertexArray> m_SquareVA;

	Prometheus::OrthograhicCamera m_Camera;
	glm::vec3 m_CameraPostion;
	float m_CameraSpeed = 0.1f;
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