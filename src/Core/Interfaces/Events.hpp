#pragma once

#include <string>
#include <unordered_map>
#include <memory>

namespace sw::core
{
	struct Event {
		uint32_t tick;
		std::string name;
		std::unordered_map<std::string, std::string> attributes;
	};

	class IEventLog {
	public:
		using Ptr = std::shared_ptr<IEventLog>;

		IEventLog() = default;
		virtual ~IEventLog() = default;

		virtual void log(Event event) = 0;
	};
}
