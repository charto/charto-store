// This file is part of charto-store, copyright (C) 2016 BusFaster Ltd.
// Released under the MIT license, see LICENSE.

#include <cstdint>

#include "Coord.h"

using namespace charto;

template class charto::Coord<double>;
template class charto::Coord<uint32_t>;

#include "nbind/nbind.h"

NBIND_CLASS(Coord<double>, Coord) {
	construct<>();
	construct<double, double>();

	getset(getX, setX);
	getset(getY, setY);
	getset(getLat, setLat);
	getset(getLon, setLon);
}

NBIND_CLASS(Coord<uint32_t>, CoordInt) {
	construct<>();
	construct<uint32_t, uint32_t>();

	getset(getX, setX);
	getset(getY, setY);
	getset(getLat, setLat);
	getset(getLon, setLon);
}
