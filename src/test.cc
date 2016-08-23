#include "QuadTree.h"
#include "Tile.h"

using namespace charto;

void test() {
	BBox<double> bbox(0, 0, 1, 1);
	QuadTree<Tile<double, double>> tree(bbox);
}

#include "nbind/nbind.h"

NBIND_GLOBAL() {
	function(test);
}
