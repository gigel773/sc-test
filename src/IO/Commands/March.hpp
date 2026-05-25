#pragma once

#include "OrderRegistry.hpp"
#include "Orders/March.hpp"

#include <cstdint>

namespace sw::io
{
	struct March final : core::ICommand
	{
		constexpr static std::string_view Name = "MARCH";

		uint32_t unitId{};
		uint32_t targetX{};
		uint32_t targetY{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("targetX", targetX);
			visitor.visit("targetY", targetY);
		}

		void apply() override
		{
			auto& orders = core::OrderRegistry::instance();
			auto order = std::make_shared<features::orders::March>(unitId, core::IMap::Position(targetX, targetY));

			orders.emplaceOrder(std::move(order));
		}
	};
}
