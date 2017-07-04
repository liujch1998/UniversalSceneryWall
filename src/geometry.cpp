#include "geometry.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

Vector2 Vector2::operator+ (Vector2 v) const {
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator- (Vector2 v) const {
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator* (double d) const {
	return Vector2(x * d, y * d);
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

Vector2 Vector2::Intersection (const Vector2 &v0a, const Vector2 &v0b, const Vector2 &v1a, const Vector2 &v1b) {
	double s1 = Vector2::Det(v1a, v0a, v1b);
	double s2 = Vector2::Det(v1a, v0b, v1b);
	Vector2 ans = (v0b * s1 - v0a * s2) * (1.0 / (s1 - s2));
	return ans;
}

Vector2 Vector2::Instantiate (Vector2 offset, double rotation) {
	return this->Rotate(rotation) + offset;
}

std::string Vector2::ToString () {
	return 
		std::to_string(x) + " " + 
		std::to_string(y);
}

Polygon Polygon::Intersection (Polygon p1, Polygon p2) {
//	p1.Output(std::cerr);
//	p2.Output(std::cerr);
	std::vector<Vector2> vertexs_new = p1.vertexs;
	for (int i = 0; i < p2.vertex_cnt; i ++) {
		int j = (i + 1) % p2.vertex_cnt;
		std::vector<Vector2> vertexs_old = vertexs_new;
		vertexs_new.clear();
		Vector2 S = *(vertexs_old.rbegin());
		for (Vector2 E : vertexs_old) {
			if (Vector2::Det(p2.vertexs[i], p2.vertexs[j], E) < 0) {
				if (Vector2::Det(p2.vertexs[i], p2.vertexs[j], S) >= 0) {
					vertexs_new.push_back(Vector2::Intersection(p2.vertexs[i], p2.vertexs[j], S, E));
				}
				vertexs_new.push_back(E);
			} else if (Vector2::Det(p2.vertexs[i], p2.vertexs[j], S) < 0) {
				vertexs_new.push_back(Vector2::Intersection(p2.vertexs[i], p2.vertexs[j], S, E));
			}
			S = E;
		}
		if (vertexs_new.empty()) {
			break;
		}
	}
	return Polygon(vertexs_new);
}

double Polygon::Area () {
	double ans = 0;
	for (int i = 1; i < vertex_cnt-1; i ++) {
		ans += Vector2::Det(vertexs[0], vertexs[i], vertexs[i+1]) / 2.0;
	}
	return fabs(ans);
}
/*
double Polygon::AreaIntersect (const Polygon &p1, const Polygon &p2) {
	double ans = 0.0;
	std::vector<Polygon> t1 = p1.Triangulate();
	std::vector<Polygon> t2 = p2.Triangulate();
	for (Polygon &a1 : t1) {
		for (Polygon &a2 : t2) {
			ans += Polygon::AreaIntersectTriangle(a1, a2);
		}
	}
	return fabs(ans);
}

double Polygon::AreaIntersectTriangle (const Polygon &p1, const Polygon &p2) {
	std::vector<Vector2> vertexs = p1.vertexs;
	for (int i = 0; i < p2.vertex_cnt; i ++) {
		int j = (i + 1) % p2.vertex_cnt;

	}
	return 0;
}

std::vector<Polygon> Polygon::Triangulate () const {
	std::vector<Polygon> ans;
	for (int i = 1; i < vertex_cnt-1; i ++) {
		std::vector<Vector2> vertexs {vertexs[0], vertexs[i], vertexs[i+1]};
		ans.push_back(Polygon(vertexs));
	}
	return ans;
}
*/
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

