#pragma once

#include "Interfaces/Object.hpp"

#include <vector>

namespace sw::core
{
	class ObjectRegistry final : public IObjectRegistry
	{
	public:
		[[nodiscard]]
		bool hasObject(uint32_t id) const override;

		void placeObject(IObject::Ptr object) override;

		[[nodiscard]]
		std::vector<IObject::Ptr> objects() const override;

		[[nodiscard]]
		std::vector<IObject::Ptr> eraseDeadObjects() override;

	private:
		std::vector<IObject::Ptr> _objects{};
	};
}
