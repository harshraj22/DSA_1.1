// Again OOPS based model using inheritance to understand it better.

/*
    Things learnt :
        1.Calling parameterise constructor of base class (use of initialiser list rather than calling from constructor of derived class);
*/

#include<bits/stdc++.h>
using namespace std;

class container{
    protected:
        vector<int> vec;
    public:
        container(vector<int> arr){
            vec = arr;
        }
};

class mergeSort : public container{
    public:
        // call constructor of base class using initialiser list else derived class tries to call defaul constructor of base class before calling the constructor of itself and since the default constructor of base class has bee overridden, it gives error. 
        mergeSort(vector<int> vec):
            container(vec){
                inf = 1e17;
            // container(arr)
        }
        vector<int> sort(){
            // Remember type of vec.size() is size_t (type of unsigned int) and for this type 1-1 is overflow(resulting in negative int ) rather than 0;
            splitAndSort(0,(int)vec.size()-1);
            return vec;
        }
    private:
        long long int inf;
        void splitAndSort(int l,int r){
            if(l==r)
                return;
            int mid = (l+r)/2;
            splitAndSort(l,mid);
            splitAndSort(mid+1,r);
            mergeArray(l,mid,r);
        }
        void mergeArray(int l,int mid,int r){
            vector<int> a(mid-l+1);
            vector<int> b(r-mid);
            for(int i=0;i<a.size();i++)
                a[i] = vec[i+l];
            for(int i=0;i<b.size();i++)
                b[i] = vec[i+mid+1];
            a.push_back(inf);
            b.push_back(inf);

            for(int i=l,ap=0,bp=0;i<=r;i++){
                if(a[ap] < b[bp]){
                    vec[i] = a[ap];
                    ap += 1;    
                }
                else {
                    vec[i] = b[bp];
                    bp += 1;
                }
            }
        }
};

int main(){
    vector<int> arr{3,4,0,3,7,8,-5};
    mergeSort mergeObject(arr);
    auto newArray = mergeObject.sort();
    for(auto it:newArray)
        cout << it << " ";
    cout << endl;

    return 0;
}