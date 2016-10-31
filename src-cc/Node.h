// This file is part of charto-store, copyright (C) 2016 BusFaster Ltd.
// Released under the MIT license, see LICENSE.

#pragma once

#include "Point.h"

namespace charto {

template <typename Unit>
class Node : public Point<Unit> {

public:

	Node(Unit x, Unit y) : Point<Unit>(x, y) {}

};

} // namespace
