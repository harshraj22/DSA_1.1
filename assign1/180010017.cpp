#include<bits/stdc++.h>
using namespace std;

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

// ------------------------ End Of Stack Class -----------------------------------------


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

// ------------------------- End Of Queue Class -----------------------------------------



template<typename T>
class Doubly_linked_list{
private:
	struct node{
		T data;
		node* prev;
		node* next;
	};

	node* head;
	ofstream output_list;
	void add(T num){
		//inserting elements at head of list
		node* temp=head;
		//if the linked list is empty
		if(head==nullptr){
			head=new node;
			head->data = num;
		}
		else{
			temp = new node;
			temp->data = num;
			temp->next = head;
			head->prev = temp;
			head=temp;
		}
		
		output_list<<"inserted "<<num<<endl;
	}

	void erase(T num){
		node* temp=head;
		while(temp != nullptr){
			//when data to be deleted is found
			if(temp->data==num){
				//if data to be erased is at head of the linked list
				if(temp->prev==nullptr)
					head=temp->next;
				//if data to be erased is just before tail
				else if(temp->next == nullptr)
						temp->prev->next=nullptr;
				else{
					//data to be deleted lies somewhere in between the extremes
					temp->prev->next=temp->next;
					temp->next->prev=temp->prev;
				}
				output_list<<"deleted "<<num<<endl;
				return;
			}
			//if not found,check next node
			else
				temp=temp->next;
		}
		output_list<<"cannot delete "<<num<<endl;
	}

	void search(T num){
		node* temp=head;
		//while we have not reached the tail of linked list
		while(temp!=nullptr){
			//if data to be searched is found
			if(temp->data==num){
				output_list<<"found "<<num<<endl;
				return;
			}
			else
				temp=temp->next;
		}
		//if while loop exits normally, the data to be searched isn't found
		output_list<<"not found "<<num<<endl;
	}

public:
	//constructor for initialising the linked list object
	Doubly_linked_list(){
		head=nullptr;
		output_list.open("dll.txt");
	}

	~Doubly_linked_list(){
		//don't forget to close the file you opened *_*
		output_list.close();
	}

	//print the whole linked list
	void print(){
		node* temp=head;
		//while the node contains data
		while(temp!=nullptr){
			output_list<<(temp->data)<<" ";
			temp=temp->next;
		}
		output_list<<endl;
	}

	//decide what operation to perform on the given input
	void operate(string s,T num){
		if(s[0]=='+')
			this->add(num);
		else if(s[0]=='-')
			this->erase(num);
		else if(s[0]=='?')
			this->search(num);
	}
};

// ------------------------- End Of Doubly Linked List Class -----------------------------

//for making command line argument availavble globally
char** argv;

void solve_stack(){
	//first argument is input file name(with address)
	ifstream input(argv[1]);

	string s;	int num;

	//creating an object of Stack class with data type as int
	Stack<int> st(stoi(argv[2]));

	//until EOF is reached
	while(input>>s){
		//if asked to print,no need to take number as input
		if(s[0]=='!')
			st.print();
		//take number as input and perform the required operation
		else{
			input>>num;
			st.operate(s,num);
		}
	}
}

void solve_queue(){
	//second argument gives the name of input file
	ifstream input(argv[1]);

	//initialise the size of queue using the third argument
	Queue<int> q(stoi(argv[2])+1);
	string s;	int num;

	//while there is any command left in the input file
	while(input>>s){
		//to show the stack in FIFO order
		if(s[0]=='!')
			q.print();
		else{
			//take the number as input and decide the operation
			input>>num;
			q.operate(s,num);
		}
	}
}

void solve_doubly_linked_list(){
	//second argument is the input file(along with path)
	ifstream input(argv[1]);

	//creating object of Doubly_linked_list class(here having int data type)
	Doubly_linked_list<int> dll;

	string s;	int num;
	//while there are commands left to be executed
	while(input>>s){
		//if the command is to print the list
		if(s[0]=='!')
			dll.print();
		else{
			//else take the number associated with the command as input and perform the required operation
			input>>num;
			dll.operate(s,num);
		}
	}
}

int main(int args, char ** kwargs){
	argv = kwargs;
	solve_stack();
	solve_queue();
	solve_doubly_linked_list();

	return 0;
}