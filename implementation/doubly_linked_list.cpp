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
    // index which points to memory next to last available element
    int tail_index;
public:
    Doubly_linked_list(){
        head = nullptr;
        tail = nullptr;
        tail_index = 0;
    }
};

int main(){

    Doubly_linked_list<int> l;
    // l.insert(23,0);
    // cout<<l.at(0)<<"\n";
    // l.remove(34);
return 0;
}