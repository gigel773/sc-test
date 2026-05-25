#include "Engine.hpp"

#include "OrderRegistry.hpp"

#include <Util/Verify.hpp>
#include <deque>
#include <stdexcept>

namespace sw::core
{
	Engine::Engine() = default;

	Engine& Engine::instance()
	{
		static Engine engine;
		return engine;
	}

	void Engine::initialize(ICommandProducer::Ptr producer)
	{
		while (producer->hasMore())
		{
			const auto next = producer->next();
			next->apply();
		}
	}

	void Engine::run()
	{
		SW_CORE_VERIFY_MSG(_map != nullptr, "map is not initialized");
		SW_CORE_VERIFY_MSG(_registry != nullptr, "registry is not initialized");

		while (!shouldStop())
		{
			const auto& planned = _plannedActions[_tick];
			std::deque actions(planned.begin(), planned.end());

			// Collect actions from board
			auto objects = _registry->objects();
			for (auto&& object : objects)
			{
				if (auto next = object->nextAction(); next != nullptr)
				{
					if (next->targetTick() == _tick)
					{
						actions.emplace_back(std::move(next));
					}
					else
					{
						_plannedActions[next->targetTick()].emplace_back(std::move(next));
					}
				}
			}

			// Check if there are no actions
			if (actions.empty())
			{
				break;
			}

			// Execute actions
			while (!actions.empty())
			{
				const auto next = actions.front();
				actions.pop_front();

				if (auto postAction = next->execute(_tick); postAction != nullptr)
				{
					if (postAction->targetTick() == _tick)
					{
						actions.emplace_back(std::move(postAction));
					}
					else
					{
						_plannedActions[postAction->targetTick()].emplace_back(std::move(postAction));
					}
				}
			}

			// Erase planned actions and move to next turn
			_plannedActions.erase(_tick);
			OrderRegistry::instance().updateOrders();
			std::ignore = _registry->eraseDeadObjects();

			++_tick;
		}
	}

	IMap::Ptr Engine::map() const
	{
		return _map;
	}

	void Engine::setMap(IMap::Ptr map)
	{
		if (_logger != nullptr)
		{
			const auto event = Event{
				.tick = _tick,
				.name = "Map",
				.attributes = {{"width", std::to_string(map->width())}, {"height", std::to_string(map->height())}}};

			_logger->log(event);
		}

		_map = std::move(map);
	}

	IEventLog::Ptr Engine::logger() const
	{
		return _logger;
	}

	void Engine::setLogger(IEventLog::Ptr logger)
	{
		_logger = std::move(logger);
	}

	IObjectRegistry::Ptr Engine::objectRegistry() const
	{
		return _registry;
	}

	void Engine::setObjectRegistry(IObjectRegistry::Ptr registry)
	{
		_registry = std::move(registry);
	}

	uint32_t Engine::tick() const
	{
		return _tick;
	}

	bool Engine::shouldStop() const
	{
		const auto& objects = _registry->objects();
		return objects.size() == 1;
	}

}
