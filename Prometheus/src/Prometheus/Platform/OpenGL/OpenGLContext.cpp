#include "pmpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Prometheus {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		PM_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PM_CORE_ASSERT(status, "Failed to initialize Glad!");

		PM_CORE_INFO("OpenGL Info:");
		PM_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		PM_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		PM_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}