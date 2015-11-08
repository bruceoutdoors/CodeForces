#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

set< vector<int> > triplets;

class Graph
{
public:
    Graph(const int &v) : m_v(v)
    {
        m_g.reserve(m_v);
        for (int i = 0; i < m_v; ++i) {
			m_g.push_back({});
		}
    }
    
    bool hasEdge(const int &v, const int &w) const 
    { 
		return m_g[v].find(w) != m_g[v].end(); 
	}
    
    void addEdge(const int &v, const int &w) 
    { 
		m_g[v].insert(w); 
		m_g[w].insert(v); 
	}
    
    set<int> adj(const int &v) const { return m_g[v]; }
    
    int getSize() const { return m_v; }
    
    void print() 
    {
        for (int i = 0; i < m_v; ++i) {
            cout << i << " : ";
            for (const auto &v : adj(i)) cout << v << " ";
             
            cout << endl;
        }
    }
    
private:
    const int m_v;
    vector< set<int> > m_g;
};

void comb(const Graph &g, int N, int K)
{
    string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's

    // print integers and permute bitmask
    do {
		vector<int> c;
        for (int i = 0; i < N; ++i) {// [0..N-1] integers
            if (bitmask[i]) c.push_back(i+1);
        }
		
		if (g.hasEdge(c[0], c[1]) 
			&& g.hasEdge(c[1], c[2])
			&& g.hasEdge(c[0], c[2])) {
				triplets.insert(c);
		}
		
    } while (prev_permutation(bitmask.begin(), bitmask.end()));
}

int main()
{
	int n, m; cin >> n >> m;
	
	Graph g(n+1);
	
	int a, b;
	while(m--) {
		cin >> a >> b;
		g.addEdge(a, b);
	}
	
	comb(g, n, 3);
	
	if (triplets.size() == 0) {
		cout << -1;
		return 0;
	}
	
	int minRecog = INT_MAX;
	
	for (const auto &t : triplets) {
		int recog = 0;
		for (const auto &w : t) {
			recog += g.adj(w).size();
		}
		
		if (recog < minRecog) minRecog = recog;
	}
	
	cout << minRecog - 6;
}
