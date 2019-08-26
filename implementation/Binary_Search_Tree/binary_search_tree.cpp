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

    node * root;
    int num_of_nodes;

    void _insert(T value,node* head){
        // inserts the value in the subtree rooted by head
        if(head->right==nullptr && (head->data)<value){
            head->right = new node;
            head->right->data = value;
            head->right->parent = head;
            num_of_nodes += 1;
            return;
        }
        else if((head->data)<value)
            this->_insert(value,(head->right));
        else if(head->left==nullptr){
            head->left = new node;
            head->left->data = value;
            head->left->parent = head;
            num_of_nodes += 1;
            return;
        }
        else this->_insert(value,(head->left));
    }

    pair<bool,node* > _search(T value,node *head){
        //return pair of bool and node*
        // returns a boolean value depending on wether the value being searched is found in the subtree rooted by head
        if(head == nullptr)
            return make_pair(false,nullptr);
        else if((head->data) == value)
            return make_pair(true,head);
        else if((head->data)<=value)
            return this->_search(value,head->right);
        else return this->_search(value,head->left);
    }

    vector<T> _inorder(node * new_head){
        // returns a vector containing the results of inorder traversal of subtree rooted by new_head
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
        // returns a vector containing the results of preorder traversal of subtree rooted by new_head
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
        // returns a vector containing the results of postorder traversal of subtree rooted by new_head
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

    pair<T,node* > _minimum(node* head){
        // assumed head is not nullptr
        while(head->left != nullptr)
            head = head->left;
        return make_pair(head->data,head);
    }

    pair<T,node* > _maximum(node* head){
        while(head->right != nullptr)
            head = head->right;
        return make_pair(head->data,head);
    }

    pair<T,node* > _successor(node* head){
        // returns the element in the current BST just bigger than that pointed by head node (assuming successor of current node always exists)

        // if right child of current node exists,the larger element must lie in its right subtree
        if(head->right != nullptr)
            return this->_minimum(head->right);
        // else it is in the left subtree of some node, that node is our answer
        node* temp = head->parent;
        while(temp != nullptr && temp->right == head){
            head = temp;
            temp = temp->parent;
        }
        return make_pair(temp->data,temp);
    }

    pair<T,node* > _predecessor(node* head){
        // returns the element in the current BST just smaller than that pointed by head node (assuming the predecessor of current node always exists)

        // if left child of current node exists the smaller element must lie in its left subtree
        if(head->left != nullptr)
            return this->_maximum(head->left);
        // else it is in the right subtree of some node, that node is our answer
        node* temp = head->parent;
        while(temp != nullptr && temp->left == head){
            head = temp;
            temp = temp->parent;
        }
        return make_pair(temp->data,temp);
    }

    void _insert(node* target,node* head){
        // target : pointer to the node which is root of the subtree to be inserted
        // head : the pointer to the node in whose subtree the target is to be inserted (assumed not to be a nullptr if it is not root)
         // while inserting, always make sure you set all the required pointers (don't forget to set parent pointer)
        if(target == nullptr)
            return;
        // target is not a nullptr
        else if(root == nullptr){
            root = target;
            target->parent = nullptr;
            return;
        }

        // assumed head and target passed was not nullptr
        else if(target->data <= head->data){
            // if subtree rooted by the node to be inserted lies in the left subtree of current node
            if(head->left == nullptr){
                // if left subtree of current node is empty, make the subtree rooted by node to be inserted as its left subtree
                target->parent = head;
                head->left = target;
                return;
            }
            // else find the correct node where the subtree rooted by node to be inserted can be placed
            this->_insert(target,head->left);
        }
        else{
            // if subtree rooted by the node to be inserted lies in the right subtree of the current node
            if(head->right == nullptr){
                // if right subtree of current node is empty, make the subtree rooted by the node to be inserted as its right subtree
                target->parent = head;
                head->right = target;
                return;
            }
            this->_insert(target,head->right);
        }
    }

    void _remove(node* head){
        // assumed head is not nullptr
        node* temp = nullptr;
        if(head == root){
            // if node to be deleted is root, make its right child as root and insert its left subtree in the BST (root being nullptr is handled in insert function)
            root = head->right;
            if(head->right != nullptr)
                head->right->parent = nullptr;
            temp = head->left;
        }
        else if(head->parent->left == head){
            // if node to be deleted is left child of its parent, add its left child as its parent's left child and insert the subtree rooted by right child of node to be deleted in the BST
            head->parent->left = head->left;
            if(head->left != nullptr)
                head->left->parent = head->parent;
            temp = head->right;
        }
        else{
            // node to be deleted is the right child of its parent, add its right child as its parent's right child and insert the subtree rooted by left child of the node to be deleted in the BST
            head->parent->right = head->right;
            if(head->right != nullptr)
                head->right->parent = head->parent;
            temp = head->left;
        }
        this->_insert(temp,root);
    }

public:
    void print();

    Binary_Search_Tree(){
        root = nullptr;
        num_of_nodes = 0;
    }
    
    void insert(T value){
        //we will never allow the private variables accessable (or passable as argument)
        if(root==nullptr){
            root=new node;
            root->data = value;
            num_of_nodes += 1;
            return;
        }        
        _insert(value, root);
    }
    
    bool search(T value){
        return _search(value,root).first;
    }

    vector<T> inorder(){
        return _inorder(root);
    }

    vector<T> postorder(){
        return _postorder(root);
    }
    vector<T> preorder(){
        return _preorder(root);
    }

    void remove(T value){   // complete the function
        auto result = _search(value,root);
        if(result.first == false)
            cout<<"can't remove a non-existing value\n.";
        else
            _remove(result.second);
        // complete the function
    }



};

int main(){
    Binary_Search_Tree<int> b;
    // b.insert(1);
    // // b.print();
    // b.insert(2);
    // // b.print();
    // b.insert(4);
    // // b.print();
    // b.insert(3);
    // // b.print();
    // for(int i=0;i<=5;i++)
    //     b.insert(i);
    //     // cout<<b.search(i)<<endl;
    // // cout<<b.search(5)<<" "<<b.search(4)<<endl;
    // // auto v=b.postorder();
    // // for(auto it:v)
    // //     cout<<it<<" ";
    // // cout<<endl;
    // b.insert(5);
    // cout<<b.search(0)<<"\n";
    // b.remove(0);
    // cout<<b.search(0)<<"\n";

    // cout<<b.search(1)<<"\n";
    // b.remove(1);
    // cout<<b.search(1)<<"\n";


    // cout<<b.search(1)<<"\n";
    // b.remove(1);
    // cout<<b.search(1)<<"\n";

    // map<string,Binary_Search_Tree<int> > _mp;
    // // _mp["insert"] = Binary_Search_Tree<int>().insert;

    string s;
    int i;
    while(cin>>s){
        if(s=="insert"){
            cin>>i;
            b.insert(i);
        }
        else if(s=="search"){
            cin>>i;
            cout<<b.search(i)<<"\n";
        }
        else if(s=="remove"){
            cin>>i;
            b.remove(i);
        }
    }

    return 0;
}