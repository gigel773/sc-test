#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace sw::core
{
	class ILoggable
	{
	public:
		using Ptr = std::shared_ptr<ILoggable>;

		ILoggable() = default;
		virtual ~ILoggable() = default;

		[[nodiscard]]
		virtual std::string name() const
			= 0;

		[[nodiscard]]
		virtual std::unordered_map<std::string, std::string> attributes()
			= 0;
	};
}
