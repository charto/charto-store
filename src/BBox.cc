#include <cstdint>

#include "BBox.h"

using namespace charto;

template <typename Unit>
double BBox<Unit> :: sqDistTo(Unit x, Unit y) const {
	double dx = 0, dy = 0;

	if(x < sw.x) dx = x - sw.x;
	else if(x > ne.x) dx = x - ne.x;

	if(y < sw.y) dy = y - sw.y;
	else if(y >= ne.y) dy = y - ne.y;

	return(dx * dx + dy * dy);
}

/*
	The extended edges of the bounding box partition the coordinate system
	into 9 regions like this:

	ul / sw

	v               v
	1100 | 0100 | 0110
	-----+------+-----
	1000 | 0000 | 0010
	-----+------+-----
	1001 | 0001 | 0011<   lr / ne

	Result is a 4-bit code where each bit represents being on the outside of a
	particular edge. Points on edges are considered to belong to the region
	below or on the right side of them in this diagram.
*/

template <typename Unit>
unsigned int BBox<Unit> :: getRegion(Unit x, Unit y) const {
	return((
		((x < ul.x) << 3) |
		((y < ul.y) << 2) |
		((x < lr.x) << 1) |
		 (y < lr.y)
	) ^ 3);
}

// Integer version uses more bit twiddles to ensure it's branchless.

template <>
unsigned int BBox<uint32_t> :: getRegion(uint32_t x, uint32_t y) const {
	return((
		(((x - ul.x) >> 28) & 8) |
		(((y - ul.y) >> 29) & 4) |
		(((x - lr.x) >> 30) & 2) |
		 ((y - lr.y) >> 31)
	) ^ 3);
}

// Box edges or corners touching each other are considered not to intersect,
// because only the SW corner and edges touching it belong to each box.

template <typename Unit>
bool BBox<Unit> :: intersects(const BBox &other) const {
	return(
		   other.sw.x < ne.x
		&& other.sw.y < ne.y
		&& other.ne.x > sw.x
		&& other.ne.y > sw.y
	);
}

// Both bounding boxes must have nonzero width!
// Otherwise this may erroneously return true.

template <typename Unit>
bool BBox<Unit> :: containsX(const BBox &other) const {
	return(other.sw.x >= sw.x && other.ne.x <= ne.x);
}

// Both bounding boxes must have nonzero height!
// Otherwise this may erroneously return true.

template <typename Unit>
bool BBox<Unit> :: containsY(const BBox &other) const {
	return(other.sw.y >= sw.y && other.ne.y <= ne.y);
}

// Both bounding boxes must have nonzero width and height!
// Otherwise this may erroneously return true.

template <typename Unit>
bool BBox<Unit> :: contains(const BBox &other) const {
	return(containsX(other) && containsY(other));
}

template <typename Unit>
void BBox<Unit> :: extend(Unit x, Unit y) {
	if(x < sw.x) sw.x = x;
	if(y < sw.y) sw.y = y;
	if(x > ne.x) ne.x = x;
	if(y > ne.y) ne.y = y;
}

template class charto::BBox<double>;
template class charto::BBox<uint32_t>;

#include "nbind/nbind.h"

using namespace nbind;

NBIND_CLASS(BBox<double>, BBox) {
	construct<double, double, double, double>();

	getter(getSW);
	getter(getNE);

//	method(sqDistTo);
	method(getRegion, Overloaded<unsigned int (double, double) const>());

	method(intersects);
	method(contains, Overloaded<bool (const BBox<double> &) const>());

	method(extend, Overloaded<void (double, double)>());
}

NBIND_CLASS(BBox<uint32_t>, BBoxInt) {
	construct<uint32_t, uint32_t, uint32_t, uint32_t>();

	getter(getSW);
	getter(getNE);

//	method(sqDistTo);
	method(getRegion, Overloaded<unsigned int (uint32_t, uint32_t) const>());

	method(intersects);

	method(extend, Overloaded<void (uint32_t, uint32_t)>());
}