#include <iostream>
#include <vector>
#include <set>
#include <queue>

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

int blueButton(const int &n) { return n-1; }
int redButton (const int &n) { return n*2; }

void addTwoPaths(Digraph &dg, const int &v, const int &m)
{
    int b = blueButton(v);
    int r = redButton(v);
    
    
    if (b <= 50000 && b > 0 && !dg.hasEdge(v, b)) {
        dg.addEdge(v, b);
        addTwoPaths(dg, b, m);
    }
    
    if (r <= 50000 && !dg.hasEdge(v, r)) {
        dg.addEdge(v, r);
        addTwoPaths(dg, r, m);
    }
}



int minStepsBfs(Digraph &dg, const int &start, const int &target)
{
    queue<int> q;
    vector<bool> marked(dg.getV(), false);
    vector<int> edgeTo(dg.getV(), -1);
    bool found = false;
    
    q.push(start);
    
    while(!q.empty() && !found) {
        int front = q.front();
        q.pop();
        for (const int &v : dg.adj(front)) {
            if (marked[v]) continue;
            
            marked[v] = true;
            q.push(v);
            edgeTo[v] = front;
            
            if (v == target) {
                found = true;
                break;
            }
        } 
    }
    
    //~ cout << target;
    int depth = 0;
    int w = target;
    while (edgeTo[w] != -1) {
        w = edgeTo[w];
        //~ cout  << " <-" << w;
        depth++;
        if (w == start) break;
    }
    //~ cout << endl;
    
    return depth;
}

int main()
{
    int n, m;
    cin >> n >> m;

    // it is never reasonable to make the number larger than 2m
    Digraph dg(100000);
    
    addTwoPaths(dg, n, m);
    //~ dg.print();
    
    cout << minStepsBfs(dg, n, m);

}
