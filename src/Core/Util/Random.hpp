#pragma once

#include <random>

namespace sw::core
{
	inline int randomInRange(const int left, const int right)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(left, right);

		return dist(gen);
	}
}
