#include "deijkstra.h"
#include "fordbellman.h"
#include <iostream>

using namespace std;

vector<Edge> edges = {
	{ 1, 2, 8 },
	{ 1, 5, 7 },
	{ 1, 6, 9 },
	{ 1, 3, 3 },
	{ 2, 4, 4 },
	{ 5, 4, 3 },
	{ 6, 8, 5 },
	{ 3, 8, 9 },
	{ 4, 7, 7 },
	{ 4, 9, 8 },
	{ 8, 7, 9 },
	{ 8, 9, 0 },
	{ 9, 10, 5 },
	{ 7, 10, 6 }	
}; 

int main() {
	int n = 0;
	for (auto & e : edges) {
		n = max(n, e.from);
		e.from--;
		n = max(n, e.to);
		e.to--;
	}

	vector<int> ans1 = fordbellman(n, edges, 0);

	vector<vector<pair<int, int>>> graph(n);
	for (auto e : edges) 
		graph[e.from].push_back({ e.to, e.cost });
	
	vector<int> ans2 = deijkstra(graph, 0);

	for (int i = 1; i <= n; i++) 
		printf("%3d ", i);
	cout << '\n';

	for (auto d : ans1)
		printf("%3d ", d);
	cout << " - fordbellman \n";

	for (auto d : ans2)
		printf("%3d ", d);
	cout << " - deijkstra \n";

}