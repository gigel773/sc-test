#pragma once

#include "Resources/Integer.hpp"

#include <Interfaces/Object.hpp>

namespace sw::features::units
{
	class Swordsman final : public core::IObject
	{
	public:
		Swordsman(uint32_t id, uint32_t hp, uint32_t strength);

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
		core::IAction::Ptr attackFlow() const;
		[[nodiscard]]
		core::IAction::Ptr moveFlow() const;

	private:
		uint32_t _id;
		core::BaseResource<resources::Integer>::Ptr _hp;
		core::BaseResource<resources::Integer>::Ptr _strength;
	};
}  // features
