#include "MapLogger.hpp"

#include <Engine.hpp>

namespace sw::core::decorators
{
	MapLogger::MapLogger(IEventLog::Ptr logger, Ptr impl) :
			_logger(std::move(logger)),
			_impl(std::move(impl))
	{
		// Empty constructor
	}

	uint32_t MapLogger::width() const
	{
		return _impl->width();
	}

	uint32_t MapLogger::height() const
	{
		return _impl->height();
	}

	IObject::Ptr MapLogger::remove(const uint32_t id)
	{
		return _impl->remove(id);
	}

	void MapLogger::emplace(const IObject::Ptr object, const Position& position)
	{
		_impl->emplace(object, position);

		// Check if object is placed at the first time
		if (!_placedCache.contains(object->id()))
		{
			_logger->log(Event{
				.tick = Engine::instance().tick(),
				.name = "Spawn",
				.attributes
				= {{"unitId", std::to_string(object->id())},
				   {"unitType", object->type()},
				   {"x", std::to_string(position.x)},
				   {"y", std::to_string(position.y)}}});

			_placedCache.emplace(object->id());
		}
	}

	IObject::Ptr MapLogger::access(const uint32_t id)
	{
		return _impl->access(id);
	}

	std::vector<IObject::Ptr> MapLogger::objectsInRange(
		const Position& start, const std::pair<uint32_t, uint32_t>& boundaries, const Layer layerMask)
	{
		return _impl->objectsInRange(start, boundaries, layerMask);
	}

	IMap::Position MapLogger::positionFor(const uint32_t id) const
	{
		return _impl->positionFor(id);
	}

	std::vector<IMap::Position> MapLogger::freePositionsAround(const Position& start, const Layer layerMask)
	{
		return _impl->freePositionsAround(start, layerMask);
	}
}
