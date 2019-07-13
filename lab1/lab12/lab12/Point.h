#pragma once
#include <cmath>
#include <vector>

using namespace std;

template <size_t n>
class Point {
public:
	vector<double> x;

	Point() {
		x.resize(n);
	}

	Point(initializer_list<double> const& il) {
		if (il.size() != n)
			throw exception("bad size");
		x.assign(il);
	}

	Point<n> & operator = (Point<n> const& p) {
		this->x = p.x;
	}

	inline double& operator [] (size_t const& i) {
		return x[i];
	}
	
	inline double const& len() const {
		double ans = 0;
		for (size_t i = 0; i < n; i++) {
			ans += x[i] * x[i];
		}
		return sqrt(ans);
	}

};

template<size_t n>
Point<n> const& operator + (Point<n> const& p1, Point<n> const& p2) {
	Point<n> ans();
	for (size_t i = 0; i < n; i++) {
		ans[i] = p1[i] + p2[i];
	}
	return ans;
}

template<size_t n>
Point<n> const& operator + (Point<n> const& p) {
	return Point(p);
}

template<size_t n>
Point<n> operator - (Point<n> const& p1, Point<n> const& p2) {
	Point<n> ans();
	for (size_t i = 0; i < n; i++) {
		ans[i] = p1[i] - p2[i];
	}
	return ans;
}

template<size_t n>
Point<n> const& operator - (Point<n> const& p) {
	return Point<n>() - p;
}

template<size_t n>
Point<n> const& operator * (Point<n> const& p, double d) {
	Point<n> ans();
	for (size_t i = 0; i < n; i++) {
		ans[i] = p[i] * d;
	}
	return ans;
}

template<size_t n>
Point<n> const& operator / (Point<n> const& p, double d) {
	return p * (1 / d);
}
