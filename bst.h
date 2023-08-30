#pragma once
#include <vector>
#include <exception>
#include<stdexcept>
#include <iostream>
///////avl
namespace cop3530 {
    using namespace std;
    template<typename Key, typename T>
    class bst {
    public:
        struct node {
            // key
            // value
            
            
            Key key;
            T value;
            node* left;
            node* right;
            int height;

            node() {}
            node(Key k, T t) :key(k), value(t), left(nullptr), right(nullptr)
            {}
        };
        bst();
        ~bst();
        void insert(const Key& key, const T& t);
        void erase(const Key& key);
        T& at(const Key& key);
        bool contains(const Key& key) const;
        bool empty() const;
        size_t size() const;
        std::vector<std::pair<Key, T>> inorder_contents();
        std::vector<std::pair<Key, T>> preorder_contents();
        //for deconstructor
        void clear();
        void deleteTree(node* node);
        //Helper methods
        void insertHelper(node*& node, const Key& key, const T& t);
        void eraseHelper(node*& node, const Key& key);
        void Delete2(node*& n, Key& k);
        node* GetNode(const Key& k);
        T& minimum(node* node);
        size_t countNodes(node* node)const;
        void inorderSet(node* node, std::vector<std::pair<Key, T>>& v);
        void preorderSet(node* node, std::vector<std::pair<Key, T>>& v);
        //avl helper
        int getHeight(node* n);
        int getBalance(node* n);
        node* right_right_rotate(node*& n);
        node* left_left_rotate(node*& n);
        void right_left_rotate(node*& n);
        void left_right_rotate(node*& n);

    private:
        // root of tree
        node* root;
    };

    //find the maximum of left subtree
    template<typename Key, typename T>
    T& bst<Key, T>::minimum(node* n)
    {
        n = n->left;
        while (n->right != nullptr)
        {
            n = n->right;
        }
        return n->value;
    }

    template<typename Key, typename T>
    typename bst<Key, T>::node* bst<Key, T>::GetNode(const Key& k)
    {
        node* curr = root;
        //cout <<"281key  :" <<key << endl;
        while (curr != nullptr)
        {
            if (curr->key == k)
            {
                return curr;
            }
            else if (k < curr->key)
            {
                curr = curr->left;
            }
            else if (k > curr->key)
            {
                curr = curr->right;
            }
        }
        return curr;
    }

    template<typename Key, typename T>
    bst<Key, T>::bst() {
        root = nullptr;
    }

    template<typename Key, typename T>
    void bst<Key, T>::deleteTree(node* node)
    {
        if (node == nullptr)
        {
            return;
        }
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    template<typename Key, typename T>
    void bst<Key, T>::clear()
    {
        deleteTree(root);
        root = nullptr;
    }
    template<typename Key, typename T>
    bst<Key, T>::~bst() {
        clear();
    }

    template<typename Key, typename T>
    void bst<Key, T>::insertHelper(node*& n, const Key& key, const T& t)
    {
        //cout << "key :"<<key << endl;
        if (n == nullptr)
        {
            //cout << "83"<<endl;
            //cout << "key  :" << key<<endl;
            n = new node(key, t);
           // cout << "n->height  :" << n->height << endl;
        }
        else if (contains(key) == true)
        {
            node* target;
            target = GetNode(key);
            target->value = t;
            return;
        }
        else if (key < n->key)
        {
            insertHelper(n->left, key, t);
        }
        else if (key > n->key)
        {
            insertHelper(n->right, key, t);
        }
        
        //update height
        n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
        int balance = getBalance(n);
        //std::cout << "key  :" << key << std::endl;
        //std::cout << getHeight(n->left) << " - " << getHeight(n->right) << std::endl;
        //std::cout << "balance:  " << balance << std::endl;
        
        //LL
        if (balance > 1 && key < n->left->key)
        {
          //  std::cout << "166!!!!!!!!!!!!!!!!!!!!" << std::endl;
           // std::cout << "balance:  " << balance << std::endl;
           // std::cout << "key > n->right:  " << key << " > " << root->left->key << std::endl;
            n = right_right_rotate(n);
            //cout << "166rightright"<<endl;
        }
        //RR
        if (balance < -1 && key > n->right->key)
        {
            
            n = left_left_rotate(n);
            //cout << "173leftleft" << endl;
        }
        //LR
        if (balance > 1 && key > n->left->key)
        {
            //n->left = rotateLeft(n->left);
            //n = rotateRight(n);
           left_right_rotate(n);
            //cout << "181leftright" << endl;
        }
        //RL
        if (balance < -1 && key < n->right->key)
        {
            //n->right = rotateRight(n->right);
            //n = rotateLeft(n);
            right_left_rotate(n);
            //cout << "189rightleft" << endl;
        }
        //cout << "189rightleft" << endl;
    }

    //Inserts a new node into the bst, mapping key to t. 
    template<typename Key, typename T>
    void bst<Key, T>::insert(const Key& key, const T& t) {
        if (root == nullptr)
        {
            root = new node(key, t);
            // cout << "116" << endl;
            // cout << "key  :" << key << endl;
        }
        else {
            //cout <<"("<<key<<","<<t<<")"<< endl;
            //cout << "148___" << endl;
            insertHelper(root, key, t);
        }
    }

    template<typename Key, typename T>
    void bst<Key, T>::eraseHelper(node*& n, const Key& key)
    {
        if (n == nullptr)
        {
            //cout << "158" << endl;
            return;
        }

        if (key < n->key)
        {
            //cout << "163" << endl;
            eraseHelper(n->left, key);
        }
        else if (key > n->key)
        {
            //cout << "169" << endl;
            eraseHelper(n->right, key);
        }
        else //key ==node->key
        {//node* temp = n;
            if (n->left != nullptr && n->right != nullptr)//two child
            {
                T v = minimum(n);
                //cout << "176 :" << n->key <<" "<< v << endl;
                Delete2(n->left, n->key);
                n->value = v;
            }
            else if (n->left == nullptr && n->right == nullptr)//no child
            {
                n = nullptr;
                if (root->key == key) {
                    //cout << "187 root ==n" << endl;
                    root = nullptr;
                }
            }
            else//one child
            {
                node* newParent;
                if (n->left == nullptr)
                {
                    newParent = n->right;
                    *n = *newParent;
                    //cout << "199 left null: " << root->key << endl;
                }
                else if (n->right == nullptr)
                {
                    //cout << "247 right null" << endl;
                    newParent = n->left;
                    *n = *newParent;
                }
            }
        }

        //after deleting the node, update the height 
        //cout << "n->key "<< n->key << endl;
        
        if (n != nullptr)
        {
            n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
        }

        int balance = getBalance(n);

        //rr
        if (balance < -1 && getBalance(n->right) <= 0)
        {
            n = left_left_rotate(n);
            //cout << "271leftleft" << endl;
        }
        //ll
        if (balance > 1 && getBalance(n->left) >= 0)
        {
            n = right_right_rotate(n);
            //cout << "178rightright" << endl;
        }
        //rl
        if (balance < -1 && getBalance(n->right)> 0)
        {
            right_left_rotate(n);
            //cout << "283rightleft" << endl;
        }
        //lr
        if (balance > 1 && getBalance(n->left) < 0)
        {
            left_right_rotate(n);
            //cout << "290leftright" << endl;
        }
    }

    template<typename Key, typename T>
    void bst<Key, T>::Delete2(node*& n, Key& k)
    {
        if (n->right == NULL)
        {
            k = n->key;
            node* temp = n;
            //delete n;
            n = temp->left;
            //cout << 220 << endl;
        }
        else {
            Delete2(n->right, k);
        }
    }

    //Removes the node with Key key from the bst.
    template<typename Key, typename T>
    void bst<Key, T>::erase(const Key& key) {
        node* temp = root;
        if (root == nullptr || contains(key) == false)
        {
            //cout << "234key:   "<<key << endl;
            throw std::out_of_range("288out_of_range");
        }
        eraseHelper(temp, key);
    }

    //Returns a reference to the value type to which key maps
    template<typename Key, typename T>
    T& bst<Key, T>::at(const Key& key) {
        node* curr = root;
        if (contains(key) == false)
        {
            throw std::out_of_range("out_of_range");
        }
        else
        {
            while (curr != nullptr)
            {
                if (curr->key == key)
                {
                    break;
                }
                else if (key < curr->key)
                {
                    if (curr->left == nullptr)
                    {
                        throw std::out_of_range(" key is not found in the bst");
                    }
                    curr = curr->left;
                }
                else if (key > curr->key)
                {
                    if (curr->right == nullptr)
                    {
                        throw std::out_of_range(" key is not found in the bst");
                    }
                    curr = curr->right;
                }
            }
        }
        return curr->value;
    }

    //Returns true if a node with Key key is present in the bst and false otherwise
    template<typename Key, typename T>
    bool bst<Key, T>::contains(const Key& key) const {
        node* curr = root;
        //cout <<"281key  :" <<key << endl;
        while (curr != nullptr)
        {
            if (curr->key == key)
            {
                //cout << 292<<endl;
                return true;
            }
            else if (key < curr->key)
            {
                curr = curr->left;
            }
            else if (key > curr->key)
            {
                curr = curr->right;
            }
        }
        //cout << 298 << endl;
        return false;
    }

    //Returns true if the bst is empty and false otherwise.
    template<typename Key, typename T>
    bool bst<Key, T>::empty() const {
        if (root == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    template<typename Key, typename T>
    size_t bst<Key, T>::countNodes(node* node)const
    {
        if (node == nullptr) {
            return 0;
        }
        size_t count = 1;
        count += countNodes(node->left);
        count += countNodes(node->right);
        return count;
    }

    //Returns the number of nodes in the bst
    template<typename Key, typename T>
    size_t bst<Key, T>::size() const {
        return countNodes(root);
    }

    template<typename Key, typename T>
    void bst<Key, T>::inorderSet(node* node, std::vector<std::pair<Key, T>>& v)
    {
        if (node == nullptr)
        {
            return;
        }
        inorderSet(node->left, v);
        v.push_back(std::make_pair(node->key, node->value));
        inorderSet(node->right, v);
    }

    template<typename Key, typename T>
    std::vector<std::pair<Key, T>> bst<Key, T>::inorder_contents() {
        std::vector<std::pair<Key, T>> contents;
        inorderSet(root, contents);
        /*
        cout << "in node:" << endl;
        for (unsigned int i = 0; i < contents.size(); i++)
        {
            cout << contents[i].first<<"  ";
            cout << contents[i].second;
            cout << endl;
        }
        cout << "in end---------" << endl;*/
        return contents;
    }

    template<typename Key, typename T>
    void bst<Key, T>::preorderSet(node* node, std::vector<std::pair<Key, T>>& v)
    {
        if (node == nullptr)
        {
            return;
        }
        v.push_back(std::make_pair(node->key, node->value));
        preorderSet(node->left, v);
        preorderSet(node->right, v);
    }

    template<typename Key, typename T>
    std::vector<std::pair<Key, T>> bst<Key, T>::preorder_contents() {
        std::vector<std::pair<Key, T>> contents;
        preorderSet(root, contents);

        /*cout <<"pre node:"<< endl;
        for (unsigned int i = 0; i < contents.size();i++)
        {
            cout << contents[i].first<<"  ";
            cout << contents[i].second;
            cout << endl;
        }
        cout << "pre end---------"<<endl;*/

        return contents;
    }

    template<typename Key, typename T>
    int bst<Key, T>::getHeight(node* n)
    {//height of nullptr is 0
        if (n == nullptr)
        {
            return 0;
        }

        return n->height;
    }
    template<typename Key, typename T>
    int bst<Key, T>::getBalance(node* n)
    {
        //balance of nullptr is 0
        if (n == nullptr)
        {
            return 0;
        }
        return getHeight(n->left) - getHeight(n->right);
    }

    //rotateRight
    template<typename Key, typename T>
    typename bst<Key, T>::node* bst<Key, T>::right_right_rotate(node*& n)
    {
        node* newParent = n->left;
        node* newParentRight = newParent->right;
        newParent->right = n;
        n->left = newParentRight;
        if (root->key == n->key) {
            //cout << "187 root ==n" << endl;
            root = newParent;
        }
        //update  
        n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
        newParent->height = max(getHeight(newParent->left), getHeight(newParent->right)) + 1;
        return newParent;
    }

    //rotateLeft
    template<typename Key, typename T>
    typename bst<Key, T>::node* bst<Key, T>::left_left_rotate(node*& n)
    {

        node* newParent = n->right;
        node* newParentLeft = newParent->left;
        newParent->left = n;
        n->right = newParentLeft;
        if (root->key == n->key) {
            //cout << "187 root ==n" << endl;
            root = newParent;
        }
        //update   
        //cout << "527newParent->key  "<< newParent->key <<endl;
        n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
        newParent->height = max(getHeight(newParent->left), getHeight(newParent->right)) + 1;
        return newParent;
    }

    template<typename Key, typename T>
    void bst<Key, T>::left_right_rotate(node*& n)
    {
        n->left = left_left_rotate(n->left);
        n = right_right_rotate(n);
        //return n;
    }
    template<typename Key, typename T>
    void bst<Key, T>::right_left_rotate(node*& n)
    {
        n->right = right_right_rotate(n->right);
        n = left_left_rotate(n);
        //return n;
    }
}