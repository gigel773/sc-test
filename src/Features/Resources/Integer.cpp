#include "Integer.hpp"

#include <Util/Resource.hpp>

namespace sw::features::resources
{
	SW_CORE_REGISTER_RESOURCE(Integer);

	void Integer::setValue(const uint32_t value)
	{
		_value = value;
	}

	uint32_t Integer::value() const
	{
		return _value;
	}
}
