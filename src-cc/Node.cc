// This file is part of charto-store, copyright (C) 2016 BusFaster Ltd.
// Released under the MIT license, see LICENSE.

#include <cstdint>

#include "Node.h"

using namespace charto;

template class charto::Node<double>;
template class charto::Node<uint32_t>;

#include "nbind/nbind.h"

NBIND_CLASS(Node<double>, Node) {
	inherit(Point<double>);

	construct<double, double>();
}

NBIND_CLASS(Node<uint32_t>, NodeInt) {
	inherit(Point<uint32_t>);

	construct<uint32_t, uint32_t>();
}
