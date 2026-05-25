#pragma once

#include "Interfaces/Events.hpp"
#include "ObjectRegistry.hpp"

namespace sw::core::decorators
{
	class ObjectRegistryLogger final : public IObjectRegistry
	{
	public:
		ObjectRegistryLogger(IEventLog::Ptr logger, Ptr impl);

		[[nodiscard]]
		bool hasObject(uint32_t id) const override;

		void placeObject(IObject::Ptr object) override;

		[[nodiscard]]
		std::vector<IObject::Ptr> objects() const override;

		[[nodiscard]]
		std::vector<IObject::Ptr> eraseDeadObjects() override;

	private:
		IEventLog::Ptr _logger;
		Ptr _impl;
	};
}
