// My acknowledgements to stack overflow for help in OOPS, GeeksForGeeks and CLRS for Algorithm
// Object Oriented Model of Inheritence

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
				rg[v].push_back(u);
				if(undirected)
					rg[u].push_back(v);
			}
		}
};

// public inheritance of graph class
class modifiedGraph:public graph{
	protected:
		// boolean vector to check if a vertex is visited during BFS/DFS Traversal
		vector<bool> visited;
		// Vector of integers to store the shortest distance from source vertex
		vector<int> distance;
		// Vector of integers to store the topological sort of given graph
		vector<int> topological_order;

		int max_present_vertex;

	public:
		modifiedGraph(int vertices):graph(vertices),
			visited(vertices+1), distance(vertices+1,-1){
				// do nothing, used list initialisation
		}

		void add_max_present_vertex(int value){
			max_present_vertex = value;
		}

		vector<int> shortest_distance_bfs(int source){
			// returns shortest distance of each vertex from given source, uses BFS internally

			// mark distance of each node from source as -1 initially
			fill(distance.begin(), distance.end(), -1);
			// mark all vertices as un-visited
			fill(visited.begin(), visited.end(), false);
			
			queue<int> q;
			// distance of source from itself is 0
			distance[source] = 0;
			// mark source vertex as visited
			visited[source] = true;
			q.push(source);

			while(q.empty() == false){
				int cur_edge = q.front();
				q.pop();

				// for all vertex that are neighbours of current edge being evalueated
				for(auto neighbours:gr[cur_edge]){
					// if they have been already visited, the shortes path to them has been found, so don't visit them
					if(visited[neighbours] == true)
						continue;
					distance[neighbours] = distance[cur_edge] + 1;
					visited[neighbours] = true;
					// push neighbours into the queue, so that its neighbours can be visited.
					q.push(neighbours);
				}
				// when all connected vertices have been visited (i.e. shortest distance from source to them has been found out), the loop terminates.
			}
			// return the calculated distance
			return distance;
		}

		void dfs(int node,int time=0){
			time += 1;
			// mark the current node as visited
			visited[node] = true;

			// for all neighbours of the current node
			for(int neighbours:gr[node]){
				// if the neighbour hasn't been visited
				if(visited[neighbours] == false)
					// do a recursive dfs on it. When this call is returned, the neighbour has been completely discovered and added to the stack finish_time
					this->dfs(neighbours, time);
			}

			time += 1;
			topological_order.push_back(node);
		}

		vector<int> topological_sort_dfs(){

			fill(visited.begin(), visited.end(), false);

			// for all vertices in the graph
			for(int i=0;i<=max_present_vertex; i+=1){
				// if the current vertex has not been visited in previous dfs calls
				if(visited[i] == false)
					// do a dfs using that vertex as root
					dfs(i);
			}

			return topological_order;
		}

};


int main(int argc, char** argv){

	ifstream iff(argv[1]);
	ofstream sd("sd.txt");
	ofstream ts("ts.txt");

	int u, v, source = stoi(argv[2]), vertices = 1e4, max_num_of_vertex = 0;

	modifiedGraph newGraph(vertices);	

	while(iff >> u >> v){
		// we build reverse graph also, to help us do topological sorting
		newGraph.add_edge(u, v, false, false);
		max_num_of_vertex = max({max_num_of_vertex, u, v});
	}

	newGraph.add_max_present_vertex(max_num_of_vertex);

	vector<int> shortest_dist = newGraph.shortest_distance_bfs(source);
	for(int vertex = 0;vertex <= max_num_of_vertex; vertex += 1){
		sd << vertex << ' ' << shortest_dist[vertex] << '\n';
	}

	vector<int> topo_sort = newGraph.topological_sort_dfs();
	for(int vertex = max_num_of_vertex ;vertex >= 0; vertex -= 1){
		ts << topo_sort[vertex] << '\n';
	}

	// don't forget to close the if/of streams *_*
	iff.close();
	sd.close();
	ts.close();

	return 0;
}