#include<bits/stdc++.h>
using namespace std;

class graph{
    protected:
        vector<vector<int> > gr;
        vector<int> visited;
    public:
        graph(int vertices){
            gr.resize(vertices,vector<int>());
            visited.resize(vertices,-1);
        }

        void add_edge(int par,int child,bool directed=false){
            gr[par].push_back(child);
            if(!directed)
                gr[child].push_back(par);
        }
};

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