#pragma once

#include "Loggable.hpp"

#include <memory>

namespace sw::core
{
	class IBehavior : public ILoggable
	{
	public:
		using Ptr = std::shared_ptr<IBehavior>;

		IBehavior() = default;
		~IBehavior() override = default;

		[[nodiscard]]
		virtual uint32_t ownerId() const
			= 0;

		[[nodiscard]]
		virtual IAction::Ptr nextAction() const
			= 0;

		[[nodiscard]]
		virtual bool isFinished() const
			= 0;

		[[nodiscard]]
		virtual bool succeed() const
			= 0;
	};
}
