#include <iostream>

using namespace std; 

bool divisible(int d)
{
	return (d % 2   == 0 && d != 2 ) 
		|| (d % 3   == 0 && d != 3 )
		|| (d % 5   == 0 && d != 5 )
		|| (d % 7   == 0 && d != 7 )
		|| (d % 11  == 0 && d != 11)
		|| (d % 13  == 0 && d != 13)
		|| (d % 17  == 0 && d != 17)
		|| (d % 19  == 0 && d != 19)
		|| (d % 23  == 0 && d != 23)
		|| (d % 29  == 0 && d != 29)
		|| (d % 31  == 0 && d != 31)
		|| (d % 37  == 0 && d != 37)
		|| (d % 41  == 0 && d != 41)
		|| (d % 43  == 0 && d != 43)
		|| (d % 47  == 0 && d != 47);
}

int main()
{
	int n; cin >> n;
	
	int a, b;
	a = n / 2;
	b = n % 2 == 0 ? a : a + 1;
	
	while (!divisible(a) || !divisible(b)) {
		--a; ++b;
	}
	
	cout << a << ' ' << b;
}
