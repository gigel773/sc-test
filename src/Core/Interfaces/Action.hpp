#pragma once

#include "Loggable.hpp"

#include <memory>

namespace sw::core
{
	class IAction : public ILoggable
	{
	public:
		using Ptr = std::shared_ptr<IAction>;

		IAction() = default;
		~IAction() override = default;

		[[nodiscard]]
		virtual Ptr execute(uint32_t tick)
			= 0;

		[[nodiscard]]
		virtual uint32_t targetTick() const
			= 0;
	};
}
