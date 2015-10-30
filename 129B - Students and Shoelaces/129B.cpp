#include <iostream>
#include <vector>

using namespace std;

struct edge {
	edge (int x, int y) : x(x), y(y) {}
	int x, y;
	bool active = true;
};

int main()
{
	int n, m; cin >> n >> m;
	
	vector<int> degrees(n+1);
	vector<edge> edges;
	edges.reserve(m);
	
	int x, y;
	while (m--) {
		cin >> x >> y;
		degrees[x]++;
		degrees[y]++;
		edges.push_back(edge(x, y));
	}
	
	int groupCount = 0;
	
	while (true) {
		vector<edge*> edgeToRemove;
		bool hasGroup = false;
		for (auto &ed : edges) {
			if (ed.active && 
					(degrees[ed.x] == 1 || degrees[ed.y] == 1)) {
				edgeToRemove.push_back(&ed);
				hasGroup = true;
			}
		}
		
		for (auto &ed : edgeToRemove) {
			degrees[ed->x]--;
			degrees[ed->y]--;
			ed->active = false;
		}
		
		if (!hasGroup) break;
		else groupCount++;;
	}
	
	cout << groupCount;
}
