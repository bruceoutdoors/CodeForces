#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n, m; cin >> n >> m;
	
	vector<int> degrees(n+1);
	
	int x, y;
	
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		degrees[x]++;
		degrees[y]++;
	}
	
	// if graph has 2 vertices with degree of 1 and others 2, it is a bus
	// if all graph vertices have a degree of 2, it is a ring
	int c = 2; 
	int starDegree = n-1;
	for (int i = 1; i < n+1; i++) {
		if (degrees[i] == 2) {
		} else if (degrees[i] == 1) {
			--c;
		} else if (m == n-1 && degrees[i] == starDegree) {
			cout << "star topology";
			return 0;
		} else {
			cout << "unknown topology";
			return 0;
		}
	}
	
	cout << (c == 0 ? "bus topology" : "ring topology");
}
