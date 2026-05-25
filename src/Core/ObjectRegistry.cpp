#include "ObjectRegistry.hpp"

#include <Engine.hpp>
#include <Util/Verify.hpp>
#include <algorithm>
#include <string>

namespace sw::core
{
	bool ObjectRegistry::hasObject(const uint32_t id) const
	{
		const auto it
			= std::find_if(_objects.begin(), _objects.end(), [&id](auto&& obj) -> bool { return obj->id() == id; });

		return it != _objects.end();
	}

	void ObjectRegistry::placeObject(IObject::Ptr object)
	{
		using namespace std::string_literals;

		SW_CORE_FAIL_NULL(object);
		SW_CORE_VERIFY_MSG(
			!hasObject(object->id()), "object already exists in registry: "s + std::to_string(object->id()));

		_objects.emplace_back(std::move(object));
	}

	std::vector<IObject::Ptr> ObjectRegistry::objects() const
	{
		return _objects;
	}

	std::vector<IObject::Ptr> ObjectRegistry::eraseDeadObjects()
	{
		const auto map = Engine::instance().map();
		std::vector<IObject::Ptr> result;

		for (auto&& obj : _objects)
		{
			if (obj->processingState() == IObject::ProcessingState::Dead)
			{
				result.emplace_back(map->remove(obj->id()));
			}
		}

		std::erase_if(
			_objects,
			[](const IObject::Ptr& obj) -> bool { return obj->processingState() == IObject::ProcessingState::Dead; });

		return result;
	}
}
