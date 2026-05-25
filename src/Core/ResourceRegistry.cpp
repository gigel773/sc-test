#include "ResourceRegistry.hpp"

#include <Util/Verify.hpp>

namespace sw::core
{
	using namespace std::string_literals;

	ResourceRegistry& ResourceRegistry::instance()
	{
		static ResourceRegistry registry;
		return registry;
	}
}
