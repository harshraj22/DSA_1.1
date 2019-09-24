// Radix sort implementation using stable sorting method of counting sort which takes O(n+k)
// time complexity of radix sort O(d*(n+k)), where d is number of digits in the largest input integer, n is number of integers, and k ig the largest input integer

#include<bits/stdc++.h>
using namespace std;

// Think about a friend class doing sorting here (or a static method)

class counting_sort{
    protected:
        vector<string> vec;

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
            // do nothing
        }
        void sort_by(int ind){
            // fill
            sort_on(ind);
        }
        vector<string> return_sorted(){
            return vec;
        }
};

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

int main(){
    int n,sz;
    string s;
    cout << "Enter number of integers :\n";
    cin >> n;
    assert(n>0);
    vector<string> v(n);
    cout << "Now enter size of each integers :\n";
    cin >> sz;
    cout << "Now enter the integers :\n";
    for(int i=0;i<n;i++){
        cin >> v[i];
        assert(v[i].size()==sz);
    }
    radix_sort radixObject(v);
    radixObject.sort();
    cout << "The sorted numbers are : \n";
    radixObject.print();

    return 0;
}
