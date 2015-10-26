#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "put the lexigraphic sequence as parameter, for example:" << endl
			 << "   combTester xutpwyvsozrqnmlkjihgfedcba < input1.txt" << endl;
		return 0;
	}
	string a = argv[1];
	
	map<char, int> m;
	
	int p = 0;
	for (auto &c : a) {
		m[c] = p;
		++p;
	}
	
	int n;
	string name;
	cin >> n;
	cin.get();
	
	for (int i = 0; i < n; ++i) {
		getline (cin, name);
		cout << name << endl;
		for (auto &c : name) {
			cout << m[c] << " ";
		}
		cout << endl;
	}

}

