#include "pmpch.h"
#include "RenderCommand.h"

#include "Prometheus/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Prometheus {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}