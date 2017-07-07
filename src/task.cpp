#include "task.hpp"
#include "geometry.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

#define PI (4*atan(1))
#define EPS 1e-2

std::string Result::ToString () {
	return 
		std::to_string(polygon_type) + " " + 
		std::to_string(layer_index) + " " + 
		position.ToString() + " " + 
		std::to_string(rotation);
}

void Task::Input () {
	std::ifstream in_wall("input/wall.in");
	in_wall >> frame_size.x >> frame_size.y;
	in_wall >> layer_cnt;
	std::vector<double> buf(6*layer_cnt);
	for (int i = 0; i < 6*layer_cnt; i ++) {
		in_wall >> buf[i];
	}
	in_wall.close();
	for (int i = 0; i < layer_cnt; i ++) {
		coverage_fraction_min.push_back(buf[6*i]);
		overlap_fraction_max.push_back(buf[6*i+1]);
		rotation_range.push_back({buf[6*i+2], buf[6*i+3]});
		polygon_range.push_back({(int)buf[6*i+4], (int)buf[6*i+5]});
	}
	std::vector<Vector2> frame_vertexs;
	Vector2 a(0, 0); frame_vertexs.push_back(a);
	Vector2 b(0, frame_size.y); frame_vertexs.push_back(b);
	Vector2 c(frame_size.x, frame_size.y); frame_vertexs.push_back(c);
	Vector2 d(frame_size.x, 0); frame_vertexs.push_back(d);
	frame = Polygon(frame_vertexs);
	
	std::ifstream in_board("input/board.in");
	in_board >> polygon_cnt;
	for (int i = 0; i < polygon_cnt; i ++) {
		Polygon polygon;
		polygon.Input(in_board);
		polygons.push_back(polygon);
	}
	in_board.close();
}

void Task::Generate () {
	std::default_random_engine engine(time(0));
	for (int layer_index = 0; layer_index < layer_cnt; layer_index ++) {
		std::uniform_int_distribution<int> dist_t(polygon_range[layer_index].first, polygon_range[layer_index].second);
		std::uniform_real_distribution<double> dist_x(0.0, frame_size.x);
		std::uniform_real_distribution<double> dist_y(0.0, frame_size.y);
		std::uniform_real_distribution<double> dist_r(rotation_range[layer_index].first, rotation_range[layer_index].second);
		while (CoverageFraction(layer_index) < coverage_fraction_min[layer_index]) {
			Result result;
			result.polygon_type = dist_t(engine);
			result.layer_index = layer_index;
			result.position.x = dist_x(engine);
			result.position.y = dist_y(engine);
			result.rotation = dist_r(engine);
			bool valid = true;
			double area_inside = 
				Polygon::Intersection(frame, polygons[result.polygon_type].Instantiate(result.position, result.rotation)).Area();
			if (area_inside < polygons[result.polygon_type].Area() - EPS) {
				valid = false;
			}
			for (Result &r : results) {
				double area_intersection = Polygon::Intersection(
					polygons[r.polygon_type].Instantiate(r.position, r.rotation), 
					polygons[result.polygon_type].Instantiate(result.position, result.rotation)
				).Area();
				if (r.layer_index == result.layer_index && area_intersection > EPS) {
					valid = false;
				}
				if (area_intersection > overlap_fraction_max[layer_index] * polygons[r.polygon_type].Area() ||
					area_intersection > overlap_fraction_max[layer_index] * polygons[result.polygon_type].Area()) {
					valid = false;
				}
			}
			if (valid) {
				results.push_back(result);
			}
		}
	}
}

void Task::Output () {
	std::ofstream out_wall("output/wall.out");
	out_wall << results.size() << std::endl << std::endl;
	for (Result &result : results) {
		out_wall << result.ToString() << std::endl;
	}
	out_wall.close();

	std::ofstream out_visual("output/visual.out");
	out_visual << frame_size.x << ' ' << frame_size.y << std::endl << std::endl;
	out_visual << results.size() << std::endl << std::endl;
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

