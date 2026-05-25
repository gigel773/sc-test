#include "OrderRegistry.hpp"

#include <Engine.hpp>
#include <algorithm>
#include <functional>

namespace sw::core
{
	OrderRegistry& OrderRegistry::instance()
	{
		static OrderRegistry registry;
		return registry;
	}

	void OrderRegistry::emplaceOrder(IBehavior::Ptr order)
	{
		if (const auto logger = Engine::instance().logger(); logger != nullptr)
		{
			logger->log(
				Event{.tick = Engine::instance().tick(), .name = order->name(), .attributes = order->attributes()});
		}

		_registry[order->ownerId()].emplace_back(std::move(order));
	}

	IAction::Ptr OrderRegistry::orderFor(const uint32_t id) const
	{
		const auto it = _registry.find(id);
		if (it == _registry.end())
		{
			return nullptr;
		}

		const auto& orders = it->second;
		const auto next = std::find_if(
			orders.begin(), orders.end(), [](const IBehavior::Ptr& order) -> bool { return !order->isFinished(); });
		if (next == orders.end())
		{
			return nullptr;
		}

		return next->get()->nextAction();
	}

	void OrderRegistry::updateOrders()
	{
		for (auto& [id, orders] : _registry)
		{
			for (auto&& order : orders)
			{
				if (!order->succeed())
				{
					continue;
				}

				if (const auto logger = Engine::instance().logger(); logger != nullptr)
				{
					logger->log(Event{
						.tick = Engine::instance().tick(), .name = order->name(), .attributes = order->attributes()});
				}
			}

			std::erase_if(orders, std::mem_fn(&IBehavior::isFinished));
		}
	}
}
