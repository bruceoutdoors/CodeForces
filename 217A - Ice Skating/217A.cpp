#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <utility> 

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
	
	bool isConnected(const int &a, const int &b) { return ids[a] == ids[b]; }
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

int main()
{
	int size;
	vector < pair<int, int> > snowDrifts;
	
	cin >> size;
	snowDrifts.reserve(size);
	Graph g(size);
	
	for (int i = 0; i < size; ++i) {
		int x, y;
		cin >> x >> y;
		
		for (int j = 0; j < snowDrifts.size(); ++j) {
			if (snowDrifts[j].first == x || snowDrifts[j].second == y) {
				g.addEdge(j, snowDrifts.size());
			}
		}
		
		pair<int, int> drift(x, y);
		snowDrifts.push_back(drift);
	}
	
	CC cc(g);
	cout << cc.getCount() - 1;
	
	// print components:
	//~ cout << endl;
	//~ map< int, vector<int> > components;
	//~ for (int i = 0; i < cc.getCount(); ++i) {
		//~ vector<int> vec;
		//~ components[i] = vec;
	//~ }
	
	//~ for (size_t i = 0; i < g.getSize(); ++i) {
		//~ components[cc.getId(i)].push_back(i);
	//~ }
	
	//~ int itr = 1;
	//~ for (const auto &compt : components) {
		//~ cout << "Component " << itr++ << ": ";
		
		//~ for (const auto &v : compt.second) 
			//~ cout << v << " ";
		
		//~ cout << endl;
	//~ }
}
