// Acknowledgements : stackoverflow and CLRS (Introduction To Algorithms)

#include<bits/stdc++.h>
using namespace std;

ifstream iff;
#define cin iff
ofstream off("bst.txt");
#define cout off

template<typename T>
class Binary_Search_Tree{
private:
    struct node{
        T data;
        node * parent;
        node * left;
        node * right;
        node(){
            // very important step, the keyword 'new' doesn't guarentee nullptr initialisation of pointers (remember you spent 4 hours here !)
            parent = nullptr;
            left = nullptr;
            right = nullptr;
        }
    };

    node * root;
    int num_of_nodes;

    void _insert(T value,node* head){
        // inserts the value in the subtree rooted by head
        if(head == nullptr){
            cout<<"passed while searching "<<value<<endl;
            return;
        }
        if((head->right) == nullptr && (head->data)<value){
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

    vector<T> _inorder(node* new_head){
        // returns a vector containing the results of inorder traversal of subtree rooted by new_head
        vector<T> v;
        //if reached at the leaf node
        if(new_head == nullptr)
            return v;
        //recursively go to left subtree and find inorder traversal
        auto res=(this->_inorder(new_head->left));
        v.reserve(v.size()+res.size());
        v.insert(v.end(),res.begin(), res.end());
        v.push_back(new_head->data);
        //recursively go to right subtree and find inorder traversal
        auto res2=(this->_inorder(new_head->right));
        v.reserve(v.size()+res2.size());
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
        auto res=this->_preorder(new_head->left);
        v.insert(v.end(),res.begin(), res.end());

        //recursively go to right subtree and find inorder traversal
        auto res2=this->_preorder(new_head->right);
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
        auto res=this->_postorder(new_head->left);
        v.insert(v.end(),res.begin(), res.end());

        //recursively go to right subtree and find inorder traversal
        auto res2=this->_postorder(new_head->right);
        v.insert(v.end(),res2.begin(), res2.end());

        v.push_back(new_head->data);
        return v;      
    }

    pair<T,node* > _minimum(node* head){
        // assumed head is not nullptr, this method returns the minimum element's value with its pointer in the subtree rooted at 'head'
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

    void _transplant(node* u,node* v){
        // as per class lectures : this function adds the subtree rooted at v as appropriate child of parent of u (if exists). Remember node U and its children are left unchanged, only change in parent of U is visible (bidirectional change i.e. parent points to child and child points to parent), 
        if(u->parent == nullptr)
            // if u is root
            root = v;
        else if(u == u->parent->left)
            // if u is left child
            u->parent->left = v;
        else
            // if u is right child
            u->parent->right = v;
        if(v != nullptr)
            v->parent = u->parent;
    }

    void _delete(node* head){
        // if the node to be deleted doesn't have a left child, 
        if(head->left == nullptr)
            this->_transplant(head,head->right);
        // if the node to be deleted doesn't have a right child
        else if(head->right == nullptr)
            this->_transplant(head,head->left);
        else{
            // find the successor (element just greater than the current node), note that this element will be the leftmost node of the current sub-tree (i.e. it won't have any left child)
            node* cur_successor = (this->_minimum(head->right)).second;
            // transplant the cur_successor with the current node, taking care of assigning the right children properly as transplant doesn't change the children in the subtree rooted by node pointer passed as first argument
            if(cur_successor->parent != head){
                // cur_successor takes place of head node
                this->_transplant(cur_successor,cur_successor->right);
                cur_successor->right = head->right;
                cur_successor->right->parent = cur_successor;
            }
            // cur_successor takes place of the node that is to be deleted
            this->_transplant(head,cur_successor);
            // by now, the parent of right child of head has been made to cur_successor (if was required)
            cur_successor->left = head->left;
            cur_successor->left->parent = cur_successor;
        }
    }

public:
    void print();

    Binary_Search_Tree(){
        root = nullptr;
        num_of_nodes = 0;
    }
    
    void insert(T value){
        //we will never allow the private variables accessable (or passable as argument)
        if(root == nullptr){
            root = new node;
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

    string maximum(){
        if(root == nullptr)
            return "";
        else return to_string(_maximum(root).first);
    }

    string minimum(){
        if(root == nullptr)
            return "";
        else return to_string(_minimum(root).first);
    }

    void successor(T value){
        if(_search(value,root).first == false)
            cout<<value<<" does not exist\n";
        else if(_maximum(root).second == _search(value,root).second)
            cout<<"successor of "<<value<<" does not exist\n";
        else
            cout<<_successor(_search(value,root).second).first<<'\n';
    }

    void predecessor(T value){
        if(_search(value,root).first == false)
            cout<<value<<" does not exist\n";
        else if(_minimum(root).second == _search(value,root).second)
            cout<<"predecessor of "<<value<<" does not exist\n";
        else
            cout<<_predecessor(_search(value,root).second).first<<'\n';
    }

    void del(T value){
        auto result = _search(value,root);
        if(result.first == false)
            cout<<value<<" does not exist\n";
        else{
            cout<<value<<" deleted\n";
            _delete(result.second);
        }
    }
};

int main(int argc, char** argv){
    iff.open(argv[1]);
    Binary_Search_Tree<int> b;
    string s;
    int i;
    while(cin>>s){
        if(s=="insert"){
            cin>>i;
            b.insert(i);
            cout<<i<<" inserted\n";
        }
        else if(s=="inorder"){
            auto vec = b.inorder();
            for(auto it:vec)
                cout<<it<<" ";
            cout<<endl;
        }
        else if(s=="preorder"){
            auto vec = b.preorder();
            for(auto it:vec)
                cout<<it<<" ";
            cout<<endl;
        }
        else if(s=="postorder"){
            auto vec = b.postorder();
            for(auto it:vec)
                cout<<it<<" ";
            cout<<endl;
        }
        else if(s=="search"){
            cin>>i;
            if(b.search(i) == true)
                cout<<i<<" found\n";
            else
                cout<<i<<" not found\n";
        }
        else if(s=="minimum"){
            cout<<b.minimum()<<'\n';
        }
        else if(s=="maximum"){
            cout<<b.maximum()<<'\n';
        }
        else if(s=="successor"){
            cin>>i;
            b.successor(i);
        }
        else if(s=="predecessor"){
            cin>>i;
            b.predecessor(i);
        }
        else if(s=="delete"){
            cin>>i;
            b.del(i);
        }
    }
    return 0;
}