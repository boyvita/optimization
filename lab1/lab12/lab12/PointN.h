#pragma once
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

const double EPS = 1e-6;

struct PointN {
	vector<double> x;
	PointN(size_t const& n) {
		x.resize(n);
	}

	PointN(initializer_list<double> il) {
		x.assign(il);
	}

	size_t dim() {
		return x.size();
	}

	PointN & operator = (PointN p) {
		this->x = p.x;
		return *this;
	}

	double & operator [] (size_t i) {
		return x[i];
	}

	double len() const {
		double ans = 0;
		for (size_t i = 0; i < x.size(); i++) {
			ans += x[i] * x[i];
		}
		return sqrt(ans);
	}

	
};

PointN operator + (PointN p1, PointN p2) {
	size_t n = min(p1.dim(), p2.dim());
	PointN ans(max(p1.dim(), p2.dim()));
	for (size_t i = 0; i < n; i++) {
		ans[i] = p1[i] + p2[i];
	}
	for (size_t i = n; i < p1.dim(); i++) {
		ans[i] = p1[i];
	}
	for (size_t i = n; i < p2.dim(); i++) {
		ans[i] = p2[i];
	}
	return ans;
}

PointN operator + (PointN p) {
	return PointN(p);
}

PointN operator - (PointN p1, PointN p2) {
	size_t n = min(p1.dim(), p2.dim());
	PointN ans(max(p1.dim(), p2.dim()));
	for (size_t i = 0; i < n; i++) {
		ans[i] = p1[i] - p2[i];
	}
	for (size_t i = n; i < p1.dim(); i++) {
		ans[i] = p1[i];
	}
	for (size_t i = n; i < p2.dim(); i++) {
		ans[i] = -p2[i];
	}
	return ans;
}

PointN operator - (PointN p) {
	return PointN(p.dim()) - p;
}

PointN operator * (PointN p, double d) {
	PointN ans(p.dim());
	for (size_t i = 0; i < p.dim(); i++) {
		ans[i] = p[i] * d;
	}
	return ans;
}

PointN operator / (PointN p, double d) {
	return p * (1 / d);
}

ostream & operator << (ostream &os, PointN p) {
	os << "(";
	for (size_t i = 0; i < p.dim() - 1; i++)
		os << p[i] << ", ";
	return os << p[p.dim() - 1] << ")";
}

PointN gradient(PointN p, double(*_f)(PointN)) {
	PointN ans(p.dim());
	double delta = 1e-6;
	//cout << "deriatives: \n";
	//cout << "current point p = " << p << "; f(p) = " << _f(p) << '\n';
	for (int i = 0; i < p.dim(); i++) {
		PointN p_new(p);
		p_new[i] += delta;
		//cout << "axis #" << i << "; new point = " << p_new << "; f(p_new)  = " << _f(p_new) << '\n';
		ans[i] = (_f(p_new) - _f(p)) / delta;
	}
	//cout << "gradient = " << ans << '\n';
	return ans;
}