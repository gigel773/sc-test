#include "Attack.hpp"

#include <Engine.hpp>
#include <ResourceAccessor.hpp>
#include <Resources/Integer.hpp>

namespace sw::features::actions
{
	Attack::Attack(const uint32_t initiatorId, const uint32_t targetId, const uint32_t damage) :
			_targetTick(core::Engine::instance().tick()),
			_initiatorId(initiatorId),
			_targetId(targetId),
			_damage(damage)
	{
		// Empty constructor
	}

	Attack::Attack(
		const uint32_t initiatorId, const uint32_t targetId, const uint32_t damage, const uint32_t targetTick) :
			_targetTick(targetTick),
			_initiatorId(initiatorId),
			_targetId(targetId),
			_damage(damage)
	{
		// Empty constructor
	}

	std::string Attack::name() const
	{
		return "Attack";
	}

	std::unordered_map<std::string, std::string> Attack::attributes()
	{
		auto& accessor = core::ResourceAccessor::instance();
		const auto health = accessor.access<resources::Integer>(_targetId, "hp");

		return {
			{"attackerUnitId", std::to_string(_initiatorId)},
			{"targetUnitId", std::to_string(_targetId)},
			{"damage", std::to_string(_damage)},
			{"targetHp", std::to_string(health->access()->value())}};
	}

	core::IAction::Ptr Attack::execute([[maybe_unused]] const uint32_t tick)
	{
		auto& accessor = core::ResourceAccessor::instance();

		const auto hp = accessor.access<resources::Integer>(_targetId, "hp");

		const auto current = hp->access()->value();
		const auto next = _damage > current ? 0 : current - _damage;

		hp->access()->setValue(next);

		return nullptr;
	}

	uint32_t Attack::targetTick() const
	{
		return _targetTick;
	}
}
