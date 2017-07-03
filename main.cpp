#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <random>

#define PI (4*atan(1))

class Vector2 {
public:
	Vector2 () {}
	Vector2 (double x, double y)
		: x(x)
		, y(y)
	{}

	Vector2 operator+ (const Vector2 &p) const {
		return Vector2(x + p.x, y + p.y);
	}

	Vector2 Rotate (double r) const {
		return Vector2(cos(r) * x - sin(r) * y, sin(r) * x + cos(r) * y);
	}

	Vector2 Instantiate (Vector2 offset, double rotation) {
		return this->Rotate(rotation) + offset;
	}
	
	std::string ToString () {
		return
			std::to_string(x) + " " +
			std::to_string(y);
	}

public:
	double x;
	double y;
};

class Polygon {
public:
	Polygon (std::vector<Vector2> &vertexs)
		: vertex_cnt(vertexs.size())
		, vertexs(vertexs)
	{
		area = Area();
	}

	Polygon Instantiate (Vector2 offset, double rotation) {
		std::vector<Vector2> v;
		for (Vector2 &vertex : vertexs) {
			v.push_back(vertex.Instantiate(offset, rotation));
		}
		return Polygon(v);
	}

	double Area () {
		return 100000.0;
	}

	Polygon operator& (const Polygon &p) const {
		return *this;
	}

public:
	int vertex_cnt;
	std::vector<Vector2> vertexs;
	double area;
};

class Result {
public:
	Result (
		int polygon_type, 
		int layer_index, 
		Vector2 position, 
		double rotation
	)	: polygon_type(polygon_type)
		, layer_index(layer_index)
		, position(position)
		, rotation(rotation)
	{}

	std::string ToString () {
		return 
			std::to_string(polygon_type) + " " + 
			std::to_string(layer_index) + " " + 
			position.ToString() + " " + 
			std::to_string(rotation);
	}
public:
	int polygon_type;
	int layer_index;
	Vector2 position;
	double rotation;
};

class Task {
public:
	Task () {}
	Task (
		Vector2 frame_size, 
		int layer_cnt, 
		std::vector<Polygon> &polygons, 
		double coverage_fraction_min, 
		double overlap_fraction_max
	)	: frame_size(frame_size)
		, layer_cnt(layer_cnt)
		, polygon_cnt(polygons.size())
		, polygons(polygons)
		, coverage_fraction_min(coverage_fraction_min)
		, overlap_fraction_max(overlap_fraction_max)
	{}

	void Input () {
		std::ifstream in_wall("wall.in");
		std::ifstream in_board("board.in");
		in_wall >> frame_size.x >> frame_size.y;
		in_wall >> layer_cnt;
		in_wall >> coverage_fraction_min >> overlap_fraction_max;
		in_board >> polygon_cnt;
		for (int i = 0; i < polygon_cnt; i ++) {
			int vertex_cnt;
			in_board >> vertex_cnt;
			std::vector<Vector2> vertexs;
			for (int j = 0; j < vertex_cnt; j ++) {
				double x, y;
				in_board >> x >> y;
				vertexs.push_back(Vector2(x, y));
			}
			polygons.push_back(Polygon(vertexs));
		}
		in_wall.close();
		in_board.close();
	}

	double CoverageFraction (int layer_index) {
		double area_total = frame_size.x * frame_size.y;
		double area_cover = 0.0;
		for (Result &result : results) {
//			std::cerr << "\t" << result.layer_index << "\t" << result.polygon_type << "\t" << polygons[result.polygon_type].area << std::endl;
			if (result.layer_index == layer_index) {
				area_cover += polygons[result.polygon_type].area;
			}
		}
		std::cerr << area_cover << ' ' << area_total << std::endl;
		return area_cover / area_total;
	}

	void Generate () {
		results.clear();
		std::uniform_int_distribution<int> dist_t(0, polygon_cnt-1);
		std::uniform_real_distribution<double> dist_x(0.0, frame_size.x);
		std::uniform_real_distribution<double> dist_y(0.0, frame_size.y);
		std::uniform_real_distribution<double> dist_r(0.0, 2 * PI);
		std::default_random_engine engine(time(0));
		for (int layer_index = 0; layer_index < layer_cnt; layer_index ++) {
			while (CoverageFraction(layer_index) < coverage_fraction_min) {
				int t = dist_t(engine);
				double x = dist_x(engine);
				double y = dist_y(engine);
				double r = dist_r(engine);
				std::cerr << t << ' ' << x << ' ' << y << ' ' << r << std::endl;
				std::cerr << CoverageFraction(layer_index) << std::endl;
				polygons[t].Instantiate(Vector2(x, y), r);
				results.push_back(Result(t, layer_index, Vector2(x, y), r));
			}
		}
	}

	void Output () {
		std::ofstream out_wall("wall.out");
		for (Result &result : results) {
			out_wall << result.ToString() << std::endl;
		}
		out_wall.close();
	}

public:
	Vector2 frame_size;
	int layer_cnt;
	int polygon_cnt;
	std::vector<Polygon> polygons;
	double coverage_fraction_min;
	double overlap_fraction_max;

	std::vector<Result> results;
};

int main (int argc, char **argv) {
	Task task;
	task.Input();
	task.Generate();
	task.Output();

	return 0;
}

