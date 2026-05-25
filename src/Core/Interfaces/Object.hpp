#pragma once

#include "Action.hpp"

#include <memory>
#include <string>
#include <vector>

namespace sw::core
{
	class IObject
	{
	public:
		using Ptr = std::shared_ptr<IObject>;

		enum class ProcessingState : uint8_t
		{
			Processing,
			Dead
		};

		IObject() = default;
		virtual ~IObject() = default;

		[[nodiscard]]
		virtual uint32_t id() const
			= 0;

		[[nodiscard]]
		virtual IAction::Ptr nextAction() const
			= 0;

		[[nodiscard]]
		virtual ProcessingState processingState() const
			= 0;

		[[nodiscard]]
		virtual std::string type() const
			= 0;
	};

	class IObjectRegistry
	{
	public:
		using Ptr = std::shared_ptr<IObjectRegistry>;

		IObjectRegistry() = default;
		virtual ~IObjectRegistry() = default;

		[[nodiscard]]
		virtual bool hasObject(uint32_t id) const
			= 0;

		virtual void placeObject(IObject::Ptr object) = 0;

		[[nodiscard]]
		virtual std::vector<IObject::Ptr> objects() const
			= 0;

		[[nodiscard]]
		virtual std::vector<IObject::Ptr> eraseDeadObjects()
			= 0;
	};
}
