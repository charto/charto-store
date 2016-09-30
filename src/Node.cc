// This file is part of charto-store, copyright (C) 2016 BusFaster Ltd.
// Released under the MIT license, see LICENSE.

#include <cstdint>

#include "Node.h"

using namespace charto;

template class charto::Node<double>;
template class charto::Node<uint32_t>;

#include "nbind/nbind.h"

NBIND_CLASS(Node<double>, Node) {
	construct<double, double>();

	getter(getXY, "xy");
}

NBIND_CLASS(Node<uint32_t>, NodeInt) {
	construct<uint32_t, uint32_t>();

	getter(getXY, "xy");
}
