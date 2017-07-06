#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <cmath>

class Vector2 {
public:
	Vector2 () {}
	Vector2 (double x, double y)
		: x(x)
		, y(y)
	{}

	Vector2 operator+ (Vector2 v) const;
	Vector2 operator- (Vector2 v) const;
	Vector2 operator* (double d) const;
	Vector2 Rotate (double rotation) const;
	static double Cross (const Vector2 &v1, const Vector2 &v2);
	static double Det (const Vector2 &v0, const Vector2 &v1, const Vector2 &v2);
	static Vector2 Intersection (const Vector2 &v0a, const Vector2 &v0b, const Vector2 &v1a, const Vector2 &v1b);
	Vector2 Instantiate (Vector2 offset, double rotation);
	
	std::string ToString ();

public:
	double x;
	double y;
};

class Polygon {
public:
	Polygon () {}
	Polygon (std::vector<Vector2> &vertexs)
		: vertex_cnt(vertexs.size())
		, vertexs(vertexs)
	{}

	double Area ();
	static Polygon Intersection (Polygon p1, Polygon p2);
	Polygon Instantiate (Vector2 offset, double rotation);

	void Input (std::istream &in);
	void Output (std::ostream &out);

public:
	int vertex_cnt;
	std::vector<Vector2> vertexs;
};

