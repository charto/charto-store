// This file is part of charto-store, copyright (C) 2016 BusFaster Ltd.
// Released under the MIT license, see LICENSE.

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
