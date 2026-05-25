#include "ResourceAccessor.hpp"

namespace sw::core
{
	ResourceAccessor& ResourceAccessor::instance()
	{
		static ResourceAccessor accessor;
		return accessor;
	}
}
