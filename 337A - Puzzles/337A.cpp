#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main()
{
	int n, m; cin >> n >> m;

	vector<int> arr;
	int f, g;

	g = m;

	while (g--) {
		cin >> f;
		arr.push_back(f);
	}

	sort(arr.begin(), arr.end());

	int minimum = INT_MAX;
	for (int i = n - 1; i < arr.size(); i++) {
		int j = i - n + 1;
		int diff = arr[i] - arr[j];
		minimum = min(diff, minimum);
	}

	cout << minimum;
}
