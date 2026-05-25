#pragma once

#include "Interfaces/Action.hpp"
#include "Interfaces/Events.hpp"

namespace sw::core::decorators
{

	class ActionLogger final : public IAction
	{
	public:
		explicit ActionLogger(IEventLog::Ptr logger, Ptr impl);

		[[nodiscard]]
		std::string name() const override;

		[[nodiscard]]
		std::unordered_map<std::string, std::string> attributes() override;

		[[nodiscard]]
		Ptr execute(uint32_t tick) override;

		[[nodiscard]]
		uint32_t targetTick() const override;

	private:
		IEventLog::Ptr _logger;
		Ptr _impl;
	};

}
