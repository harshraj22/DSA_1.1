#include<bits/stdc++.h>
using namespace std;

// Use of Inheritance revisited *_*
// Acknowledgements to GeeksForGeeks.com

// Basic block that holds the array with index pointing to the last element. (We couldn't use vector.size() for this due to our implementation)
template <typename T>
class array_implementation_of_tree{
	protected:
		// inherited private data can't be accessed from child class, thus making data protected is better idea if one doesn't want too much of getter-setter methods
		vector<T> v;
		// 'last' is the least index where data can be inserted (ie. this index is not a part of heap)
		T last;
	public:
		array_implementation_of_tree(){
			v.resize(0);
			this->last = 0;
		}

		~array_implementation_of_tree(){
			v.clear();
		}
};

// for output format
ofstream off("heap.txt");

template <typename T>
class heap : public array_implementation_of_tree <T>{
	// public inheritence : private becomes private, public becomes public and protected remains protected,
	private:
		// to return the index of parent of an index
		int par(int ind){
			if(ind % 2 == 0)
				return ind/2 -1;
			else 
				return ind/2 ;
		}
	public:
		// constructor to fix size of vector (vectors can't be infinitely large due to space issues)
		heap(int size = 0){
			this->v.resize(size,-1);
			this->last = 0;
		}

		void insert(T num){
			// increase the last element and push it up to its correct position
			increase_key(this->last,num);
			off << num << " inserted\n";
		}

		// to increase the value at node pointed by the index 'pos' in the array
		string increase_key(int pos,T num){
			// if the value to be increased is less than the value present there, don't do anything
			if(this->v[pos] > num)
				return to_string(num) + " is less than the current key at " + to_string(pos) + "\n";
			// if the value is inserted (ie. increased where there was no element present, increase the count of total nodes)
			if(pos >= this->last)
				this->last += 1;
			// else update the value
			this->v[pos] = num;
			int save = pos;
			// while the value at given index is greater than its parent
			while(pos > 0){
				// if value is less than it parent, heap is ok all over
				if(num < this->v[par(pos)])
					break;
				// swap value with parent (Greater value moves up the tree)
				swap(this->v[pos], this->v[par(pos)]);
				pos = par(pos);
			}
			return "Key at " + to_string(save) + " changed to " + to_string(num) + "\n";
		}

		string maximum(){
			// first element of heap is maximum element in the tree
			if(this->last <= 0)
				return "\n";
			else return to_string(this->v[0]) + "\n";
		}

		void extract_maximum(){
			off << maximum();
			// if heap is empty, return
			if(this->last == 0)
				return;
			this->last -= 1;
			// move the last element to the head of the tree and mark it's old place as empty (nullptr), and now rearrange the tree to move this smallest element to its correct position in the tree
			this->v[0] = this->v[this->last];
			// mark the last element's old place as empty
			this->v[this->last] = -1;
			max_heapify(0);
		}

		// the function assumes that left and right subtree are max heaps, and the abnormality is only due to element at index 'pos'
		void max_heapify(int pos){
			// if we try to call this function on nodes that doesn't exist
			if(pos >= this->last || 2*pos + 1 >= this->last)
				return ;
			// if only left child exists, don't check for right child
			else if(2*pos + 2 == this->last){
				// if parent is less than left child, swap them (remember std::swap uses reference, hence swap happens inplace)
				if(this->v[pos] < this->v[2*pos + 1])
					swap(this->v[pos],this->v[2*pos +1]);
				return;
			}
			
			// if both child exist, check if parent needs to be swapped with any one of them 
			int max_val = max({this->v[pos],this->v[2*pos+1],this->v[2*pos + 2]});
			if(max_val == this->v[pos])
				return ;
			else if(max_val == this->v[2*pos + 1]){
				swap(this->v[pos],this->v[2*pos +1]);
				this->max_heapify(2*pos + 1);
			}
			else {
				swap(this->v[pos], this->v[2*pos+2]);
				this->max_heapify(2*pos+2);
			}
		}

		vector<T> sort(){
			// we sort vector v inplace, the last part representing the sorted array, while left one representing the heap tree
			vector<T> temp = this->v;
			int unchanged = this->last;
			while(this->last){
				swap(this->v[0], this->v[this->last-1]);
				this->last -= 1;
				max_heapify(0);
			}
			swap(temp,this->v);
			swap(unchanged, this->last);
			// we need to resize as vector 'v' contains more elements than needed (extra space for new nodes)
			temp.resize(this->last);
			return temp;
		}
};

const int N = 1e6;

int main(int argc, char** argv){
	ifstream iff(argv[1]);
	#define cin iff

	heap<int> my_heap(N);
	while(cin){
		string s;
		int num, index;
		cin >> s;
		if(s == "insert"){
			cin >> num;
			my_heap.insert(num);
		}
		else if(s == "increase-key"){
			cin >> index >> num;
			off << my_heap.increase_key(index,num);
		}
		else if(s == "extract-max")
			my_heap.extract_maximum();
		else if(s == "maximum")
			off << my_heap.maximum();
		else if(s == "sort"){
			for(auto it: my_heap.sort())
				off << it << " ";
			off << "\n";
		}

	}

	// close the file before exiting
	iff.close();
	return 0;
}