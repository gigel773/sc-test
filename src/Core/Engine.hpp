#pragma once

#include "Interfaces/Commands.hpp"
#include "Interfaces/Events.hpp"
#include "Interfaces/Map.hpp"

#include <cstdint>
#include <unordered_map>
#include <vector>

namespace sw::core
{
	class Engine final
	{
	public:
		static Engine& instance();

		void initialize(ICommandProducer::Ptr producer);
		void run();

		[[nodiscard]]
		IMap::Ptr map() const;
		void setMap(IMap::Ptr map);

		[[nodiscard]]
		IEventLog::Ptr logger() const;
		void setLogger(IEventLog::Ptr logger);

		[[nodiscard]]
		IObjectRegistry::Ptr objectRegistry() const;
		void setObjectRegistry(IObjectRegistry::Ptr registry);

		[[nodiscard]]
		uint32_t tick() const;

	protected:
		Engine();
		~Engine() = default;

		bool shouldStop() const;

	private:
		uint32_t _tick{0};
		std::unordered_map<uint32_t, std::vector<IAction::Ptr>> _plannedActions;

		IMap::Ptr _map;
		IEventLog::Ptr _logger;
		IObjectRegistry::Ptr _registry;
	};
}
