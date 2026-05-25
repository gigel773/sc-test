#pragma once

#include "Interfaces/Action.hpp"
#include "Interfaces/Behavior.hpp"
#include "Interfaces/Object.hpp"

#include <deque>
#include <unordered_map>

namespace sw::core
{
	class OrderRegistry final
	{
		friend class Engine;

	public:
		static OrderRegistry& instance();

		void emplaceOrder(IBehavior::Ptr order);

		IAction::Ptr orderFor(uint32_t id) const;

	protected:
		OrderRegistry() = default;
		~OrderRegistry() = default;

		void updateOrders();

	private:
		using OrdersMap = std::unordered_map<uint32_t, std::deque<IBehavior::Ptr>>;

		OrdersMap _registry;
	};
}
