#include <iostream>

using namespace std; 

int main()
{
	int n, t; cin >> n >> t;
	
	char a;
	char q[n];
	for (int i = 0; i < n; i++) {
		cin >> a;
		q[i] = a;
	}
	
	for (int i = 0; i < t; ++i) {
		for (int j = n - 2; j >= 0; --j) {
			if (q[j] == 'B' && q[j+1] == 'G') {
				q[j]   = 'G';
				q[j+1] = 'B';
				--j;
			}
		}
	}

	for (int i = 0; i < n; i++) cout << q[i];
}
