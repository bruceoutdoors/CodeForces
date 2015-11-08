#include <algorithm>
#include <iostream>
#include <vector>

typedef long long int bigInt;

using namespace std;

vector<bigInt>  c(100001, 0);

bigInt f(const int i)
{
	if (i == 0) return 0;
	if (i == 1) return c[1];

	return max(f(i - 1), f(i - 2) + i*c[i]);
}

int main() 
{
	int n, x, m = 0;
	cin >> n;

	while(n--) {
		cin >> x;
		c[x]++;
		m = max(m, x);
	}

	cout << f(m);
}
