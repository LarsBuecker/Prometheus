#pragma once

#include "entt.hpp"

namespace Prometheus {

	class Scene
	{
	public:
		Scene();
		~Scene();
	private: 
		entt::registry m_Registry;
	};

}