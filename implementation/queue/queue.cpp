
template<typename T>
class Queue{
private:
	vector<T> v;
	int head,tail,size;
	ofstream output_queue;

	//to push element to the stack
	void push(T num){
		//if stack is full
		if(tail+1==head)
			output_queue<<"overflow\n";
		else{
			//push the data into stack and increment the tail 
			v[tail]=num;
			tail = (tail+1)%size;
			output_queue<<"enqueued "<<num<<endl;
		}
	}

	void search(T num){
		//to search the given data in the stack
		for(int i=head;i!=tail;i=(i+1)%size)
			if(v[i]==num){
				output_queue<<"found "<<num<<endl;
				return ;
			}
		//if the for loop exits normally, the data must have not been found
		output_queue<<"not found "<<num<<endl;
		return;
	}

	void pop(){
		if(tail==head)
			output_queue<<"underflow\n";
		else {
			// tail = (size+tail-1)%size;
			output_queue<<"dequeued "<<v[head]<<endl;
			head = (head+1)%size;
		}
	}

public:
	//constructor to initialise the queue
	Queue(int size){
		v.resize(size);
		tail=head=0;
		this->size=size;
		output_queue.open("queue.txt");
	}

	~Queue(){
		//don't forget to close the file you opened *_*
		output_queue.close();
	}

	//print the queue in LIFO order
	void print(){
		for(int i=head;i!=tail;i=(i+1)%size)
			output_queue<<v[i]<<" ";
		output_queue<<endl;
	}

	//decide what operation to perform
	void operate(string s,T num){
		if(s[0]=='+')
			this->push(num);
		else if(s[0]=='?')
			this->search(num);
		else if(s[0]=='-')
			this->pop();
	}

};
