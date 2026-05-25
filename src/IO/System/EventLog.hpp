#pragma once

#include "Events/MapCreated.hpp"
#include "Events/MarchEnded.hpp"
#include "Events/MarchStarted.hpp"
#include "Events/UnitAttacked.hpp"
#include "Events/UnitDied.hpp"
#include "Events/UnitMoved.hpp"
#include "Events/UnitSpawned.hpp"
#include "details/PrintFieldVisitor.hpp"

#include <Interfaces/Events.hpp>
#include <cstdint>
#include <iostream>
#include <typeindex>
#include <unordered_map>

namespace sw
{
	class EventLog final : public core::IEventLog
	{
	public:
		template <class TEvent>
		void log(const uint64_t tick, TEvent&& event)
		{
			std::cout << "[" << tick << "] " << TEvent::Name << " ";
			PrintFieldVisitor visitor(std::cout);
			event.visit(visitor);
			std::cout << std::endl;
		}

		void log(const core::Event event) override
		{
			if (event.name == "Attack")
			{
				log(event.tick, io::UnitAttacked(event));
			}
			else if (event.name == "Move")
			{
				log(event.tick, io::UnitMoved(event));
			}
			else if (event.name == "Map")
			{
				log(event.tick, io::MapCreated(event));
			}
			else if (event.name == "Die")
			{
				log(event.tick, io::UnitDied(event));
			}
			else if (event.name == "Spawn")
			{
				log(event.tick, io::UnitSpawned(event));
			}
			else if (event.name == "MarchStarted")
			{
				log(event.tick, io::MarchStarted(event));
			}
			else if (event.name == "MarchEnded")
			{
				log(event.tick, io::MarchEnded(event));
			}
		}
	};
}
