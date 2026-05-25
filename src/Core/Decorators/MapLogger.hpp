#pragma once

#include "Interfaces/Events.hpp"
#include "Interfaces/Map.hpp"

#include <unordered_set>

namespace sw::core::decorators
{
	class MapLogger final : public IMap
	{
	public:
		MapLogger(IEventLog::Ptr logger, Ptr impl);

		[[nodiscard]]
		uint32_t width() const override;

		[[nodiscard]]
		uint32_t height() const override;

		[[nodiscard]]
		IObject::Ptr remove(uint32_t id) override;

		void emplace(IObject::Ptr object, const Position& position) override;

		[[nodiscard]]
		IObject::Ptr access(uint32_t id) override;

		[[nodiscard]]
		std::vector<IObject::Ptr> objectsInRange(
			const Position& start, const std::pair<uint32_t, uint32_t>& boundaries, Layer layerMask) override;

		[[nodiscard]]
		Position positionFor(uint32_t id) const override;

		[[nodiscard]]
		std::vector<Position> freePositionsAround(const Position& start, Layer layerMask) override;

	private:
		std::unordered_set<uint32_t> _placedCache;

		IEventLog::Ptr _logger;
		Ptr _impl;
	};
}
