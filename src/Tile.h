#pragma once

#include <cstdint>

namespace charto {

struct TileFlags {
	unsigned int isLeaf: 1;
	unsigned int isPacked: 1;
};

enum class TileChildPos : unsigned int {
	SW = 0, SE = 1,
	NW = 2, NE = 3
};

struct TileData {
//	Vector<path::NodeSeq::Part> seqList;
//	Vector<path::Node *> nodeList;
	uint32_t pointCount;
};

class TileBase {

public:

	bool isLeaf() const { return(flags.isLeaf); }

	TileChildPos getChildPosAt(double x, double y);

private:

	TileFlags flags;

};

template <typename BigUnit, typename SmallUnit>
class Tile : public TileBase {

public:

	typedef BigUnit Unit;
	typedef SmallUnit Small;

	const BBox<Unit> &getBounds() const { return(bbox); }

	BBox<Unit> getChildBounds(TileChildPos pos) const;

	Tile *operator[](TileChildPos pos) {
		if(!isLeaf()) return(nullptr);

		return(childList[static_cast<unsigned int>(pos)]);
	}

private:

	BBox<Unit> bbox;

	union {
		Tile *childList[4];
		TileData data;
	};

	bool isLeafFlag = true;

};

} // namespace
