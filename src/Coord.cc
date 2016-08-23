#include <cstdint>

#include "Coord.h"

using namespace charto;

template class charto::Coord<double>;
template class charto::Coord<uint32_t>;

#include "nbind/nbind.h"

NBIND_CLASS(Coord<double>, Coord) {
	construct<double, double>();
}

NBIND_CLASS(Coord<uint32_t>, CoordInt) {
	construct<double, double>();
}
