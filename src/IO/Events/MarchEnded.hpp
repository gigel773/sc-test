#pragma once

#include <cstdint>

namespace sw::io
{
	struct MarchEnded
	{
		constexpr static std::string_view Name = "MARCH_ENDED";

		uint32_t unitId{};
		uint32_t x{};
		uint32_t y{};

		explicit MarchEnded(const core::Event& event)
		{
			unitId = std::stoi(event.attributes.at("unitId"));
			x = std::stoi(event.attributes.at("x"));
			y = std::stoi(event.attributes.at("y"));
		}

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("x", x);
			visitor.visit("y", y);
		}
	};
}
