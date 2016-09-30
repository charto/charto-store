// This file is part of charto-store, copyright (C) 2016 BusFaster Ltd.
// Released under the MIT license, see LICENSE.

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

	Unit getX() const { return(x); }
	Unit getY() const { return(y); }
	Unit getLat() const { return(lat); }
	Unit getLon() const { return(lon); }

	Unit setX(Unit x) { return(this->x = x); }
	Unit setY(Unit y) { return(this->y = y); }
	Unit setLat(Unit lat) { return(this->lat = lat); }
	Unit setLon(Unit lon) { return(this->lon = lon); }

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
