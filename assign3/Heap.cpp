#include<bits/stdc++.h>
using namespace std;

template <typename T>
class array_implementation_of_tree{
	protected:
		vector<T> v;
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

ofstream off("heap.txt");
// #define off cout

template <typename T>
class heap : public array_implementation_of_tree <T>{
	private:
		int par(int ind){
			if(ind % 2 == 0)
				return ind/2 -1;
			else 
				return ind/2 ;
		}
	public:
		heap(int size = 0){
			this->v.resize(size,-1);
			this->last = 0;
		}

		void insert(T num){
			increase_key(this->last,num);
			// this->last += 1;
			off << num << " inserted\n";
		}

		string increase_key(int pos,T num){
			// if the value to be increased is less than the value present there, don't do anything
			if(this->v[pos] > num)
				return to_string(num) + " is less than the current key at " + to_string(pos) + "\n";
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
			this->v[0] = this->v[this->last];
			this->v[this->last] = -1;
			// if(this->last > 0)
			// 	this->last -= 1;
			max_heapify(0);
		}

		// there is problem as child of 0 are not 1,2 : use 1 based indexing to correct. or separate evaluation for parent
		void max_heapify(int pos){
			if(pos >= this->last || 2*pos + 1 >= this->last)
				return ;
			else if(2*pos + 2 == this->last){
				if(this->v[pos] < this->v[2*pos + 1])
					swap(this->v[pos],this->v[2*pos +1]);
				return;
			}
			
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
			// vector<T> vv = this->v;
			// vv.resize(this->last);
			// return vv;

			vector<T> temp = this->v;
			int unchanged = this->last;
			while(this->last){
				// cout << "v[0] is " << this->v[0] << endl;
				swap(this->v[0], this->v[this->last-1]);
				this->last -= 1;
				max_heapify(0);
			}
			swap(temp,this->v);
			swap(unchanged, this->last);
			temp.resize(this->last);
			// reverse(temp.begin(), temp.end());
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

	iff.close();
	return 0;
}