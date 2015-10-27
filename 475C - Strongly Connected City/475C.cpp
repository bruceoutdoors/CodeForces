#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <deque>

using namespace std;

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
    
    DiGraph reverse() const
    {
		DiGraph r(m_v);
		
		for (int i = 0; i < m_v; ++i) {
			for (const auto &v : adj(i)) {
				r.addEdge(v, i);
			}
		}
		
		return r;
	}
    
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

	deque<int> order; // used as stack
	
private:
	void dfs(const DiGraph &g, const int &v)
	{
		marked[v] = true;
		
		for (const auto &w : g.adj(v)) {
			if (!marked[w]) {
				dfs(g, w);
			}
		}
		
		order.push_front(v);
	}

	vector<bool> marked;
};

class KosarajuSCC
{
public:
	KosarajuSCC(const DiGraph &g) : count(0)
	{
		for (int i = 0; i < g.getSize(); ++i) {
			marked.push_back(false);
			ids.push_back(0);
		}
		
		Topological topo(g.reverse());
		
		for (const auto &v : topo.order) {
			if (marked[v]) continue;
			
			dfs(g, v);
			++count;
		} 

	}
	
	bool isConnected(const int &a, const int &b) { return ids[a] == ids[b]; }
	int getId(const int &v) { return ids[v]; }
	int getCount() const { return count; }
	
private:
	void dfs(const DiGraph &g, int v) 
	{
		marked[v] = true;
		ids[v] = count;
		
		for (const auto &adjV : g.adj(v)) {
			if (marked[adjV]) continue;
			
			dfs(g, adjV);
		}
	}

	int count;
	vector<bool> marked;
	vector<int> ids;
};

int main()
{
	int n, m, size;
	cin >> n >> m;
	
	size = n * m;
	DiGraph g(size);
	
	char c;
	
	for (int i = 0; i < n; ++i) {
		cin >> c;
		
		for (int j = i*m; j < ((i+1)*m)-1; ++j)  {
			if (c == '>') {
				//~ cout << "add edge: " << j << " " << j+1 << endl;
				g.addEdge(j, j+1);
			} else {
				//~ cout << "add edge: " << j+1 << " " << j << endl;
				g.addEdge(j+1, j);
			}
		}
	}
	
	for (int i = 0; i < m; ++i) {
		cin >> c;
		
		for (int j = i; j < size - (m - i); j += m)  {
			if (c == '^') {
				//~ cout << "add edge: " << j+m << " " << j << endl;
				g.addEdge(j+m, j);
			} else {
				//~ cout << "add edge: " << j << " " << j+m << endl;
				g.addEdge(j, j+m);
			}
		}
	}
	
	KosarajuSCC kscc(g);

	cout << (kscc.getCount() == 1 ? "YES" : "NO");
}
