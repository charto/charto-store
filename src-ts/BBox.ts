// This file is part of charto-store, copyright (C) 2016 BusFaster Ltd.
// Released under the MIT license, see LICENSE.

import {Coord} from './Coord';

function assert(condition: Boolean) { if(!condition) throw(new Error('Assert failed')); }

export class BBox {

	constructor(sw: Coord, ne?: Coord);
	constructor(x1: number, y1: number);
	constructor(x1: number, y1: number, x2: number, y2: number);

	constructor(a: number | Coord, b?: number | Coord, x2?: number, y2?: number) {
		let x1: number;
		let y1: number;

		if(typeof(a) == 'number') {
			assert(typeof(b) == 'number');

			x1 = a;
			y1 = b as number;
		} else {
			({x: x1, y: y1} = a);

			if(b) {
				assert(typeof(b) != 'number');

				({x: x2, y: y2} = b as Coord);
			}
		}

		if(!x2 && x2 !== 0) x2 = x1;
		if(!y2 && y2 !== 0) y2 = y1;

		assert(x1 <= x2 && y1 <= y2);

		this.x1 = x1;
		this.y1 = y1;
		this.x2 = x2!;
		this.y2 = y2!;
	}

	sw() { return(new Coord(this.x1, this.y1)); }
	ul = this.sw;

	ne() { return(new Coord(this.x2, this.y2)); }
	lr = this.ne;

	sqDistTo(xy: Coord): number;
	sqDistTo(x: number, y: number): number;

	sqDistTo(a: number | Coord, y?: number) {
		let x: number;
		let dx = 0, dy = 0;

		if(typeof(a) == 'number') x = a;
		else ({x, y} = a);

		if(x < this.x1) dx = x - this.x1;
		else if(x > this.x2) dx = x - this.x2;

		if(y < this.y1) dy = y - this.y1;
		else if(y >= this.y2) dy = y - this.y2;

		return(dx * dx + dy * dy);
	}

	area() {
		return((this.x2 - this.x1) * (this.y2 - this.y1));
	}

	getCenter() {
		return(new Coord((this.x1 + this.x2) / 2, (this.y1 + this.y2) / 2));
	}

	getRegion(xy: Coord): number;
	getRegion(x: number, y: number): number;

	getRegion(a: number | Coord, y?: number) {
		let x: number;

		if(typeof(a) == 'number') x = a;
		else ({x, y} = a);

		return((
			(((x - this.x1) >>> 28) & 8) |
			(((y - this.y1) >>> 29) & 4) |
			(((x - this.x2) >>> 30) & 2) |
			 ((y - this.y2) >>> 31)
		) ^ 3);
	}

	/** Box edges or corners touching each other are considered not to intersect,
	  * because only the SW corner and edges touching it belong to each box. */

	intersects(other: BBox) {
		return(
			   other.x1 < this.x2
			&& other.y1 < this.y2
			&& other.x2 > this.x1
			&& other.y2 > this.y1
		);
	}

	containsX(other: BBox) {
		return(other.x1 >= this.x1 && other.x2 <= this.x2);
	}

	containsY(other: BBox) {
		return(other.y1 >= this.y1 && other.y2 <= this.y2);
	}

	contains(other: BBox): boolean;
	contains(xy: Coord): boolean;
	contains(x: number, y: number): boolean;

	contains(a: number | Coord | BBox, y?: number) {
		let x: number;

		if(typeof(a) == 'number') x = a;
		else if(a instanceof Coord) ({x, y} = a);
		else return(this.containsX(a) && this.containsY(a));

		return(this.getRegion(x, y!) == 0);
	}

	extend(xy: Coord): BBox;
	extend(x: number, y: number): BBox;

	extend(a: number | Coord, y?: number) {
		let x: number;

		if(typeof(a) == 'number') x = a;
		else ({x, y} = a);

		if(x < this.x1) this.x1 = x;
		if(y < this.y1) this.y1 = y!;
		if(x > this.x2) this.x2 = x;
		if(y > this.y2) this.y2 = y!;

		return(this);
	}

	x1: number;
	y1: number;

	x2: number;
	y2: number;

}
