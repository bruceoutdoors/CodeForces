#include <iostream>
#include <vector>
#include <set>
#include <array>

using namespace std;

class Digraph
{
public:
    Digraph(const int &v) : m_v(v)
    {
        m_g.reserve(m_v);
        for (int i = 0; i < m_v; ++i) m_g.push_back({});
    }
    
    bool hasEdge(const int &v, const int &w) { return m_g[v].find(w) == m_g[v].end() ? false : true; }
    
    void addEdge(const int &v, const int &w) { m_g[v].insert(w); }
    
    set<int> adj(const int &v) const { return m_g[v]; }
    
    int getV() const { return m_v; }
    
    Digraph getReverse() const
    {
        Digraph rdg(m_v);
        
        for (int i = 0; i < m_v; i++) {
            for (const int &v : adj(i)) {
                rdg.addEdge(v, i);
            }
        }
        
        return rdg;
    }
    
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

int deepestDepth = 0;
void deepestDepthDfs(Digraph &dg, int source, int depth = 1)
{
    if (depth > deepestDepth) deepestDepth = depth;
    
    for (const int &v : dg.adj(source)) {
        deepestDepthDfs(dg, v, depth+1);
    }
}

int main()
{
    int n, m, i, manager;
    i = 0;

    cin >> n;
    
    Digraph dg(n+1);

    m = n;
    while (m--) {
        i++;
        cin >> manager;
        if (manager == -1) continue;
        
        dg.addEdge(i, manager);
        //~ cout << i << "  " << manager << endl;
    }
    
    // find deepest depth of the digraph
    for (int i = 1; i <= n; i++)
        deepestDepthDfs(dg, i);

    cout << deepestDepth;
}
