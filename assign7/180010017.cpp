// My acknowledgements for this code goes to GeeksForGeeks.com and Introduction To Algorihms (CLRS) book

#include<bits/stdc++.h>
using namespace std;

#define ll long long int
#define pi pair<int,int>
#define pii pair<int,pi>
#define mp make_pair

/*
	Krushkal's algorithm to find the Minimum Spanning Tree of the given connected edge-weighted undirected graph.

	Algo : Put all edges in a priority-queue and keep extracting the minimum weighted edge until the priority-queue is not empty. For each extracted edge, check if it forms a cycle. If it doesn't form a cycle, add the chosen edge to the Minimum Spanning Tree.

	Time Complexity : |E|log(|V|) using Disjoint Set Union, with Union By Rank and Path Compression.

	Union By Rank : Head of tree having more children becomes head of new tree formed by union of two trees.

	Path Compression : While finding parent of a tree, if the current node is not the child of its tree's parent, shift it so that it becomes so.

	Time Complexity of DSU using Path Compression and Union By Rank : alpha(m) Where m is number of times DSU is called and alpha is a function which returns value <= 4 for very large m.
*/

// change name to weighted graph
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
				rg[v].push_back(u);
				if(undirected)
					rg[u].push_back(v);
			}
		}
};

class graph_supporting_DSU{
    protected:
    	// parent[i]: holds index of parent
    	vector<int> parent, rank;
    public:
        graph_supporting_DSU(int vertices): parent(vertices+1), rank(vertices+1){
        	// initialise each vertex as parent of forest formed by itself.
            iota(parent.begin(), parent.end(), 0);
            // set size/rank of each forest formed by only one vertex as 1
            fill(rank.begin(), rank.end(), 1);
        }

        // returns the index of head of the forest which contains 'index'
        int findParent(int index){
        	// Using path compression, at each call, path from vertex to its parent is reduced
        	// if the queried vertex is direct child of the parent of the forest it is contained in, return its parent
        	if(parent[index] == index)
        		return index;
        	// else, make the forest's head as its parent, and return forest's head
        	parent[index] = this->findParent(parent[index]);
        	return parent[index];
        }

        // joins the two forest which contains vertices u and v
        void unionByRank(int u, int v){
        	// Using Union By Rank
        	int parent_of_u = findParent(u), parent_of_v = findParent(v);
        	// if the number of vertices in the forest headed by v, is more than that by u, make v as the head of forest formed by the union of the two forest.
        	if(rank[parent_of_v] > rank[parent_of_u])
        		parent[parent_of_u] = parent_of_v;
        	else
        		parent[parent_of_v] = parent_of_u;
        }

        bool createsCycle(int u, int v){
        	int parent_of_u = findParent(u), parent_of_v = findParent(v);
        	// if both the vertices belong to same forest, adding edge between them will form a cycle
        	if(parent_of_v == parent_of_u)
        		return true;
        	return false;
        }
};

// Multiple inheritance, using class graph to store final result, class graph_supporting_DSU to store final MST
class graph_supporting_finding_MST: public graph, public graph_supporting_DSU{
	protected:
		// priority_queue using min heap containing pair (weight => (from, to))
		priority_queue<pii, vector<pii>, greater<pii> > edge, ans;
	public:
		// Call constructors of super class using list initialisers
		graph_supporting_finding_MST(int vertices): graph(vertices), graph_supporting_DSU(vertices) {
			// do nothing
		}

		// taking edges of original graph and storing it
		void add_edge(int from, int to, int weight){
			edge.push(make_pair(weight,make_pair(from,to)));
		}

		// returns the MST formed
		priority_queue<pii, vector<pii>, greater<pii> > returnMST(){
			while(edge.empty() == false){
				// pick the edge with min weight
				auto curEdge = edge.top();
				edge.pop();

				int weight = curEdge.first, from = curEdge.second.first, to = curEdge.second.second;

				// if adding that edge to currently formed spanning tree, creates a cycle, ignore it
				if(createsCycle(from, to))
					continue;

				// else, add it to the set of edges of currently formed spanning tree
				// graph::add_edge(from, to);
				ans.push(make_pair(weight, make_pair(from, to)));
				// and update its parent, and forest so that cycle formation checking becomes faster.
				unionByRank(from, to);
			}
			return ans;
		}
};


void solveAssignment(char**argv){
	const int N = 1e6 + 2;
	graph_supporting_finding_MST grph(N);
	ifstream iff(argv[1]);	
	ofstream off("mst.txt");

	long long int from, to, weight, maxVertex=0;
	while(iff >> from >> to >> weight){
		grph.add_edge(from, to, weight);
		maxVertex = max({maxVertex, from, to});
	}
	auto ans = grph.returnMST();
	while(ans.empty() == false){
		auto curEdge = ans.top();
		ans.pop();

		int weight = curEdge.first, from = curEdge.second.first, to = curEdge.second.second;
		off << from << ' ' << to << ' ' << weight << '\n';
	}	
	iff.close();
	off.close();

}

int main(int argc, char**argv){

	solveAssignment(argv);

	return 0;
}