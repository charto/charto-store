// This file is part of charto-store, copyright (C) 2016 BusFaster Ltd.
// Released under the MIT license, see LICENSE.

#pragma once

#include "Coord.h"

namespace charto {

template <typename Unit>
class Point {

public:

	Point(Unit x, Unit y) : xy(x, y) {}

	const Coord<Unit> &getXY() const { return(xy); }

protected:

	Coord<Unit> xy;
};

} // namespace
