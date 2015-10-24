#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Digraph
{
public:
    Digraph(const int &v) : m_v(v)
    {
        m_g.reserve(m_v);
        for (int i = 0; i < m_v; ++i) m_g.push_back({});
    }
    
    void addEdge(const int &v, const int &w) { m_g[v].insert(w); }
    
    set<int> adj(const int &v) const { return m_g[v]; }
    
    int getV() const { return m_v; }
    
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
    CC(const Digraph &dg, const int &s) : 
        m_marked(dg.getV(), false) 
    {
        dfs(dg, s);
    }
    
    void dfs(const Digraph &dg, const int &v)
    {
        m_marked[v] = true;
        
        for (const int &w : dg.adj(v)) {
            if (!m_marked[w]) dfs(dg, w);
        }
    }
    
    bool isConnected(const int &v) const { return m_marked[v]; }
    
private:
    vector<bool> m_marked;
};

int main()
{
    int numCells, target;
    cin >> numCells >> target;
    
    Digraph dg(numCells+1);
    
    //~ cout << numCells << " " << target << endl;
    
    int i, c = 0;
    while (cin >> i) {
        c++;
        dg.addEdge(c, i+c);
    }
    
    //~ dg.print();
    
    CC cc(dg, 1);
    cout << (cc.isConnected(target) ? "YES" : "NO");
}
