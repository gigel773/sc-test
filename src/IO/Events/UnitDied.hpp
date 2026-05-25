#pragma once

#include <cstdint>
#include <string>

namespace sw::io
{
	struct UnitDied
	{
		constexpr static std::string_view Name = "UNIT_DIED";

		uint32_t unitId{};

		explicit UnitDied(const core::Event& event)
		{
			unitId = std::stoi(event.attributes.at("unitId"));
		}

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
		}
	};
}
