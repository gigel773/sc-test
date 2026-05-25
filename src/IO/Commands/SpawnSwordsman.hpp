#pragma once

#include <Units/Swordsman.hpp>
#include <cstdint>
#include <iosfwd>

namespace sw::io
{
	struct SpawnSwordsman final : core::ICommand
	{
		constexpr static std::string_view Name = "SPAWN_SWORDSMAN";

		uint32_t unitId{};
		uint32_t x{};
		uint32_t y{};
		uint32_t hp{};
		uint32_t strength{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("x", x);
			visitor.visit("y", y);
			visitor.visit("hp", hp);
			visitor.visit("strength", strength);
		}

		void apply() override
		{
			const auto map = core::Engine::instance().map();
			const auto registry = core::Engine::instance().objectRegistry();

			auto swordsman = core::makeObject<features::units::Swordsman>(unitId, hp, strength);

			registry->placeObject(swordsman);
			map->emplace(std::move(swordsman), core::IMap::Position(x, y));
		}
	};
}
