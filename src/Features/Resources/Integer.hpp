#pragma once

#include <Interfaces/Resource.hpp>

namespace sw::features::resources
{

	class Integer final : public core::BaseResource<Integer>
	{
	public:
		void setValue(uint32_t value);
		[[nodiscard]]
		uint32_t value() const;

	private:
		uint32_t _value = 0;
	};

}
