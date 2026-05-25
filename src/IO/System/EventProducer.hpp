#pragma once

#include <Interfaces/Commands.hpp>
#include <queue>

namespace sw::io
{
	class EventProducer final : public sw::core::ICommandProducer
	{
	public:
		EventProducer() = default;

		core::ICommand::Ptr next() override;

		bool hasMore() override;

		void append(core::ICommand::Ptr command);

	private:
		std::queue<core::ICommand::Ptr> _commands;
	};
}
