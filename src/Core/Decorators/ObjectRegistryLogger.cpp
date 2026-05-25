#include "ObjectRegistryLogger.hpp"

#include <Engine.hpp>

namespace sw::core::decorators
{
	ObjectRegistryLogger::ObjectRegistryLogger(IEventLog::Ptr logger, Ptr impl) :
			_logger(std::move(logger)),
			_impl(std::move(impl))
	{
		// Empty constructor
	}

	bool ObjectRegistryLogger::hasObject(const uint32_t id) const
	{
		return _impl->hasObject(id);
	}

	void ObjectRegistryLogger::placeObject(IObject::Ptr object)
	{
		_impl->placeObject(std::move(object));
	}

	std::vector<IObject::Ptr> ObjectRegistryLogger::objects() const
	{
		return _impl->objects();
	}

	std::vector<IObject::Ptr> ObjectRegistryLogger::eraseDeadObjects()
	{
		const auto result = _impl->eraseDeadObjects();
		for (auto&& object : result)
		{
			_logger->log(Event{
				.tick = Engine::instance().tick(),
				.name = "Die",
				.attributes = {{"unitId", std::to_string(object->id())}}});
		}

		return result;
	}

}
