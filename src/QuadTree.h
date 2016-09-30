#pragma once

#include "BBox.h"

namespace charto {

template <class Member>
class QuadTree {

public:

	typedef typename Member::Unit Unit;

	explicit QuadTree(const BBox<Unit> &bbox) : bbox(bbox), root(new Member(bbox)) {}

	explicit QuadTree(BBox<Unit> &&bbox) : bbox(bbox), root(new Member(bbox)) {}

private:

	BBox<Unit> bbox;

	std::unique_ptr<Member> root;

};

} // namespace
