#include <iostream>
#include <set>

using namespace std;

int main()
{
	int size, invalidsSize;
	set<int> invalids;
	cin >> size >> invalidsSize;
	
	for (int i = 0; i < invalidsSize; ++i) {
		for (int j = 0; j < 2; ++j) {
			int a;
			cin >> a;
			invalids.insert(a);
		}
	}
	
	cout << size - 1 << endl;
	
	int center;
	for (int i = 1; i <= size; ++i) {
		if (invalids.find(i) == invalids.end()) {
			center = i;
			break;
		}
	}
	
	for (int i = 1; i <= size; ++i) {
		if (i == center) continue;
		
		cout << center << " " << i << endl;
	}
}
