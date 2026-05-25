#pragma once

#include <Interfaces/Action.hpp>
#include <Interfaces/Map.hpp>
#include <Interfaces/Object.hpp>

namespace sw::features::actions
{
	class Move final : public core::IAction
	{
	public:
		Move(uint32_t targetId, const core::IMap::Position& to);

		Move(uint32_t targetId, const core::IMap::Position& to, uint32_t targetTick);

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
		uint32_t _targetId;
		core::IMap::Position _to;
	};
}
