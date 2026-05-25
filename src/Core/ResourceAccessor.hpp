#pragma once

#include "Interfaces/Resource.hpp"
#include "Util/Verify.hpp"

#include <memory>
#include <string>
#include <unordered_map>

namespace sw::core
{

	class ResourceAccessor final
	{
	public:
		static ResourceAccessor& instance();

		template <class T>
		typename BaseResource<T>::Ptr access(const uint32_t id, const std::string& name)
		{
			using namespace std::string_literals;

			const auto resource = _resources[id].find(name);
			SW_CORE_VERIFY_MSG(resource != _resources[id].end(), "unable to find a resource with name: "s + name);

			const auto result = std::static_pointer_cast<BaseResource<T>>(resource->second);
			return result;
		}

		template <class T>
		void registerResourceFor(const uint32_t id, const std::string& name, typename BaseResource<T>::Ptr resource)
		{
			using namespace std::string_literals;

			const auto [_, inserted] = _resources[id].try_emplace(name, std::move(resource));
			SW_CORE_VERIFY_MSG(inserted, "resource with name already registered: "s + name);
		}

	protected:
		ResourceAccessor() = default;
		~ResourceAccessor() = default;

	private:
		using ResourceMapping = std::unordered_map<std::string, std::shared_ptr<void>>;

		std::unordered_map<uint32_t, ResourceMapping> _resources;
	};

}
