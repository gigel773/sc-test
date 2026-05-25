#pragma once

#include <cstdint>
#include <string>

namespace sw::io
{
	struct UnitAttacked
	{
		constexpr static std::string_view Name = "UNIT_ATTACKED";

		uint32_t attackerUnitId{};
		uint32_t targetUnitId{};
		uint32_t damage{};
		uint32_t targetHp{};

		explicit UnitAttacked(const core::Event& event)
		{
			attackerUnitId = std::stoi(event.attributes.at("attackerUnitId"));
			targetUnitId = std::stoi(event.attributes.at("targetUnitId"));
			damage = std::stoi(event.attributes.at("damage"));
			targetHp = std::stoi(event.attributes.at("targetHp"));
		}

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("attackerUnitId", attackerUnitId);
			visitor.visit("targetUnitId", targetUnitId);
			visitor.visit("damage", damage);
			visitor.visit("targetHp", targetHp);
		}
	};
}
