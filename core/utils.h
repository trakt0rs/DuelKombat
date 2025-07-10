#pragma once

#include <type_traits>

namespace Core {
	template<class T>
	struct Vec2 {
		static_assert(std::is_same_v<T, float> || std::is_same_v<T, int>, "Vec2 should be either float or int");
		T x = 0, y = 0;
		Vec2() = default;
		Vec2(T x, T y) : x(x), y(y) {}
	};

	using Vec2f = Vec2<float>;
	using Vec2i = Vec2<int>;
}