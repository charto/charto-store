// This file is part of charto-store, copyright (C) 2016 BusFaster Ltd.
// Released under the MIT license, see LICENSE.

#pragma once

#include <cstdint>
#include <memory>
#include <array>

#include "BBox.h"

namespace charto {

struct TileFlags {
	uint32_t isLeaf: 1;
	uint32_t isPacked: 1;
};

enum class TileChildPos : uint32_t {
	SW = 0, SE = 1,
	NW = 2, NE = 3
};

inline TileChildPos operator+ (TileChildPos a, TileChildPos b) {
	return(static_cast<TileChildPos>(
		static_cast<uint32_t>(a) + static_cast<uint32_t>(b)
	));
}

inline TileChildPos operator- (TileChildPos a, TileChildPos b) {
	return(static_cast<TileChildPos>(
		static_cast<uint32_t>(a) - static_cast<uint32_t>(b)
	));
}

struct TileData {
//	Vector<path::NodeSeq::Part> seqList;
//	Vector<path::Node *> nodeList;
	uint32_t pointCount;
};

class TileBase {

public:

	bool isLeaf() const { return(flags.isLeaf); }

private:

	TileFlags flags;

};

template <typename BigUnit, typename SmallUnit>
class Tile : public TileBase {

public:

	typedef BigUnit Unit;
	typedef SmallUnit Small;

	Tile(const BBox<Unit> &bbox) : bbox(bbox) { assert(bbox.area() > 0); }
	Tile(BBox<Unit> &&bbox) : bbox(bbox) { assert(bbox.area() > 0); }

	~Tile() {
		if(!isLeafFlag) childList.~array();
	}

	const BBox<Unit> &getBounds() const { return(bbox); }

	BBox<Unit> getChildBounds(TileChildPos pos) const;

	TileChildPos getChildPosAt(Unit x, Unit y) const;

	Tile *operator[](TileChildPos pos) {
		if(!isLeaf()) return(nullptr);

		return(childList[static_cast<uint32_t>(pos)].get());
	}

private:

	BBox<Unit> bbox;

	union {
		std::array<std::unique_ptr<Tile>, 4> childList;
		TileData data;
	};

	bool isLeafFlag = true;

};

} // namespace
