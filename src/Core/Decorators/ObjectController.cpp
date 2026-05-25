#include "ObjectController.hpp"

#include "OrderRegistry.hpp"

namespace sw::core::decorators
{
	ObjectController::ObjectController(Ptr impl) :
			_impl(std::move(impl))
	{
		// Empty constructor
	}

	uint32_t ObjectController::id() const
	{
		return _impl->id();
	}

	IAction::Ptr ObjectController::nextAction() const
	{
		// Check if we have to execute an order
		if (const auto order = core::OrderRegistry::instance().orderFor(_impl->id()); order != nullptr)
		{
			return order;
		}

		// Process user logic
		return _impl->nextAction();
	}

	IObject::ProcessingState ObjectController::processingState() const
	{
		return _impl->processingState();
	}

	std::string ObjectController::type() const
	{
		return _impl->type();
	}
}
