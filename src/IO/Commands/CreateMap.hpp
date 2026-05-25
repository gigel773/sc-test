#pragma once

#include <Interfaces/Commands.hpp>
#include <Map.hpp>
#include <Util/Factories.hpp>
#include <cstdint>
#include <iosfwd>

namespace sw::io
{
	struct CreateMap final : public core::ICommand
	{
		constexpr static std::string_view Name = "CREATE_MAP";

		uint32_t width{};
		uint32_t height{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("width", width);
			visitor.visit("height", height);
		}

		void apply() override
		{
			const auto map = core::makeMap(width, height);

			core::Engine::instance().setMap(map);
		}
	};
}
