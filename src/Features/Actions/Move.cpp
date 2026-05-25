#include "Move.hpp"

#include <Engine.hpp>

namespace sw::features::actions
{
	Move::Move(const uint32_t targetId, const core::IMap::Position& to) :
			_targetTick(core::Engine::instance().tick()),
			_targetId(targetId),
			_to(to)
	{
		// Empty constructor
	}

	Move::Move(const uint32_t targetId, const core::IMap::Position& to, const uint32_t targetTick) :
			_targetTick(targetTick),
			_targetId(targetId),
			_to(to)
	{
		// Empty constructor
	}

	std::string Move::name() const
	{
		return "Move";
	}

	std::unordered_map<std::string, std::string> Move::attributes()
	{
		return {{"unitId", std::to_string(_targetId)}, {"x", std::to_string(_to.x)}, {"y", std::to_string(_to.y)}};
	}

	core::IAction::Ptr Move::execute([[maybe_unused]] const uint32_t tick)
	{
		const auto map = core::Engine::instance().map();

		auto removed = map->remove(_targetId);
		map->emplace(std::move(removed), _to);

		return nullptr;
	}

	uint32_t Move::targetTick() const
	{
		return _targetTick;
	}
}
