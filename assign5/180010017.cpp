// Acknowledgements to StackOverFlow and CLRS (Introduction to Algorithms)
// Radix sort implementation using stable sorting method of counting sort which takes O(n+k)
// time complexity of radix sort O(d*(n+k)), where d is number of digits in the largest input integer, n is number of integers, and k ig the largest input integer

#include<bits/stdc++.h>
using namespace std;

ofstream off("radix.txt");
#define cout off

// Think about a friend class doing sorting here (or a static method)

class counting_sort{
    protected:
        vector<string> vec;

        // This function sorts the numbers based on the ind'th significant digit
        void sort_on(int ind){
            vector<vector<string> > v(10);
            for(auto it:vec){
                int index = it[ind] - '0';
                v[index].push_back(it);
            }
            vec.clear();
            for(auto it:v){
                for(auto iit:it)
                    vec.push_back(iit);
            }
        }

    public:
        counting_sort(vector<string> v):vec(v){
            // Constructor using initialiser list 
        }
        void sort_by(int ind){
            sort_on(ind);
        }
        vector<string> return_sorted(){
            return vec;
        }
};

// Could have used inheritance instead.
class radix_sort{
    private:
        vector<string> vec;
        counting_sort countObject;
    public:
        radix_sort(vector<string> v)
            :vec(v),countObject(v){
            // do nothing, using initialiser list;
            // counting_sort countObject(v);
        }
        void sort(){
            int lim = vec[0].size();
            for(int i=lim-1;i>=0;i--)
                countObject.sort_by(i);
            vec = countObject.return_sorted();
        }
        void print(){
            for(auto it:vec)
                cout << it << endl;
        }

};

int main(int argc,char ** argv){
    int n,sz;
    string s;
    ifstream iff(argv[1]);
    #define cin iff
    sz = stoi(argv[2]);
    vector<string> v;
    while(cin){
        int i;
        cin >> s;
        v.push_back(s);
    }

    v.pop_back();

    radix_sort radixObject(v);
    radixObject.sort();
    radixObject.print();

    return 0;
}