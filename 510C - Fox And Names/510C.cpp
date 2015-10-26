#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <deque>

using namespace std;

string ALPHABETS = "abcdefghijklmnopqrstuvwxyz";

class DiGraph
{
public:
    DiGraph(const int &v) : m_v(v)
    {
        m_g.reserve(m_v);
        for (int i = 0; i < m_v; ++i) {
			m_g.push_back({});
		}
    }
    
    bool hasEdge(const int &v, const int &w) { return m_g[v].find(w) == m_g[v].end() ? false : true; }
    
    void addEdge(const int &v, const int &w) 
    { 
		m_g[v].insert(w); 
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

class Topological 
{
public:
	Topological(const DiGraph &g)
	{
		for (int i = 0; i < g.getSize(); ++i) {
			marked.push_back(false);
		}
		
		for (int u = 0; u < g.getSize(); ++u) {
			if (!marked[u]) dfs(g, u);
		}
	}

	deque<char> order; // used as stack
	
private:
	void dfs(const DiGraph &g, const int &v)
	{
		marked[v] = true;
		
		for (const auto &w : g.adj(v)) {
			if (!marked[w]) {
				dfs(g, w);
			}
		}
		
		order.push_front(ALPHABETS[v]);
	}

	vector<bool> marked;
};

class DiCycle
{
public:
	DiCycle(const DiGraph &g) : hasCycle(false)
	{
		for (int i = 0; i < g.getSize(); ++i) {
			onStack.push_back(false);
			marked.push_back(false);
		}
		
		for (int i = 0; i < g.getSize(); ++i) {
			if (!marked[i] && !hasCycle) dfs(g, i);
		}
	}
	
	bool hasCycle;
	
private:
	void dfs(const DiGraph &g, const int &v)
	{
		if (hasCycle) return;
		
		onStack[v] = true;
		marked[v] = true;
		
		for (const auto &w : g.adj(v)) {
			if (!marked[w]) {
				dfs(g, w);
			} else if (onStack[w]) {
				hasCycle = true;
				return;
			}
		}
		
		onStack[v] = false;
	}
	
	vector<bool> onStack;
	vector<bool> marked;
};

int main()
{
	DiGraph g(ALPHABETS.size());
	
	map<char, int> m;
	for (int i = 0; i < ALPHABETS.size(); ++i) {
		m[ALPHABETS[i]] = i;
	}
	
	int n;
	string a, b;
	cin >> n >> a;
	
	// add precedence constraints:
	for (int i = 0; i < n-1; ++i) {
		cin >> b;
		//~ cout << "compare " << a << " and " << b << endl;
		for (int j = 0;j < a.size() && j < b.size(); ++j) {
			if (a[j] != b[j]) {
				//~ cout << a[j] << " precedes " << b[j] << endl;
				g.addEdge(m[a[j]], m[b[j]]);
				break;
			} 
			
			// if both words have no differing characters, the shortest 
			// string should be smaller.
			if ((j == b.size() - 1) 
					&& (a.size() > b.size())) {
				cout << "Impossible";
				return 0;
			}
		}
		
		swap(a, b);
	}
	
	DiCycle cycle(g);
	
	if (cycle.hasCycle) {
		cout << "Impossible";
		return 0;
	}
	
	Topological topo(g);
	
	for (const auto &c : topo.order) cout << c;
}
