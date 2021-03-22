#pragma once

// For use by Prometheus applications

#include "Prometheus/Core/Application.h"
#include "Prometheus/Core/Layer.h"
#include "Prometheus/Core/Log.h"

#include "Prometheus/Core/Timestep.h"

#include "Prometheus/Core/Input.h"
#include "Prometheus/Core/MouseButtonCodes.h"
#include "Prometheus/Core/KeyCodes.h"

#include "Prometheus/ImGui/ImGuiLayer.h"

// --- Renderer  --------------------------------
#include "Prometheus/Renderer/Renderer.h"
#include "Prometheus/Renderer/Renderer2D.h"
#include "Prometheus/Renderer/RenderCommand.h"

#include "Prometheus/Renderer/Buffer.h"
#include "Prometheus/Renderer/Shader.h"
#include "Prometheus/Renderer/Texture.h"
#include "Prometheus/Renderer/SubTexture2D.h"
#include "Prometheus/Renderer/VertexArray.h"

#include "Prometheus/Renderer/OrthographicCamera.h"
#include "Prometheus/Renderer/OrthographicCameraController.h"
// ---------------------------------------------