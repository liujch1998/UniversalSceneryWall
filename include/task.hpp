#pragma once

#include "geometry.hpp"

#include <string>
#include <vector>

class Result {
public:
	std::string ToString ();

public:
	int polygon_type;
	int layer_index;
	Vector2 position;
	double rotation;
};

class Task {
public:
	void Input ();
	void Generate ();
	void Output ();
	double CoverageFraction (int layer_index);

public:
	Vector2 frame_size;
	Polygon frame;
	int layer_cnt;
	std::vector<double> coverage_fraction_min;
	std::vector<double> overlap_fraction_max;
	std::vector<std::pair<double,double> > rotation_range;
	std::vector<std::pair<int,int> > polygon_range; // inclusive
	int polygon_cnt;
	std::vector<Polygon> polygons;

	std::vector<Result> results;
};

