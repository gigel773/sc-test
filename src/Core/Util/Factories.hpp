#pragma once

#include "Decorators/ActionLogger.hpp"
#include "Decorators/MapLogger.hpp"
#include "Decorators/ObjectController.hpp"
#include "Decorators/ObjectRegistryLogger.hpp"
#include "Engine.hpp"
#include "Interfaces/Object.hpp"
#include "Map.hpp"

namespace sw::core
{
	[[nodiscard]]
	inline IObjectRegistry::Ptr makeObjectRegistry()
	{
		IObjectRegistry::Ptr result = std::make_shared<ObjectRegistry>();
		if (auto logger = Engine::instance().logger(); logger != nullptr)
		{
			result = std::make_shared<decorators::ObjectRegistryLogger>(std::move(logger), std::move(result));
		}

		return result;
	}

	template <class T, class... Args>
		requires std::is_base_of_v<IAction, T>
	IAction::Ptr makeAction(Args... args)
	{
		IAction::Ptr result = std::make_shared<T>(args...);
		if (auto logger = Engine::instance().logger(); logger != nullptr)
		{
			result = std::make_shared<decorators::ActionLogger>(std::move(logger), std::move(result));
		}

		return result;
	}

	template <class T, class... Args>
		requires std::is_base_of_v<IObject, T>
	IObject::Ptr makeObject(Args... args)
	{
		IObject::Ptr result = std::make_shared<T>(args...);

		return std::make_shared<decorators::ObjectController>(std::move(result));
	}

	[[nodiscard]]
	inline IMap::Ptr makeMap(const uint32_t width, const uint32_t height)
	{
		IMap::Ptr result = std::make_shared<Map>(width, height);
		if (auto logger = Engine::instance().logger(); logger != nullptr)
		{
			result = std::make_shared<decorators::MapLogger>(std::move(logger), std::move(result));
		}

		return result;
	}
}
