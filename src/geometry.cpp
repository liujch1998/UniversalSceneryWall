#include "geometry.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <cmath>

Vector2 Vector2::operator+ (Vector2 v) const {
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator- (Vector2 v) const {
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::Rotate (double rotation) const {
	return Vector2(
		cos(rotation) * x - sin(rotation) * y, 
		sin(rotation) * x + cos(rotation) * y
	);
}

double Vector2::Cross (const Vector2 &v1, const Vector2 &v2) {
	return v1.x * v2.y - v2.x * v1.y;
}

double Vector2::Det (const Vector2 &v0, const Vector2 &v1, const Vector2 &v2) {
	Vector2 a = v1 - v0;
	Vector2 b = v2 - v0;
	return Cross(a, b);
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
	double ans = 0;
	for (int i = 1; i < vertex_cnt-1; i ++) {
		ans += Vector2::Det(vertexs[0], vertexs[i], vertexs[i+1]) / 2.0;
	}
	return fabs(ans);
}

Polygon Polygon::operator& (const Polygon &p) const {
	// Pending implementation
	return *this;
}

Polygon Polygon::Instantiate (Vector2 offset, double rotation) {
	std::vector<Vector2> v;
	for (Vector2 &vertex : vertexs) {
		v.push_back(vertex.Instantiate(offset, rotation));
	}
	return Polygon(v);
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

