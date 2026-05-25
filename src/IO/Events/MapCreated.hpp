#pragma once

#include <cstdint>

namespace sw::io
{
	struct MapCreated
	{
		constexpr static std::string_view Name = "MAP_CREATED";

		uint32_t width{};
		uint32_t height{};

		explicit MapCreated(const core::Event& event)
		{
			width = std::stoi(event.attributes.at("width"));
			height = std::stoi(event.attributes.at("height"));
		}

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("width", width);
			visitor.visit("height", height);
		}
	};
}
