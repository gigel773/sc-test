#include "Ranger.hpp"

#include "Actions/Attack.hpp"
#include "Actions/Move.hpp"
#include "OrderRegistry.hpp"

#include <ResourceRegistry.hpp>
#include <Util/Factories.hpp>
#include <Util/Random.hpp>

namespace sw::features::units
{
	Ranger::Ranger(
		const uint32_t id, const uint32_t hp, const uint32_t agility, const uint32_t strength, const uint32_t range) :
			_id(id)
	{
		const auto& resources = core::ResourceRegistry::instance();

		_hp = resources.create<resources::Integer>(_id, "hp");
		_agility = resources.create<resources::Integer>(_id, "agility");
		_strength = resources.create<resources::Integer>(_id, "strength");
		_range = resources.create<resources::Integer>(_id, "range");

		SW_CORE_FAIL_NULL(_hp);
		SW_CORE_FAIL_NULL(_agility);
		SW_CORE_FAIL_NULL(_strength);
		SW_CORE_FAIL_NULL(_range);

		_hp->access()->setValue(hp);
		_agility->access()->setValue(agility);
		_strength->access()->setValue(strength);
		_range->access()->setValue(range);
	}

	uint32_t Ranger::id() const
	{
		return _id;
	}

	core::IAction::Ptr Ranger::nextAction() const
	{
		// Check if we should shoot
		if (const auto shoot = shootFlow(); shoot != nullptr)
		{
			return shoot;
		}

		// Check if we should attack
		if (const auto attack = meleeAttackFlow(); attack != nullptr)
		{
			return attack;
		}

		// Check if we should move
		if (const auto move = moveFlow(); move != nullptr)
		{
			return move;
		}

		return nullptr;
	}

	core::IObject::ProcessingState Ranger::processingState() const
	{
		const auto hp = _hp->access()->value();
		return hp == 0 ? ProcessingState::Dead : ProcessingState::Processing;
	}

	std::string Ranger::type() const
	{
		return "Ranger";
	}

	core::IAction::Ptr Ranger::shootFlow() const
	{
		const auto map = core::Engine::instance().map();
		const auto position = map->positionFor(_id);
		const auto range = _range->access()->value();

		// Check if shooting is allowed
		const auto neighbours = map->objectsInRange(position, std::make_pair(1, 1), core::IMap::Layer::Default);
		if (!neighbours.empty())
		{
			return nullptr;
		}

		// Check if there are available targets
		const auto targets = map->objectsInRange(position, std::make_pair(2, range), core::IMap::Layer::Default);
		if (targets.empty())
		{
			return nullptr;
		}

		// Choose target and shoot
		const auto targetIdx = core::randomInRange(0, static_cast<int>(targets.size() - 1));

		return core::makeAction<actions::Attack>(_id, targets[targetIdx]->id(), _agility->access()->value());
	}

	core::IAction::Ptr Ranger::meleeAttackFlow() const
	{
		const auto map = core::Engine::instance().map();
		const auto position = map->positionFor(_id);

		// Check if there are targets for attack
		const auto targets = map->objectsInRange(position, std::make_pair(1, 1), core::IMap::Layer::Default);
		if (targets.empty())
		{
			return nullptr;
		}

		// Choose target and attack
		const auto targetIdx = core::randomInRange(0, static_cast<int>(targets.size() - 1));

		return core::makeAction<actions::Attack>(_id, targets[targetIdx]->id(), _strength->access()->value());
	}

	core::IAction::Ptr Ranger::moveFlow() const
	{
		const auto map = core::Engine::instance().map();
		const auto position = map->positionFor(_id);

		const auto freeSpots = map->freePositionsAround(position, core::IMap::Layer::Default);
		if (freeSpots.empty())
		{
			return nullptr;
		}

		const auto targetIdx = core::randomInRange(0, static_cast<int>(freeSpots.size() - 1));

		return core::makeAction<actions::Move>(_id, freeSpots[targetIdx]);
	}
}
