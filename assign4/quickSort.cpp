#include<bits/stdc++.h>
using namespace std;

template <typename T>
class container{
    protected:
        vector<T> vec;
    public:
        container(vector<T> arr){
            vec = arr;
        }
};

// have a look at : https://stackoverflow.com/questions/4643074/why-do-i-have-to-access-template-base-class-members-through-the-this-pointer for excuse of excessive use of 'this' pointer
template<typename T>
class quickSort : public container<T>{
    public:
        quickSort(vector<T> arr):
        container<T>(arr){
            // do nothing for now
        }    
        vector<T> sort(){
            doPartitionSort(0,(int)this->vec.size()-1);
            return this->vec;
        }
    private:
    void doPartitionSort(int l,int r){
        if(l >= r)
            return;
        int st = l,en = r-1;
        while(st < en){
            while(st < en && this->vec[st] <= this->vec[r])
                st += 1;
            while(en > st && this->vec[en] > this->vec[r])
                en -= 1;
            if(st < en)
                swap(this->vec[st],this->vec[en]);
        }
        if(this->vec[st] < this->vec[r])
            return;
        swap(this->vec[st],this->vec[r]);
        doPartitionSort(l,st-1);
        doPartitionSort(st+1,r);
    }
};

int main(){
    vector<int> arr{2,-3};
    quickSort<int> newObject(arr);
    auto v = newObject.sort();
    for(auto it:v)
        cout << it << " ";
    cout << endl;

    return 0;
}