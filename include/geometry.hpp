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
	static double Cross (const Vector2 &v1, const Vector2 &v2);
	static double Det (const Vector2 &v0, const Vector2 &v1, const Vector2 &v2);
	Vector2 Rotate (double rotation) const;
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
	Polygon operator& (const Polygon &p) const;
	Polygon Instantiate (Vector2 offset, double rotation);

	void Input (std::istream &in);
	void Output (std::ostream &out);

public:
	int vertex_cnt;
	std::vector<Vector2> vertexs;
};

