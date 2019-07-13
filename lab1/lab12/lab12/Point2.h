#pragma once
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

class Point2 {
public:
	double x, y;
	
	Point2() = default;

	Point2(Point2 const&) = default;

	Point2(double x, double y) : x(x), y(y) {}

	Point2 & operator = (Point2 const& p) = default;

	double len() const {
		return sqrt(x * x + y * y);
	}

};

Point2 operator + (Point2 const& p1, Point2 const& p2) {
	return Point2(p1.x + p2.x, p1.y + p2.y);
}

Point2 operator + (Point2 const& p) {
	return Point2(p);
}

Point2 operator - (Point2 const& p1, Point2 const& p2) {
	return Point2(p1.x - p2.x, p1.y - p2.y);
}

Point2 operator - (Point2 const& p) {
	return Point2() - p;
}


Point2 operator * (Point2 const& p, double d) {
	return Point2(p.x * d, p.y * d);
}


Point2 operator / (Point2 const& p, double d) {
	return Point2(p.x / d, p.y / d);
}

ostream & operator << (ostream &os, Point2 p) {
	return os << "(" << p.x << ", " << p.y << ")";
}
