#include "Map.hpp"

#include "Interfaces/Object.hpp"

#include <Engine.hpp>
#include <Util/Verify.hpp>
#include <algorithm>
#include <cstdint>
#include <ranges>
#include <string>

namespace sw::core
{
	using namespace std::string_literals;

	Map::Map(const uint32_t width, const uint32_t height)
	{
		const auto row = std::vector(width, std::vector<IObject::Ptr>());
		_map = MapType(height, row);
	}

	uint32_t Map::width() const
	{
		return _map.front().size();
	}

	uint32_t Map::height() const
	{
		return _map.size();
	}

	IObject::Ptr Map::remove(const uint32_t id)
	{
		const auto it = _idToPosition.find(id);
		SW_CORE_VERIFY_MSG(it != _idToPosition.end(), "unit not found for id: "s + std::to_string(id));

		const auto position = it->second;
		auto& candidates = _map[position.y][position.x];
		const auto result
			= std::find_if(candidates.begin(), candidates.end(), [id](auto obj) -> bool { return id == obj->id(); });
		SW_CORE_VERIFY_MSG(result != candidates.end(), "unit id is not found: "s + std::to_string(id));

		auto object = *result;
		candidates.erase(result);
		_idToPosition.erase(id);

		return std::move(object);
	}

	void Map::emplace(IObject::Ptr object, const Position& position)
	{
		const auto registry = Engine::instance().objectRegistry();
		SW_CORE_VERIFY_MSG(registry->hasObject(object->id()), "object should be registered before placing");

		auto& candidates = _map[position.y][position.x];
		for (auto&& candidate : candidates)
		{
			const auto candidatePosition = _idToPosition[candidate->id()];
			SW_CORE_VERIFY_MSG(!doesCollide(position.layer, candidatePosition.layer), "place is already taken");
		}

		_idToPosition[object->id()] = position;
		candidates.emplace_back(std::move(object));
	}

	IObject::Ptr Map::access(const uint32_t id)
	{
		const auto it = _idToPosition.find(id);
		SW_CORE_VERIFY_MSG(it != _idToPosition.end(), "unit not found for id: "s + std::to_string(id));

		const auto position = it->second;
		auto& candidates = _map[position.y][position.x];
		const auto result
			= std::find_if(candidates.begin(), candidates.end(), [id](auto obj) -> bool { return id == obj->id(); });
		SW_CORE_VERIFY_MSG(result != candidates.end(), "unit id is not found: "s + std::to_string(id));

		return *result;
	}

	std::vector<IObject::Ptr> Map::objectsInRange(
		const Position& start, const std::pair<uint32_t, uint32_t>& boundaries, const Layer layerMask)
	{
		std::vector<IObject::Ptr> result;

		for (auto& [id, position] : _idToPosition)
		{
			const auto range = start.distanceTo(position);
			if (range < boundaries.first || range > boundaries.second)
			{
				continue;
			}

			if (!doesCollide(position.layer, layerMask))
			{
				continue;
			}

			result.emplace_back(access(id));
		}

		return result;
	}

	IMap::Position Map::positionFor(const uint32_t id) const
	{
		const auto it = _idToPosition.find(id);
		SW_CORE_VERIFY_MSG(it != _idToPosition.end(), "unit not found for id: "s + std::to_string(id));

		return it->second;
	}

	std::vector<IMap::Position> Map::freePositionsAround(const Position& start, const Layer layerMask)
	{
		const std::vector candidates
			= {Position(start.x - 1, start.y - 1, layerMask),
			   Position(start.x, start.y - 1, layerMask),
			   Position(start.x + 1, start.y - 1, layerMask),
			   Position(start.x - 1, start.y, layerMask),
			   Position(start.x + 1, start.y, layerMask),
			   Position(start.x - 1, start.y + 1, layerMask),
			   Position(start.x, start.y + 1, layerMask),
			   Position(start.x + 1, start.y + 1, layerMask)};

		std::vector<Position> freePositions;

		for (const auto& candidate : candidates)
		{
			if (candidate.isWithinBounds(width(), height()) && isFree(candidate))
			{
				freePositions.push_back(candidate);
			}
		}

		return freePositions;
	}

	bool Map::doesCollide(Layer a, Layer b)
	{
		const auto result = (static_cast<uint8_t>(a) & static_cast<uint8_t>(b)) != 0;

		return result;
	}

	bool Map::isFree(const Position& position)
	{
		for (auto&& candidate : _map[position.y][position.x])
		{
			const auto candidatePosition = _idToPosition[candidate->id()];
			if (doesCollide(position.layer, candidatePosition.layer))
			{
				return false;
			}
		}

		return true;
	}
}
