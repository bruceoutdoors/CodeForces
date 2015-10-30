#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <algorithm>


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

int deepestDepth = 0;
void deepestDepthDfs(Digraph &dg, int source, int depth = 1)
{
    if (depth > deepestDepth) deepestDepth = depth;
    
    for (const int &v : dg.adj(source)) {
        deepestDepthDfs(dg, v, depth+1);
    }
}

map<string, int> symTable;

int main()
{
    int n; cin >> n;
    
    Digraph dg(n+2);

	string s1, delim, s2;
	int v1, v2, m = 1;
	
    while (n--) {
        cin >> s1 >> delim >> s2;
        for (auto &c : s1) c = toupper(c);
        for (auto &c : s2) c = toupper(c);
        //~ cout << s1 << "  " << s2 << endl;
        
        v1 = symTable[s1];
        v2 = symTable[s2];
        
        if (v1 == 0) {
			v1 = m;
			symTable[s1] = m++;
		}
		
        if (v2 == 0) {
			v2 = m;
			symTable[s2] = m++;
		}
        //~ cout << v1 << "  " << v2 << endl;
        
        
        dg.addEdge(v2, v1);
        //~ cout << i << "  " << manager << endl;
    }
    
    // find deepest depth of the digraph
    // because POLYCARP is always in the first line second name it can be
    // hardcoded as the root node
	//~ cout << symTable["POLYCARP"] << endl;
    deepestDepthDfs(dg, 2);
    
    cout << deepestDepth;
}
