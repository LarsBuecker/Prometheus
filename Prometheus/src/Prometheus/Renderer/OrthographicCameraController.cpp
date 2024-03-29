#include "pmpch.h"
#include "Prometheus/Renderer/OrthographicCameraController.h"

#include "Prometheus/Core/Input.h"
#include "Prometheus/Core/KeyCodes.h"

namespace Prometheus {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		PM_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(PM_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(PM_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(PM_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(PM_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(PM_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;

			if (Input::IsKeyPressed(PM_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		PM_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(PM_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(PM_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
	}

	void OrthographicCameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		PM_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return true;
	}

	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		PM_PROFILE_FUNCTION();

		OnResize((float) e.GetWidth(), (float) e.GetHeight());
		return false;
	}

}