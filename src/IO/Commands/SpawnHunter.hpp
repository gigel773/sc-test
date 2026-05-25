#pragma once

#include "Units/Ranger.hpp"

#include <Interfaces/Commands.hpp>
#include <cstdint>
#include <iosfwd>

namespace sw::io
{
	struct SpawnHunter final : core::ICommand
	{
		constexpr static std::string_view Name = "SPAWN_HUNTER";

		uint32_t unitId{};
		uint32_t x{};
		uint32_t y{};
		uint32_t hp{};
		uint32_t agility{};
		uint32_t strength{};
		uint32_t range{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("x", x);
			visitor.visit("y", y);
			visitor.visit("hp", hp);
			visitor.visit("agility", agility);
			visitor.visit("strength", strength);
			visitor.visit("range", range);
		}

		void apply() override
		{
			const auto map = core::Engine::instance().map();
			const auto registry = core::Engine::instance().objectRegistry();

			auto ranger = core::makeObject<features::units::Ranger>(unitId, hp, agility, strength, range);

			registry->placeObject(ranger);
			map->emplace(std::move(ranger), core::IMap::Position(x, y));
		}
	};
}
