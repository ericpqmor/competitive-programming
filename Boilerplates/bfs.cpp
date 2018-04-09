#include <bits/stdc++.h>
using namespace std;

vector<int> g[3000];

void visit(int n) {
	cout << "Visited: " << n << endl;
}

void bfs(int root) {
	bool visited[3000];
	memset(visited, 0, sizeof visited);
	queue<int> q;
	
	visited[root] = 1;
	q.push(root);

	while(!q.empty()) {
		int r = q.front();
		q.pop();
		visit(r);

		for(int i=0; i<(int) g[r].size(); i++) {
			int v = g[r][i];
			if(!visited[v]) {
				visited[v] = true;
				q.push(v);
			}
		}
	}
}

int main() {
	int numEdges;
	cin >> numEdges;

	for(int i=0; i<numEdges; i++) {
		int x, y;
		cin >> x >> y;
		
		g[x].push_back(y);
		g[y].push_back(x);
	}

	bfs(1);
}
