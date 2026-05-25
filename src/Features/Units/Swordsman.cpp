#include "Swordsman.hpp"

#include <Actions/Attack.hpp>
#include <Actions/Move.hpp>
#include <Engine.hpp>
#include <OrderRegistry.hpp>
#include <ResourceRegistry.hpp>
#include <Util/Factories.hpp>
#include <Util/Random.hpp>
#include <Util/Verify.hpp>
#include <random>

namespace sw::features::units
{
	Swordsman::Swordsman(const uint32_t id, const uint32_t hp, const uint32_t strength) :
			_id(id)
	{
		const auto& resources = core::ResourceRegistry::instance();

		_hp = resources.create<resources::Integer>(_id, "hp");
		_strength = resources.create<resources::Integer>(_id, "strength");

		SW_CORE_FAIL_NULL(_hp);
		SW_CORE_FAIL_NULL(_strength);

		_hp->access()->setValue(hp);
		_strength->access()->setValue(strength);
	}

	uint32_t Swordsman::id() const
	{
		return _id;
	}

	core::IAction::Ptr Swordsman::nextAction() const
	{
		// Check whether we should attack
		if (const auto attack = attackFlow(); attack != nullptr)
		{
			return attack;
		}

		// Check whether we should move
		if (const auto move = moveFlow(); move != nullptr)
		{
			return move;
		}

		return nullptr;
	}

	core::IObject::ProcessingState Swordsman::processingState() const
	{
		const auto hp = _hp->access()->value();
		return hp == 0 ? ProcessingState::Dead : ProcessingState::Processing;
	}

	std::string Swordsman::type() const
	{
		return "Swordsman";
	}

	core::IAction::Ptr Swordsman::attackFlow() const
	{
		const auto map = core::Engine::instance().map();
		const auto position = map->positionFor(_id);
		const auto neighbours = map->objectsInRange(position, std::make_pair(1, 1), core::IMap::Layer::Default);

		if (neighbours.empty())
		{
			return nullptr;
		}

		const auto targetIdx = core::randomInRange(0, static_cast<int>(neighbours.size() - 1));
		const auto& target = neighbours[targetIdx];

		return core::makeAction<actions::Attack>(_id, target->id(), _strength->access()->value());
	}

	core::IAction::Ptr Swordsman::moveFlow() const
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
