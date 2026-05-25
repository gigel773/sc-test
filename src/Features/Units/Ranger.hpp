#pragma once

#include "Resources/Integer.hpp"

#include <Interfaces/Object.hpp>

namespace sw::features::units
{
	class Ranger final : public core::IObject
	{
	public:
		Ranger(uint32_t id, uint32_t hp, uint32_t agility, uint32_t strength, uint32_t range);

		[[nodiscard]]
		uint32_t id() const override;

		[[nodiscard]]
		core::IAction::Ptr nextAction() const override;

		[[nodiscard]]
		ProcessingState processingState() const override;

		[[nodiscard]]
		std::string type() const override;

	protected:
		[[nodiscard]]
		core::IAction::Ptr shootFlow() const;
		[[nodiscard]]
		core::IAction::Ptr meleeAttackFlow() const;
		[[nodiscard]]
		core::IAction::Ptr moveFlow() const;

	private:
		uint32_t _id;
		core::BaseResource<resources::Integer>::Ptr _hp;
		core::BaseResource<resources::Integer>::Ptr _agility;
		core::BaseResource<resources::Integer>::Ptr _strength;
		core::BaseResource<resources::Integer>::Ptr _range;
	};
}
