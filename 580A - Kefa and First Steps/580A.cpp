#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int n; cin >> n;

	int p, q, maxSeq = 1, seq = 1; 

	cin >> p;
	while (--n) {
		cin >> q;
		if (q >= p) {
			maxSeq = max(++seq, maxSeq);
		} else {
			seq = 1;
		}
		swap(p, q);
	}

	cout << maxSeq;
}
