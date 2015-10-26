#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> a;
	int size, edges, minEnergy;
	cin >> size >> edges;
	
	a.reserve(size+1);
	a.push_back(-1); // index start at 1
	
	for (int i = 0; i < size; ++i) {
		int b;
		cin >> b;
		a.push_back(b);
	}
	
	minEnergy = 0;
	for (int i = 0; i < edges; ++i) {
		int c, d;
		cin >> c >> d;
		
		minEnergy += (a[c] < a[d] ? a[c] : a[d]);
	}
	
	cout << minEnergy;
}
