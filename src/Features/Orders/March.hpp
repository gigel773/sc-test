#pragma once

#include <Interfaces/Action.hpp>
#include <Interfaces/Behavior.hpp>
#include <Interfaces/Map.hpp>

namespace sw::features::orders
{
	class March final : public core::IBehavior
	{
	public:
		March(uint32_t targetId, const core::IMap::Position& target);

		[[nodiscard]]
		std::string name() const override;

		[[nodiscard]]
		std::unordered_map<std::string, std::string> attributes() override;

		[[nodiscard]]
		uint32_t ownerId() const override;

		[[nodiscard]]
		core::IAction::Ptr nextAction() const override;

		[[nodiscard]]
		bool isFinished() const override;

		[[nodiscard]]
		bool succeed() const override;

	protected:
		[[nodiscard]]
		bool hasTargets() const;

		[[nodiscard]]
		bool isSurrounded() const;

	private:
		uint32_t _targetId = 0;
		core::IMap::Position _target;
		core::IMap::Position _initialPosition;
	};
}
