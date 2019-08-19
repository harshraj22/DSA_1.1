#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

template<typename T>
class Doubly_linked_list{
private:
    struct node{
        T data;
        node * prev;
        node * next;
    };
    node * head;
    node * tail;
    // index which points to memory to last available element
    int tail_index;
public:
    Doubly_linked_list(){
        head = nullptr;
        tail = nullptr;
        tail_index = -1;
    }
    int size(){
        return tail_index+1;
    }
    bool empty(){
        return tail_index == -1;
    }
    void insert(T value,int pos){
        //if trying to insert outside the extremas of current linked list
        if(pos>tail_index+1 || pos<0){
            cout<<"Can't insert outside the bounds\n";
            raise(SIGSEGV);
        }
        else if(pos==0){
            // adding element at the head
            if(head==nullptr){
                // linked list is empty
                head=new node;
                head->data = value;
                tail_index +=1;
                return;
            }
            // linked list is not empty
            node* temp = new node;
            temp->data = value;
            temp->next = head;
            head->prev = temp;
            head = temp;
            tail_index +=1;
            return;
        }
        else if(pos==tail_index){
            // adding elements at tail
            node * temp=head;
            while(temp->next != nullptr)
                temp = temp->next;
            // create a new structure to be placed at index pos, pointer to which is 'var'
            node *var=new node;
            var->data = value;
            // add link to new data to be inserted at index 'pos' and data in linked list at index 'pos-1'
            temp->prev->next = var;
            var->prev = temp->prev;
            // add link to new data to be inserted at index 'pos' and data in current linked list at index 'pos'
            var->next = temp;
            temp->prev = var;
            
            tail_index +=1;
            return;
        }
        else if(pos==tail_index+1){
            // adding elements after tail
            node * temp = head;
            while(temp->next != nullptr)
                temp =temp->next;
            temp->data = value;
            tail_index +=1;
            return ;
        }
        else {
            // adding elements in the middle
            node * temp = head;
            int cur_index = 0;
            // temp points to structure at index pos
            while(cur_index < pos){
                cur_index += 1;
                temp = temp->next;
            }
            // create a new structure to be placed at index pos, pointer to which is 'var'
            node * var = new node;
            var->data = value;
            // add link to new data to be inserted at index 'pos' and data in linked list at index 'pos-1'
            temp->prev->next = var;
            var->prev = temp->prev;
            // add link to new data to be inserted at index 'pos' and data in current linked list at index 'pos'
            temp->next->prev = var;
            var->next = temp->next;

            tail_index +=1;
            return;
        }
    }
    T at(int pos){
        if(pos>tail_index || pos<0){
            cout<<"Can't access unavailable indexes\n";
            raise(SIGSEGV);
        }
        node *temp = head;
        int cur_index=0;
        while(cur_index!=pos){
            cur_index+=1;
            temp=temp->next;
        }
        return temp->data;
    }
};

int main(){
/*
    // Test cases :
    Doubly_linked_list<int> l;
    l.insert(23,0);
    cout<<"size of linked list is "<<l.size()<<'\n';
    l.insert(24,0);
    cout<<"size of linked list is "<<l.size()<<'\n';
    l.insert(25,1);
    cout<<"size of linked list is "<<l.size()<<'\n';

    for(int i=0;i<l.size();i++)
        cout<<"value at "<<i<<" is "<<l.at(i)<<endl;

    // l.insert(26,-1);
    // cout<<"size of linked list is "<<l.size()<<'\n';
    // l.insert(27,2);
    // cout<<"size of linked list is "<<l.size()<<'\n';
    // l.insert(28,12);
    // cout<<"size of linked list is "<<l.size()<<'\n';

*/
/*
    Causion:
    Need to handle cases where typecasting of data happens,for example,
    Doubly_linked_list<int> l;
    l.insert('a',0);
    l.insert(2.3,0);
*/
return 0;
}