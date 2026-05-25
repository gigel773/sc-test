#pragma once

#include <cstdint>
#include <string>

namespace sw::io
{
	struct UnitSpawned
	{
		constexpr static std::string_view Name = "UNIT_SPAWNED";

		uint32_t unitId{};
		std::string unitType{};
		uint32_t x{};
		uint32_t y{};

		explicit UnitSpawned(const core::Event& event)
		{
			unitId = std::stoi(event.attributes.at("unitId"));
			unitType = event.attributes.at("unitType");
			x = std::stoi(event.attributes.at("x"));
			y = std::stoi(event.attributes.at("y"));
		}

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("unitType", unitType);
			visitor.visit("x", x);
			visitor.visit("y", y);
		}
	};
}
