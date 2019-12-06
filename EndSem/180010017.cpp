// [done] create description.txt and explain
//[done] see num _of_nodes is not the last node, see eval_girth function


#include<bits/stdc++.h>
using namespace std;

#define ll long long int

// Do not hardcode values !
#define inf 0x3f3f3f3f
const int N = 10004;
const int Assumed_size = 500;
// vector<vector<int> > graph;
vector<int> graph[N];
int dist[Assumed_size][Assumed_size];

int numOfNodes=0,numOfEdges=0,minDeg=1e8,maxDeg=0,radious=inf,diameter=0,girth=inf,cur_girth=0;

vector<bool> vis(N,false);
vector<int> bfs_dist(N,inf);

// contains all nodes
set<int> st;
set<pair<int,int> > stt;

void count_nodes_edges(){
	// for(int i=0;i<graph.size();i++){
	for(int i=0;i<10004;i++){
		for(auto it:graph[i]){
			st.insert(it);
			stt.insert(make_pair(i,it));
			minDeg = min(minDeg, (int)graph[i].size());
			maxDeg = max(maxDeg, (int)graph[i].size());
		}
	}
	numOfNodes = st.size();
	// each edge will be counted twice (u,v) and (v,u), so divide by 2
	numOfEdges = (int)stt.size()/2;
	if(st.size()==0){
		// if there is no edge in graph
		minDeg = 0;
		maxDeg = 0;
	}
}

// floyd warshall O(n3) to find min dist between each pair of nodes
void floyd(){
	for(int k=0;k<=numOfNodes;k++){
		for(int i=0;i<=numOfNodes;i++){
			for(int j=0;j<=numOfNodes;j++){
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	for(int i=0;i<=numOfNodes;i++){
		int cur_row_max = 0;
		// cur_row_max represents the eccentricity of 'i'th vertex
		//  i.e. the distance of farthest node from 'i'th node. Since graph is connected, all nodes have a finite distance between them.
		for(int j=0;j<=numOfNodes;j++){
			// if node labels 'i' and 'j' exist ( in first input label '0' doesn't exists )
			if(st.find(i) != st.end() && st.find(j) != st.end()){
				// i!=j as eccentricity is min dist between a vertex and any 'other' vertex
				if(dist[i][j] < inf && dist[i][j] > 0 && i!=j){
					// update the eccentricity of current vertex
					cur_row_max = max(cur_row_max, dist[i][j]);
				}
			}
		}
		if(cur_row_max < inf && cur_row_max > 0){
			// diameter and radious calculate as per definition
			diameter = max(diameter, cur_row_max);
			radious = min(radious, cur_row_max);
		}
	}
	// radious is the min of max of each row 
	// diameter is the max of min of each row
}

// custom function to check errors
void print_flood(){
	for(int i=0;i<numOfNodes;i++){
		for(int j=0;j<=numOfNodes;j++)
			cout << dist[i][j] << " \n"[j==numOfNodes];
	}
}

void bfs(int node){
	// do a bfs over the graph to detect cycle, if a visited node is reachable while bfs (and the reachable node is not parent of current node, we found a cycle)
	queue<int> q;
	q.push(node);

	vis[node] = true;
	// stores the shortest distance of 'node' from 'source' while bfs
	bfs_dist[node] = 0;

	// stores the parent of 'node' in the bfs tree
	vector<int> par(N);

	// mark each 'node' as its parent (i.e. par[i] = i)
	iota(par.begin(), par.end(),0);
	par[node] = 0;

	// typical bfs
	while(q.empty() == false){
		int cur = q.front();
		q.pop();

		// for all neighbours of current node
		for(auto it:graph[cur]){
			// if the neighbour is visited, either we found a cycle, or current node's parent in bfs tree
			if(vis[it]){
				// if(abs(bfs_dist[cur]-bfs_dist[it]) >= 3){
				if(it != par[cur]){
					// if we found a cycle, update the girth
					girth = min(girth, bfs_dist[cur] + bfs_dist[it] + 1);
				}
				continue;
			}
			vis[it] = true;
			par[it] = cur;
			q.push(it);
			bfs_dist[it] = 1 + bfs_dist[cur];

		}
	}
}

/*
void dfs(int node, int par=-1){
	cout << "inside dfs " << node << " " << par << "\n";
	if(vis[node] == true){
		girth = min(girth, cur_girth);
		return;
	}
	vis[node] = true;
	cur_girth += 1;

	for(auto it:graph[node]){
		if(it==par)
			continue;
		// for each neighbour of current node
		dfs(it, node);
	}

	// vis[node] = false;
	cur_girth -= 1;
	return;
}
*/

// girth is defined as no of vertices in the shortest cycle
void eval_girth(){
	for(int i=0;i<=numOfNodes;i++){
		if(st.find(i) != st.end()){
			// if 'i' is the node present in the graph
			cur_girth = 0;
			fill(vis.begin(), vis.end(), false);
			fill(bfs_dist.begin(), bfs_dist.end(), inf);
			// bfs_dist[i] = 0;
			// dfs(i);
			bfs(i);
		}
	}
}


int main(int argc, char**argv){
	ifstream input(argv[1]);
	ofstream output("parameters.txt");
	int u,v;
	for(int i=0;i<Assumed_size;i++)
		for(int j=0;j<Assumed_size;j++)
			dist[i][j] = inf;

	while(input >> u >> v){
		graph[u].push_back(v);
		graph[v].push_back(u);
		st.insert(u);
		st.insert(v);
		dist[u][v] = 1;
		dist[v][u] = 1;
	}

	count_nodes_edges();
	output << numOfNodes << "\n" << numOfEdges << "\n";
	output << minDeg << "\n" << maxDeg << "\n";
	floyd();
	output << radious << "\n" << diameter << "\n";
	eval_girth();
	// print_flood();
	// if there is no cycle, girth is -1
	if(girth >= inf)
		girth = -1;
	output << girth << "\n";

	return 0;	
}