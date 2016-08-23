#include "Tile.h"

using namespace charto;

BBox<Big> Tile :: getChildBounds(TilePos pos) const {
	const BBox<double> &bboxChild = getBounds();
	const Coord<double> &xy1 = bboxChild.getSW();
	const Coord<double> &xy2 = bboxChild.getNE();
	Coord<double> center = bboxChild.getCenter();

	switch(pos) {
		case TilePos::SW: return(BBox<double>(xy1, center));
		case TilePos::SE: return(BBox<double>(xy1.x, center.y, center.x, xy2.y));
		case TilePos::NW: return(BBox<double>(center.x, xy1.y, xy2.x, center.y));
		case TilePos::NE: return(BBox<double>(center, xy2));
	}
}

TileChildPos TileBase :: getChildPosAt(double x, double y) {
	Coord<double> center = bbox.getCenter();
	unsigned int childPos;

    // TODO: Use bit twiddling to extract sign bits of x and y comparisons
    // avoiding all if statements?
    if(query.x>=xSplit) childPos=ChildPos::NW;
    else childPos=ChildPos::SW;

    if(query.y>=ySplit) util::EnumMath(&childPos)+=util::EnumMath(ChildPos::SE)-ChildPos::SW;

//  printf("Child %d\n",childPos);

    return(childPos);
}

template class charto::Tile<uint32_t, uint16_t>;
template class charto::Tile<double, double>;

#include "nbind/nbind.h"

NBIND_CLASS(Tile<double>, Tile) {
}
