#pragma once

#include <cstdint>
#include <string>

namespace sw::io
{
	struct MarchStarted
	{
		constexpr static std::string_view Name = "MARCH_STARTED";

		uint32_t unitId{};
		uint32_t x{};
		uint32_t y{};
		uint32_t targetX{};
		uint32_t targetY{};

		explicit MarchStarted(const core::Event& event)
		{
			unitId = std::stoi(event.attributes.at("unitId"));
			x = std::stoi(event.attributes.at("x"));
			y = std::stoi(event.attributes.at("y"));
			targetX = std::stoi(event.attributes.at("targetX"));
			targetY = std::stoi(event.attributes.at("targetY"));
		}

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("x", x);
			visitor.visit("y", y);
			visitor.visit("targetX", targetX);
			visitor.visit("targetY", targetY);
		}
	};
}
