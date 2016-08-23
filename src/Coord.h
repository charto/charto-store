#pragma once

#include "nbind/api.h"

namespace charto {

// Coordinate pair.

template <typename Unit>
class Coord {

public:

	explicit Coord(Unit x = 0, Unit y = 0) : x(x), y(y) {}

	bool operator==(const Coord &other) const {
		return(x == other.x && y == other.y);
	}

	void toJS(nbind::cbOutput output) const { output(x, y); }

	union {
		Unit x;
		Unit lat;
	};

	union {
		Unit y;
		Unit lon;
	};
};

} // namespace
