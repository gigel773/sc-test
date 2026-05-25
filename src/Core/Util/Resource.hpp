#pragma once

#include "ResourceAccessor.hpp"
#include "ResourceRegistry.hpp"

#define SW_CORE_REGISTER_RESOURCE(resourceType)                                                                        \
	static bool _registered_##resourceType = []() -> bool                                                              \
	{                                                                                                                  \
		sw::core::ResourceRegistry::instance().registerResource<resourceType>(                                         \
			[](const uint32_t id, const std::string& name) -> resourceType::Ptr                                        \
			{                                                                                                          \
				const auto result = std::make_shared<resourceType>();                                                  \
				sw::core::ResourceAccessor::instance().registerResourceFor<resourceType>(id, name, result);            \
				return result;                                                                                         \
			});                                                                                                        \
		return true;                                                                                                   \
	}();
