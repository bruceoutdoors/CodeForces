#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

class Graph
{
public:
    Graph(const int &v) : m_v(v)
    {
        m_g.reserve(m_v);
        for (int i = 0; i < m_v; ++i) m_g.push_back({});
    }
    
    bool hasEdge(const int &v, const int &w) { return m_g[v].find(w) == m_g[v].end() ? false : true; }
    
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

class CC
{
public:
	CC(const Graph &g) : count(0)
	{
		for (int i = 0; i < g.getSize(); ++i) {
			marked.push_back(false);
			ids.push_back(0);
		}
		
		for (int i = 0; i < g.getSize(); ++i) {
			if (marked[i]) continue;
			
			dfs(g, i);
			++count;
		} 

	}
	
	bool isConnected(const int &a, const int &b) const { return ids[a] == ids[b]; }
	int getId(const int &v) { return ids[v]; }
	int getCount() const { return count; }
	
private:
	void dfs(const Graph &g, int v) 
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

// maps color to a graph
map<int, Graph*> colorToGraph;
vector<CC> ccs;

int main()
{
	int n, m; cin >> n >> m;
	int a, b, c;
	
	while (m--) {
		cin >> a >> b >> c;
		
		if (!colorToGraph[c]) colorToGraph[c] = new Graph(n+1);
		
		colorToGraph[c]->addEdge(a, b);
	}
	
	ccs.reserve(colorToGraph.size());
	for (const auto &g : colorToGraph) {
		ccs.push_back(CC(*g.second));
	}
	
	int q; cin >> q;
	int u, v, count;
	
	while (q--) {
		count = 0;
		cin >> u >> v;
		for (const auto &cc : ccs) {
			if (cc.isConnected(u, v)) count++;
		}
		cout << count << endl;
	}
	

	for (auto &g : colorToGraph) delete g.second;
}
