#include "EventProducer.hpp"

namespace sw::io
{
	core::ICommand::Ptr EventProducer::next()
	{
		auto next = _commands.front();
		_commands.pop();

		return next;
	}

	bool EventProducer::hasMore()
	{
		return !_commands.empty();
	}

	void EventProducer::append(sw::core::ICommand::Ptr command)
	{
		_commands.push(std::move(command));
	}
}
