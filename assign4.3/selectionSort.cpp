#include<bits/stdc++.h>
using namespace std;

// Selection sort O(n^2)

class selectionSort{
    private:
        vector<int> vec;
    public:
        selectionSort(vector<int> v):vec(v){
            // do nothing
        }
        void sort(){
            int n = vec.size();
            for(int i=0;i<n;i++){
                int minIndex=i;
                for(int j=i+1;j<n;j++){
                    if(vec[j] < vec[minIndex])
                        minIndex = j;
                }
                swap(vec[i],vec[minIndex]);
            }
        }
        void print(){
            for(auto it:vec)
                cout << it << " ";
            cout << endl;
        }
};

int main(){
    vector<int> v{3,4,7,8,9,12,8,0,2,12,234,2345,56};
    selectionSort sortObject(v);
    sortObject.sort();
    sortObject.print();

    return 0;
}