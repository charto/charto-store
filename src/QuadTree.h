#pragma once

#include "BBox.h"

namespace charto {

template <class Member>
class QuadTree {

public:

	typedef typename Member::Unit Unit;

	explicit QuadTree(const BBox<Unit> &bbox) : bbox(bbox) {}

private:

	Member *root;

	BBox<Unit> bbox;

};

} // namespace
