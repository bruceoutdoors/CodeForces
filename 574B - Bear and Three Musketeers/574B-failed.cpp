#include <iostream>
#include <vector>
#include <set>

using namespace std;

set< set<int> > triplets;

class Graph
{
public:
    Graph(const int &v) : m_v(v)
    {
        m_g.reserve(m_v);
        for (int i = 0; i < m_v; ++i) {
            vector<bool> b(m_v, false);
            m_g.push_back(b);
        }
    }
    
    bool hasEdge(const int &v, const int &w) const 
    { 
        return m_g[v][w]; 
    }
    
    void addEdge(const int &v, const int &w) 
    { 
        m_g[v][w] = true; 
        m_g[w][v] = true; 
    }
    
    set<int> adj(const int &v) const 
    { 
        set<int> a;
        
        for (int i = 0; i < m_v; ++i) {
            if (m_g[v][i]) a.insert(i);
        }
        
        return a; 
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
    vector< vector<bool> > m_g;
};

void tripetFind(const Graph &g, const int &root,
             set<int>::iterator start, const set<int>::iterator &end)
{
    int p = *start++;

    for (auto it = start; it != end; ++it) {
        if (g.hasEdge(p, *it)) {
            triplets.insert({root, p, *it});
        }
    }
    
    if (start != end) tripetFind(g, root, start, end);
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
    
    for (int i = 1; i < g.getSize(); ++i) {
        auto adj = g.adj(i);
        if (adj.size() == 0) continue;
        tripetFind(g, i, adj.begin(), adj.end());
    }
    
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
