#include "geometry.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <cmath>

Vector2 Vector2::operator+ (Vector2 v) const {
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::Rotate (double rotation) const {
	return Vector2(
		cos(rotation) * x - sin(rotation) * y, 
		sin(rotation) * x + cos(rotation) * y
	);
}

Vector2 Vector2::Instantiate (Vector2 offset, double rotation) {
	return this->Rotate(rotation) + offset;
}

std::string Vector2::ToString () {
	return 
		std::to_string(x) + " " + 
		std::to_string(y);
}

double Polygon::Area () {
	return 10000.0;
}

Polygon Polygon::operator& (const Polygon &p) const {
	return *this;
}

Polygon Polygon::Instantiate (Vector2 offset, double rotation) {
	std::vector<Vector2> v;
	for (Vector2 &vertex : vertexs) {
		v.push_back(vertex.Instantiate(offset, rotation));
	}
}

void Polygon::Input (std::istream &in) {
	in >> vertex_cnt;
	for (int vertex_index = 0; vertex_index < vertex_cnt; vertex_index ++) {
		Vector2 vertex;
		in >> vertex.x >> vertex.y;
		vertexs.push_back(vertex);
	}
}

void Polygon::Output (std::ostream &out) {
	out << vertex_cnt << std::endl;
	for (Vector2 &vertex : vertexs) {
		out << vertex.x << ' ' << vertex.y << std::endl;
	}
}

