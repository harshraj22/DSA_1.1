// Acknowledgements : Stackoverflow and Geeksforgeeks
// Again OOPS based model using inheritance to understand it better.

/*
    Things learnt :
        1.Calling parameterise constructor of base class (use of initialiser list rather than calling from constructor of derived class);
*/

#include<bits/stdc++.h>
using namespace std;

// this stores the data in vector for doing the sorting (the other container is implemented using template to understand the difference of template while using inheritance)
class container1{
    protected:
        vector<int> vec;
    public:
        container1(vector<int> arr){
            vec = arr;
        }
};

class mergeSort : public container1{
    public:
        // call constructor of base class using initialiser list else derived class tries to call defaul constructor of base class before calling the constructor of itself and since the default constructor of base class has bee overridden, it gives error. 
        mergeSort(vector<int> vec):
            container1(vec){
                inf = 1e17;
            // container1(arr)
        }
        // This method returns the sorted array of input integers
        vector<int> sort(){
            // Remember type of vec.size() is size_t (type of unsigned int) and for this type 1-1 is overflow(resulting in negative int ) rather than 0;
            splitAndSort(0,(int)vec.size()-1);
            return vec;
        }
    private:
        long long int inf;
        // This function splits the input array and recursively sorts them, then merges them
        void splitAndSort(int l,int r){
            // if there is only one element, it must be sorted
            if(l==r)
                return;
            int mid = (l+r)/2;
            // recursively sort the left and right halves
            splitAndSort(l,mid);
            splitAndSort(mid+1,r);
            // merge the two sorted array
            mergeArray(l,mid,r);
        }

        // This function merges the two sorted array to form one sorted array
        void mergeArray(int l,int mid,int r){
            vector<int> a(mid-l+1);
            vector<int> b(r-mid);
            for(int i=0;i<a.size();i++)
                a[i] = vec[i+l];
            for(int i=0;i<b.size();i++)
                b[i] = vec[i+mid+1];
            // assign last element to a very large number, in order to escape from lots of if-else statements while merging
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
            // remember the reasoning for type casting vec.size() (size_t type)
            doPartitionSort(0,(int)this->vec.size()-1);
            return this->vec;
        }
    private:
        // This function uses last element as pivot and breaks the input array into two halves where all elements are either greater or less than pivot and sorts them
        void doPartitionSort(int l,int r){
            if(l >= r)
                return;
            // we use two-references to indicate the elements that are less/greater than the pivot
            int st = l,en = r-1;
            while(st < en){
                while(st < en && this->vec[st] <= this->vec[r])
                    st += 1;
                while(en > st && this->vec[en] > this->vec[r])
                    en -= 1;
                if(st < en)
                    swap(this->vec[st],this->vec[en]);
            }
            if(this->vec[st] > this->vec[r])
                swap(this->vec[st],this->vec[r]);
            // else is for case when the pivot is the largest element in the given range. 
            else 
                st += 1;
            doPartitionSort(l,st-1);
            doPartitionSort(st+1,r);
        }
};

int main(int argc,char ** argv){
    ifstream iff(argv[1]);
    const int N = 1e6;
    vector<int> v(N);
    int i = 0;
    iff >> v[i++];
    while(iff.fail() == false){
        iff >> v[i];
        i += 1;
        // cout << i << endl;
    }
    v.resize(i-1);
    quickSort<int> newQuickObject(v);
    mergeSort newMergeSortObject(v);

    auto QuickSortedArray = newQuickObject.sort();
    auto MergeSortedArray = newMergeSortObject.sort();

    ofstream off("mergesort.txt");
    for(int j=0;j<i-1;j++)
        off << MergeSortedArray[j] << endl;
    off.close();

    ofstream of("quicksort.txt");
    for(int j=0;j<i-1;j++)
        of << QuickSortedArray[j] << endl;
    of.close();
    return 0;
}
