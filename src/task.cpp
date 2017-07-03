#include "task.hpp"
#include "geometry.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

#define PI (4*atan(1))

std::string Result::ToString () {
	return 
		std::to_string(polygon_type) + " " + 
		std::to_string(layer_index) + " " + 
		position.ToString() + " " + 
		std::to_string(rotation);
}

void Task::Input () {
	std::ifstream in_wall("input/wall.in");
	std::ifstream in_board("input/board.in");
	in_wall >> frame_size.x >> frame_size.y;
	in_wall >> layer_cnt;
	in_wall >> coverage_fraction_min >> overlap_fraction_max;
	in_board >> polygon_cnt;
	for (int i = 0; i < polygon_cnt; i ++) {
		Polygon polygon;
		polygon.Input(in_board);
		polygons.push_back(polygon);
	}
	in_wall.close();
	in_board.close();
}

void Task::Generate () {
	results.clear();
	std::uniform_int_distribution<int> dist_t(0, polygon_cnt-1);
	std::uniform_real_distribution<double> dist_x(0.0, frame_size.x);
	std::uniform_real_distribution<double> dist_y(0.0, frame_size.y);
	std::uniform_real_distribution<double> dist_r(0.0, 2 * PI);
	std::default_random_engine engine(time(0));
	for (int layer_index = 0; layer_index < layer_cnt; layer_index ++) {
		while (CoverageFraction(layer_index) < coverage_fraction_min) {
			Result result;
			result.polygon_type = dist_t(engine);
			result.layer_index = layer_index;
			result.position.x = dist_x(engine);
			result.position.y = dist_y(engine);
			result.rotation = dist_r(engine);
			results.push_back(result);
		}
	}
}

void Task::Output () {
	std::ofstream out_wall("output/wall.out");
	for (Result &result : results) {
		out_wall << result.ToString() << std::endl;
	}
	out_wall.close();

	std::ofstream out_visual("output/visual.out");
	for (Result &result : results) {
		out_visual << result.layer_index << std::endl;
		polygons[result.polygon_type].Instantiate(result.position, result.rotation).Output(out_visual);
		out_visual << std::endl;
	}
	out_visual.close();
}

double Task::CoverageFraction (int layer_index) {
	double area_total = frame_size.x * frame_size.y;
	double area_cover = 0.0;
	for (Result &result : results) {
		if (result.layer_index == layer_index) {
			area_cover += polygons[result.polygon_type].Area();
		}
	}
	return area_cover / area_total;
}

