#include "Tile.h"
#include "QuadTree.h"

using namespace charto;

template class charto::QuadTree<Tile<double, double>>;
template class charto::QuadTree<Tile<uint32_t, uint16_t>>;

typedef QuadTree<Tile<double, double>> BigTree;
typedef QuadTree<Tile<uint32_t, uint16_t>> SmallTree;

#include "nbind/nbind.h"

NBIND_CLASS(BigTree, Tree) {}

NBIND_CLASS(SmallTree) {}
