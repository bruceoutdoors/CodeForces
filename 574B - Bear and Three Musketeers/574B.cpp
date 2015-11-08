#include <iostream>
#include <algorithm>

using namespace std;

bool adjMat[4001][4001];
int val[4001], x[4001], y[4001];
int minRecog = INT_MAX;

int main()
{
	int n, m; cin >> n >> m;
	
    for (int i = 1; i < m+1; ++i) {
        cin >> x[i] >> y[i];
        adjMat[x[i]][y[i]] = adjMat[y[i]][x[i]] = true;
        val[x[i]]++;
        val[y[i]]++;
    }
    
    for (int i = 1; i < m+1; ++i) { // iterate edges
        for (int j = 1; j < n+1; ++j) { // iterate vertices
			if (adjMat[j][x[i]] && adjMat[j][y[i]]) {
				minRecog = min(minRecog, val[j] + val[x[i]] + val[y[i]]);
			}
		}
    }
    
    cout << (minRecog == INT_MAX ? -1 : minRecog - 6);
}
