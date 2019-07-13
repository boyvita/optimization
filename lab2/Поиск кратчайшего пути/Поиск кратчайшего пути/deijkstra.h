#pragma once
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

vector<int> deijkstra(vector<vector<pair<int, int>>> const& graph, int start) {
	const int INF = 1e6;
	vector<int> d(graph.size(), INF);
	d[start] = 0;
	set<pair<int, int>> q;
	q.insert(make_pair(d[start], start));
	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase(q.begin());

		for (auto now : graph[v]) {
			int to = now.first;
			int cost = now.second;
			if (d[v] + cost < d[to]) {
				q.erase(make_pair(d[to], to));
				d[to] = d[v] + cost;
				q.insert(make_pair(d[to], to));
			}
		}
	}
	return d;
}