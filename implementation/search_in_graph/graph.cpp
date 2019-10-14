#include<bits/stdc++.h>
using namespace std;

class graph{
	protected:
		// graph represented as adjacency list
		vector<vector<int> > gr;
		// supports building reverse graph as well
		vector<vector<int> > rg;
	public:
		graph(int vertices)
			:gr(vertices+1), rg(vertices+1){
				// do nothing, used list initialisation
		}

		// add edge between vertices (u,v)
		void add_edge(int u, int v, bool undirected=false, bool reverse=false){
			gr[u].push_back(v);
			// if graph is undirected, use bidirectional edge
			if(undirected)
				gr[v].push_back(u);

			// if we also need to build the reverse graph
			if(reverse){
				rg[v].push_back(U);
				if(undirected)
					rg[u].push_back(v);
			}
		}
};

// public inheritence, thus protected data instead of private
class modified_graph: public graph{
    private:
    public:
        modified_graph(int vertices): graph(vertices){
            // do nothing
        }

};


int main(){
    

    return 0;
}