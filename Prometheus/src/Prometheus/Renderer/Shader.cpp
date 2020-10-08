#include "pmpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Prometheus/Platform/OpenGL/OpenGLShader.h"

namespace Prometheus {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:    PM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		PM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
