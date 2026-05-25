#pragma once

#include <Interfaces/Action.hpp>

namespace sw::features::actions
{
	class Attack final : public core::IAction
	{
	public:
		Attack(uint32_t initiatorId, uint32_t targetId, uint32_t damage);

		Attack(uint32_t initiatorId, uint32_t targetId, uint32_t damage, uint32_t targetTick);

		[[nodiscard]]
		std::string name() const override;

		[[nodiscard]]
		std::unordered_map<std::string, std::string> attributes() override;

		[[nodiscard]]
		Ptr execute(uint32_t tick) override;

		[[nodiscard]]
		uint32_t targetTick() const override;

	private:
		uint32_t _targetTick;
		uint32_t _initiatorId = 0;
		uint32_t _targetId = 0;
		uint32_t _damage = 0;
	};
}
