#pragma once
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
	int from, to, cost;
};


vector<int> fordbellman(int n, vector<Edge> const& edges, int start) {
	const int INF = 1e6;
	vector<int> d(n, INF);
	d[start] = 0;
	for (int i = 0; i < n - 1; i++)
		for (auto e : edges)
			if (d[e.from] < INF)
				d[e.to] = min(d[e.to], d[e.from] + e.cost);
	return d;
}