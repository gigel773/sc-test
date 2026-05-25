#pragma once

#include <memory>

namespace sw::core
{
	class ICommand
	{
	public:
		using Ptr = std::shared_ptr<ICommand>;

		ICommand() = default;
		virtual ~ICommand() = default;

		virtual void apply() = 0;
	};

	class ICommandProducer
	{
	public:
		using Ptr = std::shared_ptr<ICommandProducer>;

		ICommandProducer() = default;
		virtual ~ICommandProducer() = default;

		[[nodiscard]]
		virtual ICommand::Ptr next()
			= 0;
		[[nodiscard]]
		virtual bool hasMore()
			= 0;
	};
}
