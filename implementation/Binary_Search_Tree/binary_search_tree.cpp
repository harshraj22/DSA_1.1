#include<bits/stdc++.h>
using namespace std;

template<typename T>
class Binary_Search_Tree{
private:
    struct node{
        T data;
        node * parent;
        node * left;
        node * right;
    };

    node * head;
    Binary_Search_Tree(){
        head = nullptr;
    }
public:
    void insert(T value);
    void erase(T value);
    bool search(T value);
    vector<T> inorder();
    vector<T> postorder();
    vector<T> preorder();

};

int main(){

    return 0;
}