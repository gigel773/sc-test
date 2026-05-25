#pragma once

#include "Interfaces/Map.hpp"
#include "Interfaces/Object.hpp"

#include <cstdint>
#include <unordered_map>
#include <vector>

namespace sw::core
{
	class Map final : public IMap
	{
	public:
		Map(uint32_t width, uint32_t height);
		~Map() override = default;

		[[nodiscard]]
		uint32_t width() const override;

		[[nodiscard]]
		uint32_t height() const override;

		IObject::Ptr remove(uint32_t id) override;

		void emplace(IObject::Ptr object, const Position& position) override;

		IObject::Ptr access(uint32_t id) override;

		[[nodiscard]]
		std::vector<IObject::Ptr> objectsInRange(
			const Position& start, const std::pair<uint32_t, uint32_t>& boundaries, Layer layerMask) override;

		[[nodiscard]]
		Position positionFor(uint32_t id) const override;

		[[nodiscard]]
		std::vector<Position> freePositionsAround(const Position& start, Layer layerMask) override;

	protected:
		static bool doesCollide(Layer a, Layer b);

		[[nodiscard]]
		bool isFree(const Position& position);

	private:
		using MapType = std::vector<std::vector<std::vector<IObject::Ptr>>>;

		MapType _map;
		std::unordered_map<uint32_t, Position> _idToPosition{};
	};
}
