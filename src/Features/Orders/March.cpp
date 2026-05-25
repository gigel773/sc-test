#include "March.hpp"

#include <Actions/Move.hpp>
#include <Engine.hpp>
#include <Util/Factories.hpp>
#include <algorithm>

namespace sw::features::orders
{
	March::March(const uint32_t targetId, const core::IMap::Position& target) :
			_targetId(targetId),
			_target(target)
	{
		// Empty constructor
	}

	std::string March::name() const
	{
		return isFinished() ? "MarchEnded" : "MarchStarted";
	}

	std::unordered_map<std::string, std::string> March::attributes()
	{
		const auto position = core::Engine::instance().map()->positionFor(_targetId);
		auto result = std::unordered_map<std::string, std::string>();

		return {
			{"unitId", std::to_string(_targetId)},
			{"x", std::to_string(position.x)},
			{"y", std::to_string(position.y)},
			{"targetX", std::to_string(_target.x)},
			{"targetY", std::to_string(_target.y)}};
	}

	uint32_t March::ownerId() const
	{
		return _targetId;
	}

	core::IAction::Ptr March::nextAction() const
	{
		// No movement as attack has priority
		if (isSurrounded() || hasTargets())
		{
			return nullptr;
		}

		const auto map = core::Engine::instance().map();
		const auto position = map->positionFor(_targetId);
		const auto freeSpots = map->freePositionsAround(position, core::IMap::Layer::Default);

		// Check if target is in free spots
		const auto it = std::find(freeSpots.begin(), freeSpots.end(), _target);
		if (it != freeSpots.end())
		{
			return core::makeAction<actions::Move>(_targetId, *it);
		}

		// Choose the best next move and return it
		const auto next = std::min_element(
			freeSpots.begin(),
			freeSpots.end(),
			[this](auto a, auto b) -> bool
			{
				const auto left = _target.distanceTo(a);
				const auto right = _target.distanceTo(b);

				return left < right;
			});

		return core::makeAction<actions::Move>(_targetId, *next);
	}

	bool March::isFinished() const
	{
		try
		{
			const auto map = core::Engine::instance().map();
			const auto position = map->positionFor(_targetId);
			return position == _target;
		}
		catch (...)
		{
			return true;
		}
	}

	bool March::succeed() const
	{
		try
		{
			const auto map = core::Engine::instance().map();
			const auto position = map->positionFor(_targetId);
			return position == _target;
		}
		catch (...)
		{
			return false;
		}
	}

	bool March::hasTargets() const
	{
		const auto map = core::Engine::instance().map();

		// Targets are only available for rangers
		if (const auto object = map->access(_targetId); object->type() != "Ranger")
		{
			return false;
		}

		const auto position = map->positionFor(_targetId);
		const auto targets = map->objectsInRange(position, std::make_pair(1, 5), core::IMap::Layer::Default);

		return !targets.empty();
	}

	bool March::isSurrounded() const
	{
		const auto map = core::Engine::instance().map();
		const auto position = map->positionFor(_targetId);
		const auto neighbours = map->objectsInRange(position, std::make_pair(1, 1), core::IMap::Layer::Default);

		return !neighbours.empty();
	}
}
