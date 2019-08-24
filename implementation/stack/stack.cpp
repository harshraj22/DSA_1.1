//to make our stack support different data types
template<typename T>
class Stack{
private:
	vector<T> v;
	int head,tail,size;
	ofstream output_stack;
	//add elements to stack
	void push(T num){
		//if stack is full
		if(tail==size)
			output_stack<<"overflow\n";
		else{
			//add elements to defined place in stack
			v[tail]=num;
			//shift tail to next position
			tail += 1; //(tail+1)%size;
			//print the message that it is pushed successfully
			output_stack<<"pushed "<<num<<endl;
		}
	}

	//to search for the given data in our stack
	void search(T num){
		for(int i=head;i!=tail;i+=1)
			if(v[i]==num){
				output_stack<<"found "<<num<<endl;
				return ;
			}
		//if the for loop exits normally, the data must have not been found
		output_stack<<"not found "<<num<<endl;
		return;
	}


	void pop(T num){
		if(tail==head){
			output_stack<<"underflow\n";
			return;
		}
		else{
			tail -= 1;
			output_stack<<"popped "<<v[tail]<<endl;
		}
	}

public:
	//constructor to initialise the stack size
	Stack(int size){
		v.resize(size,0);
		head=tail=0;
		this->size=size;
		output_stack.open("stack.txt");
	}

	~Stack(){
		//don't forget to close the file you opened *_*
		output_stack.close();
	}

	//print the whole stack
	void print(){
		//to maintain LIFO order, we need to print in reversed order
		vector<T> var;
		for(int i=head;i!=tail;i++)
			var.emplace_back(v[i]);
		//reverse the array(vector)
		reverse(var.begin(), var.end());
		//print the reversed vector
		for(auto it:var)
			output_stack<<it<<" ";
		output_stack<<endl;
	}

	void operate(string s,T num){
		//calling private methods on self object using 'this' pointer
		if(s[0]=='+')
			this->push(num);
		else if(s[0]=='?')
			this->search(num);
		else if(s[0]=='-')
			this->pop(num);
	}
};