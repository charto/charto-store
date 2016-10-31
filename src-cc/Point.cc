// This file is part of charto-store, copyright (C) 2016 BusFaster Ltd.
// Released under the MIT license, see LICENSE.

#include <cstdint>

#include "Point.h"

using namespace charto;

template class charto::Point<double>;
template class charto::Point<uint32_t>;

#include "nbind/nbind.h"

NBIND_CLASS(Point<double>, Point) {
	construct<double, double>();

	getter(getXY, "xy");
}

NBIND_CLASS(Point<uint32_t>, PointInt) {
	construct<uint32_t, uint32_t>();

	getter(getXY, "xy");
}
