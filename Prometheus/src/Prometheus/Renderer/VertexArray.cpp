#include "pmpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Prometheus/Platform/OpenGL/OpenGLVertexArray.h"

namespace Prometheus {
	
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		PM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLVertexArray();
		}

		PM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}