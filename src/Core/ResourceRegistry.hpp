#pragma once

#include "Interfaces/Resource.hpp"
#include "Util/Verify.hpp"

#include <functional>
#include <typeindex>
#include <unordered_map>

namespace sw::core
{
	class ResourceRegistry final
	{
	public:
		using Ptr = std::shared_ptr<ResourceRegistry>;
		using FactoryMethod = std::function<std::shared_ptr<void>(uint32_t, const std::string&)>;

		static ResourceRegistry& instance();

		template <class T>
		typename BaseResource<T>::Ptr create(const uint32_t ownerId, const std::string& name) const
		{
			using namespace std::string_literals;

			const auto factory = _factories.find(std::type_index(typeid(T)));
			SW_CORE_VERIFY_MSG(
				factory != _factories.end(), "unable to find a factory method for: "s + typeid(T).name());

			const auto next = factory->second(ownerId, name);

			return std::static_pointer_cast<BaseResource<T>>(next);
		}

		template <class T>
		void registerResource(std::function<typename BaseResource<T>::Ptr(uint32_t, const std::string&)> fn)
		{
			using namespace std::string_literals;

			auto [_, inserted] = _factories.try_emplace(
				std::type_index(typeid(T)),
				[fn = std::move(fn)](const uint32_t id, const std::string& name) -> std::shared_ptr<void>
				{
					auto next = fn(id, name);
					return next;
				});
			SW_CORE_VERIFY_MSG(inserted, "resource type already registered: "s + typeid(T).name());
		}

	protected:
		ResourceRegistry() = default;
		~ResourceRegistry() = default;

	private:
		std::unordered_map<std::type_index, FactoryMethod> _factories{};
	};
}
