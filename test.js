var nbind = require('nbind');
var binding = nbind.init(__dirname);
var lib = binding.lib;

function Coord(x, y) {
	this.x = x;
	this.y = y;
}

Coord.prototype.fromJS = function(output) {
	output(this.x, this.y);
}

binding.bind('Coord', Coord);
 
lib.test();

var bbox = new lib.BBox(1, 2, 3, 4);
var bboxInt = new lib.BBoxInt(1, 2, 3, 4);

var x1 = bbox.SW.x;
var y1 = bbox.SW.y;
var x2 = bbox.NE.x;
var y2 = bbox.NE.y;

bbox.SW.constructor.prototype.toString = function() {
	return(this.x + ', ' + this.y);
}

console.log(x1);
console.log(y1);
console.log(x2);
console.log(y2);

// Test points intersect all regions, edge segments and edge intersections
// in the diagram on the right.

var testList = [
	[x1 - 1, y1 - 1, 12], [x1, y1 - 1, 4 ], [x1 + 1, y1 - 1, 4 ], [x2, y1 - 1,  6], [x2 + 1, y1 - 1, 6 ], // 1100 | 0100 | 0110
	[x1 - 1, y1,     8 ], [x1, y1,     0 ], [x1 + 1, y1,     0 ], [x2, y1,      2], [x2 + 1, y1,     2 ], // -----+------+-----
	[x1 - 1, y1 + 1, 8 ], [x1, y1 + 1, 0 ], [x1 + 1, y1 + 1, 0 ], [x2, y1 + 1,  2], [x2 + 1, y1 + 1, 2 ], // 1000 | 0000 | 0010
	[x1 - 1, y2,     9 ], [x1, y2,     1 ], [x1 + 1, y2,     1 ], [x2, y2,      3], [x2 + 1, y2,     3 ], // -----+------+-----
	[x1 - 1, y2 + 1, 9 ], [x1, y2 + 1, 1 ], [x1 + 1, y2 + 1, 1 ], [x2, y2 + 1,  3], [x2 + 1, y2 + 1, 3 ], // 1001 | 0001 | 0011
];

for(var num = 0; num < testList.length; ++num) {
	var xyr = testList[num];
	var x = xyr[0];
	var y = xyr[1];
	var r = xyr[2];

	if(bbox.getRegion(x, y) != r) console.error('ERROR ' + x + ' '  + y);
	if(bboxInt.getRegion(x, y) != r) console.error('ERROR ' + x + ' '  + y);
}

// console.log(bbox.sqDistTo(new lib.Coord(0, 0)));
console.log('' + bbox.SW);

bbox.extend(0, 0);

console.log('' + bbox.SW);
