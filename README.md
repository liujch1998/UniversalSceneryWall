# UniversalSceneryWall

This software generates specification of a random scenery wall used in Universal Studio (Beijing). 

## Usage

### Input

* File `input/wall.in` specifies the wall. Format: 
	* Line 1: two real numbers, for the width and height of the wall, separated by a space. 
	* Line 2: one integer, for the number of layers of boards. 
	* Line 3: two real numbers, for the minimum area coverage per layer and the maximum area overlap for each pair of boards, respectively; separated by a space. 
* File `input/board.in` specifies the boards. Format: 
	* Line 1: one integer, for the number of boards. 
	* For each board: 
		* Line 1: one integer, for the number of vertices of the shape. 
		* For each vertex, one line containing two real numbers, for the coordinate of the vertex relative to the center of the board. The vertices must be give in **CLOCKWISE** sequence. 

### Usage

run `./UniversalSceneryWall` to generate specification of scenery wall
run `python src/visual.py` to generate visualization of the obtained scenery wall

### Output

* File `output/wall.out` specifies the layout of boards. Format: 
	* Line 1: one integer, for the total number of boards. 
	* Each subsequent line specifies a board: 
		* The first integer is the type index of the board. 
		* The second integer is the layer index. 
		* The third and fourth real numbers are the coordinates. 
		* The fifth real number is the counter-clockwise rotation in radius. 
* File `output/visual.out` specifies the coordinates of boards. Format: 
	* Line 1: two real numbers, for the width and height of the wall. 
	* Line 2: one integer, for the total number of boards. 
	* For each board: 
		* Line 1: one integer, for the layer index. 
		* Line 2: one integer, for the number of vertices of the shape. 
		* For each vertex, one line containing two real numbers, for the coordinate of the vertex on wall. The lower-left corner of the wall is (0,0). 

