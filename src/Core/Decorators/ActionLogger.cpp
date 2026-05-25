#include "ActionLogger.hpp"

namespace sw::core::decorators
{
	ActionLogger::ActionLogger(IEventLog::Ptr logger, Ptr impl) :
			_logger(std::move(logger)),
			_impl(std::move(impl))
	{
		// Empty constructor
	}

	std::string ActionLogger::name() const
	{
		return _impl->name();
	}

	std::unordered_map<std::string, std::string> ActionLogger::attributes()
	{
		return _impl->attributes();
	}

	IAction::Ptr ActionLogger::execute(const uint32_t tick)
	{
		const auto result = _impl->execute(tick);

		_logger->log(Event{.tick = tick, .name = _impl->name(), .attributes = _impl->attributes()});

		return result;
	}

	uint32_t ActionLogger::targetTick() const
	{
		return _impl->targetTick();
	}
}
