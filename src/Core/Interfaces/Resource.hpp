#pragma once

#include <memory>

namespace sw::core
{
	template <class Derived>
	class BaseResource
	{
	public:
		using Ptr = std::shared_ptr<BaseResource>;
		using Type = Derived;

		[[nodiscard]]
		Derived* access()
		{
			return static_cast<Derived*>(this);
		}
	};
}
