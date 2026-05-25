#pragma once

#include "Object.hpp"

#include <cstdint>
#include <memory>
#include <vector>

namespace sw::core
{
	class IMap
	{
	public:
		using Ptr = std::shared_ptr<IMap>;

		enum class Layer : uint8_t
		{
			Default = 0b00000001,
			All = 0b11111111
		};

		struct Position
		{
			Position() = default;
			Position(const Position& other) = default;
			Position& operator=(const Position& other) = default;

			bool operator==(const Position&) const = default;

			Position(const uint32_t x, const uint32_t y, const Layer layer = Layer::Default) :
					x(x),
					y(y),
					layer(layer)
			{
				// Empty constructor
			}

			[[nodiscard]]
			int32_t distanceTo(const Position& other) const
			{
				return std::max(
					std::abs(static_cast<int32_t>(x) - static_cast<int32_t>(other.x)),
					std::abs(static_cast<int32_t>(y) - static_cast<int32_t>(other.y)));
			}

			[[nodiscard]]
			bool isWithinBounds(const uint32_t width, const uint32_t height) const
			{
				return x < width && y < height;
			}

			uint32_t x = 0;
			uint32_t y = 0;
			Layer layer = Layer::Default;
		};

		IMap() = default;
		virtual ~IMap() = default;

		[[nodiscard]]
		virtual uint32_t width() const
			= 0;

		[[nodiscard]]
		virtual uint32_t height() const
			= 0;

		[[nodiscard]]
		virtual IObject::Ptr remove(uint32_t id)
			= 0;

		virtual void emplace(IObject::Ptr object, const Position& position) = 0;

		[[nodiscard]]
		virtual IObject::Ptr access(uint32_t id)
			= 0;

		[[nodiscard]]
		virtual std::vector<IObject::Ptr> objectsInRange(
			const Position& start, const std::pair<uint32_t, uint32_t>& boundaries, Layer layerMask)
			= 0;

		[[nodiscard]]
		virtual Position positionFor(uint32_t id) const
			= 0;

		[[nodiscard]]
		virtual std::vector<Position> freePositionsAround(const Position& start, Layer layerMask)
			= 0;
	};
}
