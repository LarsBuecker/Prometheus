#pragma once

#include "Prometheus/Core/Core.h"
#include "Prometheus/Core/KeyCodes.h"
#include "Prometheus/Core/MouseButtonCodes.h"

namespace Prometheus {

	class Input {
	public:
		static bool IsKeyPressed(int keycode);

		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}