#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <algorithm>

using namespace std;

class Graph
{
public:
	Graph(istream &is)
	{
		is >> size;
		//~ cout << size;
		
		for (size_t i = 0; i < size; ++i) is >> symTable[i];
		//~ for (auto const &el : symTable) cout << el.second << " ";
		
		// fill adjacency matrix
		adjMatrix.reserve(size);
		for (size_t i = 0; i < size; ++i) {
			vector<bool> vec;
			adjMatrix.push_back(vec);
			adjMatrix[i].reserve(size);	
			
			for (size_t j = 0; j < size; ++j) {
				char val;
				is >> val;
				bool v = atoi(&val);
				adjMatrix[i].push_back(v);
			}
		}
		
		//~ for (auto const &row : adjMatrix) {
			//~ for (auto const &cell : row) cout << cell;
			//~ cout << endl;
		//~ }
	}
	
	vector<int> adj(const int &v) const
	{
		vector<int> adjV;
		
		for (size_t i = 0; i < adjMatrix[v].size(); ++i) {
			if (adjMatrix[v][i] == true) adjV.push_back(i);
		}
		
		return adjV;
	}
	
	int getSym(const int &v) { return symTable[v]; }
	void setSym(const int &v, const int val) { symTable[v] = val; } 
	size_t getSize() const { return size; }
	
private:
	size_t size;
	map<int, int> symTable;
	vector< vector<bool> > adjMatrix;
};

class CC
{
public:
	CC(const Graph &g) : count(0)
	{
		for (size_t i = 0; i < g.getSize(); ++i) {
			marked.push_back(false);
			ids.push_back(0);
		}
		
		for (size_t i = 0; i < g.getSize(); ++i) {
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
	Graph g(cin);
	
	//~ auto o = g.adj(3);
	//~ for (auto &p : o) cout << p << " ";
	
	CC cc(g);
	
	//~ cout << cc.getCount() << " components." << endl;
	//~ for (size_t i = 0; i < g.getSize(); ++i) {
		//~ cout << cc.getId(i) << " ";
	//~ }
	
	// get components:
	map< int, vector<int> > components;
	for (int i = 0; i < cc.getCount(); ++i) {
		vector<int> vec;
		components[i] = vec;
	}
	
	for (size_t i = 0; i < g.getSize(); ++i) {
		components[cc.getId(i)].push_back(i);
	}
	
	// print:
	//~ int itr = 1;
	//~ for (const auto &compt : components) {
		//~ cout << "Component " << itr++ << ": ";
		
		//~ for (const auto &v : compt.second) 
			//~ cout << "(" << v << ", " << g.getSym(v) << ") ";
		
		//~ cout << endl;
	//~ }
	
	// sort each component and place them in order
	for (int i = 0; i < cc.getCount(); ++i) {
		vector<int> vals;
		
		for (const auto &v : components[i]) {
			vals.push_back(g.getSym(v));
		}
		
		sort(vals.begin(), vals.end());
		
		int j = 0;
		for (const auto &v : components[i]) {
			g.setSym(v, vals[j++]);
		}
	}
	//~ cout << "AFTER SORT: " << endl;
	//~ itr = 1;
	//~ for (const auto &compt : components) {
		//~ cout << "Component " << itr++ << ": ";
		
		//~ for (const auto &v : compt.second) 
			//~ cout << "(" << v << ", " << g.getSym(v) << ") ";
		
		//~ cout << endl;
	//~ }
	
	for (size_t i = 0; i < g.getSize(); ++i) {
		cout << g.getSym(i) << " ";
	}
}
