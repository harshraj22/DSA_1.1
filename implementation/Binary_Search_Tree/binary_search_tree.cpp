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
    int num_of_nodes;

    void _insert(T value,node* head){
        if(head->right==nullptr && (head->data)<value){
            head->right = new node;
            head->right->data = value;
            num_of_nodes += 1;
            return;
        }
        else if((head->data)<value)
            this->_insert(value,(head->right));
        else if(head->left==nullptr){
            head->left = new node;
            head->left->data = value;
            num_of_nodes += 1;
            return;
        }
        else this->_insert(value,(head->left));
    }

    bool _search(T value,node *head){
        if(head==nullptr)
            return false;
        else if((head->data) == value)
            return true;
        else if((head->data)<=value)
            return this->_search(value,head->right);
        else return this->_search(value,head->left);
    }

    vector<T> _inorder(node * new_head){
        vector<T> v;
        //if reached at the leaf node
        if(new_head==nullptr)
            return v;
        //recursively go to left subtree and find inorder traversal
        auto res=this->_inorder(new_head->left);
        v.insert(v.end(),res.begin(), res.end());
        v.push_back(new_head->data);
        //recursively go to right subtree and find inorder traversal
        auto res2=this->_inorder(new_head->right);
        v.insert(v.end(),res2.begin(), res2.end());
        return v;
    }

    vector<T> _preorder(node *new_head){
        vector<T> v;
        //if reached at the leaf node
        if(new_head==nullptr)
            return v;

        v.push_back(new_head->data);
        //recursively go to left subtree and find inorder traversal
        auto res=this->_inorder(new_head->left);
        v.insert(v.end(),res.begin(), res.end());

        //recursively go to right subtree and find inorder traversal
        auto res2=this->_inorder(new_head->right);
        v.insert(v.end(),res2.begin(), res2.end());
        return v;
    }

    vector<T> _postorder(node *new_head){
        vector<T> v;
        //if reached at the leaf node
        if(new_head==nullptr)
            return v;
        //recursively go to left subtree and find inorder traversal
        auto res=this->_inorder(new_head->left);
        v.insert(v.end(),res.begin(), res.end());

        //recursively go to right subtree and find inorder traversal
        auto res2=this->_inorder(new_head->right);
        v.insert(v.end(),res2.begin(), res2.end());

        v.push_back(new_head->data);
        return v;      
    }

public:
    void print();

    Binary_Search_Tree(){
        head = nullptr;
        num_of_nodes = 0;
    }
    
    void insert(T value){
        //we will never allow the private variables accessable (or passable as argument)
        if(head==nullptr){
            head=new node;
            head->data = value;
            num_of_nodes += 1;
            return;
        }        
        _insert(value, head);
    }

    void erase(T value);
    bool search(T value){
        return _search(value,head);
    }

    vector<T> inorder(){
        return _inorder(head);
    }

    vector<T> postorder(){
        return _postorder(head);
    }
    vector<T> preorder(){
        return _preorder(head);
    }
};

int main(){
    // Binary_Search_Tree<int> b;
    // b.insert(1);
    // // b.print();
    // b.insert(2);
    // // b.print();
    // b.insert(4);
    // // b.print();
    // b.insert(3);
    // // b.print();
    // for(int i=0;i<5;i++)
    //     b.insert(i);
    //     // cout<<b.search(i)<<endl;
    // // cout<<b.search(5)<<" "<<b.search(4)<<endl;
    // auto v=b.postorder();
    // for(auto it:v)
    //     cout<<it<<" ";
    // cout<<endl;

    return 0;
}