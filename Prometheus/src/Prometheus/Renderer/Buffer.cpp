#include "pmpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Prometheus/Platform/OpenGL/OpenGLBuffer.h"

namespace Prometheus {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) 
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    PM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
		}

		PM_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    PM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLIndexBuffer(indices, size);
		}

		PM_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}