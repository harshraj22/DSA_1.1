// My acknowledgement for this assignment goes to GeeksForGeeks and CLRS (Introduction To Algorithms). Also lots of thanks to stackoverflow for revising me about cool stuffs about OOPS.

#include<bits/stdc++.h>
using namespace std;

// Using class based template implementation to better understand the object oriented concepts

/*
	Dijkstra Algorithm to find the single source shortest path.
	Time complexity using Fibonacci heap : (|E| + |V|log|v|)
	Time complexity using Binary heap : ((|E| + |v|)log|v|)

	std::priority_queue uses Binary heap

	Algo : 
		Mark the distance from source of all vertices as infinity initially. Also mark the distance of source as 0. Visit the source vertex and relax all the neighbouring vertices. Add all the vertices that are relaxed to priority queue (min heap on weight). When extracting the most prior vertex, mark it as visited. If the extracted vertex is already visited, ignore it. Repeat this until priority queue is empty.
*/


const int N = 1e4;
long long int inf = 1e15;

// T is expected to be int or long long int, using static_assert for the same
template<typename T>
class safeGraph{
	protected:
		// Adjacency list to store pair(node, weight)safeGraph
		vector<pair<T,T> > gr[N];
		// infinity
		T inf;
	public:
		safeGraph(T vertices){
			// check for template to be only of type 'int' or 'long long int'
			static_assert(std::is_same<T,int>::value || std::is_same<T,long long int>::value, "Type not matched");
			// if template type is 'int', use lower value of inf
			if(typeid(T) == typeid(int)){
				inf = 0x3f3f3f3f;
			}
			else if(typeid(T) == typeid(long long int)){
				// for 'long long int', we need different value of inf
				inf = 0xFFFFFFFFFFFFFFFL;
			}
			else{
				// Not possible, already used static_assert
			}
		};

		void add_edge(T from, T to, T weight, bool directed=false){
			gr[from].push_back(make_pair(to, weight));
			if(directed == false)
				gr[to].push_back(make_pair(from, weight));
		}

		~safeGraph(){
			// Do nothing
		};	
};

template<typename T>
class dijkstra:public safeGraph<T>{
	private:
	protected:
		// stores the smallest weights from source
		vector<T> weights;
		// tells if the smallest distance from source to 'index' has been already found
		vector<bool> visited;
		// to choose the next vertex to be relaxed (min heap using weights as key)
		priority_queue<pair<T, T>, vector<pair<T,T> >, greater<pair<T, T> > > pq;
	public:
		dijkstra(T vertices):safeGraph<T>(vertices),weights(vertices, inf),visited(vertices,false){
			// 
		}

		void add_edge(T from, T to, T weight, bool directed=false){
			safeGraph<T>::add_edge(from, to, weight, directed);
		}

		vector<T> returnWeights(int source){
			// mark distance of source as 0
			weights[source] = 0;
			// add source to priority queue (pair of weight, node)
			pq.push(make_pair(0, source));

			while(pq.empty() == false){
				// while some elements are left to be processed
				// take the edge with min priority
				pair<T,T> cur = pq.top();
				// remove the selected edge
				pq.pop();

				T curWeight = cur.first;
				T node = cur.second;

				// if the minimum distance to current vertex has already been calculated, ignore
				if(visited[node] == true)
					continue;

				visited[node] = true;

				// Iterate over all the neighbours (node, weight) pair of the current node
				// reason for using 'this' pointer even after inheriting the class : https://stackoverflow.com/questions/4643074/why-do-i-have-to-access-template-base-class-members-through-the-this-pointer
				for(auto neighbour:this->gr[node]){
					T neighbourWeight = neighbour.second;
					T neighbourNode = neighbour.first;

					// if there exists a path going through the current node to its neighbour having less distance
					if(weights[neighbourNode] > weights[node] + neighbourWeight){
						weights[neighbourNode] = weights[node] + neighbourWeight;

						// add the modified neighbour to the priority queue
						pq.push(make_pair(weights[neighbourNode], neighbourNode));
					}
				}
			}

			return weights;
		}
};

int main(int argc, char**argv){
	dijkstra<long long int> myGraph(N);

	ifstream iff(argv[1]);
	ofstream off("dijkstra.txt");
	int source = stoi(argv[2]);
	int from, to, weight, maxVertex=0;

	while(iff >> from >> to >> weight){
		myGraph.add_edge(from, to, weight, true);
		maxVertex = max({maxVertex, from, to});
	}

	auto shortesWeights = myGraph.returnWeights(source);
	for(int i=0;i<= maxVertex;i++){
		if(shortesWeights[i] >= inf)
			shortesWeights[i] = -1;
		off << i << ' ' << shortesWeights[i] << '\n';
	}

	iff.close();
	off.close();

	return 0;
}



/*
	Initialise a const private variable using list initialisation, but check type of template before initialising

*/