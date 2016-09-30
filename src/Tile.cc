#include "Tile.h"

using namespace charto;

template <typename BigUnit, typename SmallUnit>
BBox<BigUnit> Tile<BigUnit, SmallUnit> :: getChildBounds(TileChildPos pos) const {
	const BBox<Unit> &bboxChild = getBounds();
	const Coord<Unit> &xy1 = bboxChild.getSW();
	const Coord<Unit> &xy2 = bboxChild.getNE();
	Coord<Unit> center = bboxChild.getCenter();

	switch(pos) {
		case TileChildPos::SW: return(BBox<Unit>(xy1, center));
		case TileChildPos::SE: return(BBox<Unit>(xy1.x, center.y, center.x, xy2.y));
		case TileChildPos::NW: return(BBox<Unit>(center.x, xy1.y, xy2.x, center.y));
		case TileChildPos::NE: return(BBox<Unit>(center, xy2));
	}
}

template <typename BigUnit, typename SmallUnit>
TileChildPos Tile<BigUnit, SmallUnit> :: getChildPosAt(Unit x, Unit y) const {
	Coord<Unit> center = bbox.getCenter();
	TileChildPos childPos;

	if(x >= center.x) childPos = TileChildPos::NW;
	else childPos = TileChildPos::SW;

	if(y >= center.y) childPos = childPos + (TileChildPos::SE - TileChildPos::SW);

	return(static_cast<TileChildPos>(childPos));
}


template class charto::Tile<double, double>;
template class charto::Tile<uint32_t, uint16_t>;

typedef Tile<double, double> BigTile;
typedef Tile<uint32_t, uint16_t> SmallTile;

#include "nbind/nbind.h"

NBIND_CLASS(BigTile, Tile) {}

NBIND_CLASS(SmallTile) {}
