#pragma once

#include "Coord.h"

namespace charto {

/*
	Only the southwest (or upper left, depending on how you imagine the
	coordinate system) corner and edges touching it belong to each box.
	This ensures that in a grid of bounding boxes, every point belongs
	to exactly one box. Diagram:

     ◌┈┈┈┈◌ ← ne
     ┃    ┊
     ┃    ┊   ul → ●━━━━◌
sw → ●━━━━◌        ┃    ┊
                   ┃    ┊
                   ◌┈┈┈┈◌ ← lr
*/

template <typename Unit>
class BBox {

public:

	explicit BBox(const Coord<Unit> &xy) : sw(xy), ne(xy) {}
	BBox(const Coord<Unit> &sw, const Coord<Unit> &ne) : sw(sw), ne(ne) {}
	BBox(Unit x1, Unit y1, Unit x2, Unit y2) : sw(x1, y1), ne(x2, y2) {}

	const Coord<Unit> &getSW() { return(sw); }
	const Coord<Unit> &getNE() const { return(ne); }

	double sqDistTo(Unit x, Unit y) const;
	double sqDistTo(const Coord<Unit> &xy) const {
		return(sqDistTo(xy.x, xy.y));
	};

	unsigned int getRegion(Unit x, Unit y) const;
	unsigned int getRegion(const Coord<Unit> &xy) const {
		return(getRegion(xy.x, xy.y));
	};

	// Bounding boxes touching each other are considered not to intersect.

	bool intersects(const BBox &other) const;
	bool containsX(const BBox &other) const;
	bool containsY(const BBox &other) const;
	bool contains(const BBox &other) const;

	bool contains(Unit x, Unit y) const {
		// x >= sw.x &&
		// y >= sw.y &&
		// x <  ne.x &&
		// y <  ne.y

		return(getRegion(x, y) == 0);
	}

	bool contains(const Coord<Unit> &xy) const {
		return(contains(xy.x, xy.y));
	}

	void extend(Unit x, Unit y);
	void extend(const Coord<Unit> &xy) { extend(xy.x, xy.y); }

private:

	union {
		Coord<Unit> sw;
		Coord<Unit> ul;
	};

	union {
		Coord<Unit> ne;
		Coord<Unit> lr;
	};

};

} // namespace
