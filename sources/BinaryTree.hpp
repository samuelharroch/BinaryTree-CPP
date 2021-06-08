#pragma once
#include <iostream>
#include <stdexcept>
#include <queue>

namespace ariel {

    template<typename T> class BinaryTree{

    private:

        // Node struct
        struct Node
        {
            T value;
            Node* right;
            Node* left;

            Node (const T& v)
            : value{v},right{nullptr},left{nullptr}{}

            //copy construtor
            Node(const Node * other)
            : value(0), right(nullptr), left(nullptr){
                if(other != nullptr){
                    value= other->value;
                    if( other->right!= nullptr){
                        right= new Node(other->right);
                    }
                    if( other->left!= nullptr){
                        left= new Node(other->left);
                    }
                }
            }

            Node(const Node& other){}
            Node& operator=(const Node& other){ 
                if (this == other){return *this;}
                delete this->left;
                delete this->right;
                this->right= new Node(other.right);
                this->left = new Node(other.left);
                return *this;}

            Node(Node&& other) noexcept{}
            Node& operator=(Node&& other) noexcept{ return *this;}

            ~Node(){
                delete left;
                delete right;
            }
        };// end of Node

         
        Node* search(Node* node, const T& parent){
            if(node == nullptr){return nullptr;}
            if(node->value == parent){return node;}
            Node * right= search(node->right, parent);
            Node * left= search(node->left, parent);
            if (left) {return left;}
            return right;
            
        }
    
    public:
        Node* root;

        BinaryTree():root{nullptr}{}
        // avoid copying 
        BinaryTree (const BinaryTree& other)
        :root(new Node(other.root)){}

        BinaryTree& operator= (const BinaryTree& other){
            if (this == &other ){return *this;}
            if(root != nullptr){delete root;}
            root = new Node (other.root);
            return *this;
        }

        BinaryTree& operator=(BinaryTree&& other) noexcept {
            root = other.root;
            other.root = nullptr;
            return *this;
        }

        BinaryTree(BinaryTree &&other) noexcept {
            root = other.root;
            other.root = nullptr;
        }

        ~BinaryTree(){
            delete root;
        }

        BinaryTree<T>& add_root (const T& value){
            if(root){
                root->value = value;
            }else{
                root = new Node(value);
            }
            return *this;
        }

        BinaryTree<T>& add_left (const T& parent_value, const T& left_child_value){

            Node* node = search(root, parent_value);
            if(node== nullptr){
                throw std::invalid_argument {"parent value dont exist"};
            }

            if (node->left == nullptr){
                node->left = new Node(left_child_value);
            }else{
                node->left->value = left_child_value;
            }
            return *this;
        }

        BinaryTree<T>& add_right (const T& parent_value,const T& right_child_value){
            Node* node = search(root, parent_value);
            if(node== nullptr){
                throw std::invalid_argument {"parent value dont exist"};
            }

            if (node->right == nullptr){
                node->right = new Node(right_child_value);
            }else{
                node->right->value = right_child_value;
            }
            return *this;
        }

        

    //---------------------------- inner class iterator-----------------------//
        class inorder_iterator;
        class preorder_iterator;
        class postorder_iterator;

        class iterator{
            private:
                Node* current;
                std::queue<Node* > queue;
                void run(Node* node){
                    if (node == nullptr){return;};
                    run(node->left);
                    queue.push(node);
                    run(node->right);
                }

            public:
                Node* getCurrent() const{ return current;}

                iterator(Node* node ):current(nullptr){
                    run(node);
                    queue.push(nullptr);
                    current = queue.front();
                    queue.pop();
                }

                T& operator*() const{
                    return current->value;
                }

                T* operator->() const{
                    return &(current->value);
                }

                iterator &operator++()
                {

                    if (!queue.empty())
                        {
                            current = queue.front();
                            queue.pop();
                        }
                    return *this;
                }
                iterator operator++(int)
                {
                    iterator tmp = *this;
                    current = queue.front();
                    queue.pop();
                    return tmp;
                }
                bool operator==(const iterator& rhs) const{
                    return current == rhs.getCurrent();
                }
                bool operator==(const postorder_iterator& rhs) const{
                    return current == rhs.getCurrent();
                }
                bool operator==(const inorder_iterator& rhs) const{
                    return current == rhs.getCurrent();
                }
                bool operator==(const preorder_iterator& rhs) const{
                    return current == rhs.getCurrent();
                }

                bool operator!=(const iterator& rhs) const {
			        return current != rhs.getCurrent();
		        }

        }; // end of class iterator


        class inorder_iterator{
            private:
                Node* current;
                std::queue<Node* > queue;
                void run(Node* node){
                    if (node == nullptr){return;};
                    run(node->left);
                    queue.push(node);
                    run(node->right);
                }

            public:
                
                Node* getCurrent() const{ return current;}
                inorder_iterator(Node* node ):current(nullptr){
                    run(node);
                    queue.push(nullptr);
                    current = queue.front();
                    queue.pop();
                }

                T& operator*() const{
                    return current->value;
                }

                T* operator->() const{
                    return &(current->value);
                }

                inorder_iterator& operator++() {
                    if (!queue.empty())
                        {
                            current = queue.front();
                            queue.pop();
                        }
                    return *this;
                }
                inorder_iterator operator++(int)
                {
                    inorder_iterator tmp = *this;
                    current = queue.front();
                    queue.pop();
                    return tmp;
                }

                bool operator==(const iterator& rhs) const{
                    return current == rhs.getCurrent();
                }
                bool operator==(const postorder_iterator& rhs) const{
                    return current == rhs.getCurrent();
                }
                bool operator==(const inorder_iterator& rhs) const{
                    return current == rhs.getCurrent();
                }
                bool operator==(const preorder_iterator& rhs) const{
                    return current == rhs.getCurrent();
                }

                bool operator!=(const inorder_iterator& rhs) const {
			        return current != rhs.getCurrent();
		        }

        }; // end of class iterator


        class preorder_iterator{
            private:
                Node* current;
                std::queue<Node* > queue;
                void run(Node* node){
                    if (node == nullptr){return;};
                    queue.push(node);
                    run(node->left);
                    run(node->right);
                }
            public:
                
                Node* getCurrent()const { return current;}

                preorder_iterator(Node* node ):current(nullptr){
                    run(node);
                    queue.push(nullptr);
                    current = queue.front();
                    queue.pop();
                }

                T& operator*() const{
                    return current->value;
                }

                T* operator->() const{
                    return &(current->value);
                }

                preorder_iterator& operator++() {
                    if (!queue.empty())
                        {
                            current = queue.front();
                            queue.pop();
                        }
                    return *this;
                }
                preorder_iterator operator++(int)
                {
                    preorder_iterator tmp = *this;
                    current = queue.front();
                    queue.pop();
                    return tmp;
                }

                bool operator==(const iterator& rhs) const{
                    return current == rhs.getCurrent();
                }
                bool operator==(const postorder_iterator& rhs) const{
                    return current == rhs.getCurrent();
                }
                bool operator==(const inorder_iterator& rhs) const{
                    return current == rhs.getCurrent();
                }
                bool operator==(const preorder_iterator& rhs) const{
                    return current == rhs.getCurrent();
                }

                bool operator!=(const preorder_iterator& rhs) const {
			        return current != rhs.getCurrent();
		        }

        }; // end of class iterator


        class postorder_iterator{
            private:
                Node* current;
                std::queue<Node* > queue;
                void run(Node* node){
                    if (node == nullptr){return;};
                    
                    run(node->left);
                    run(node->right);
                    queue.push(node);
                }
            public:
                
                Node* getCurrent() const{ return current;}

                postorder_iterator(Node* node ):current(nullptr){
                    run(node);
                    queue.push(nullptr);
                    current = queue.front();
                    queue.pop();
                }

                T& operator*() const{
                    return current->value;
                }

                T* operator->() const{
                    return &(current->value);
                }

                postorder_iterator& operator++() {
                    if (!queue.empty())
                        {
                            current = queue.front();
                            queue.pop();
                        }
                    return *this;
                }

                postorder_iterator operator++(int)
                {
                    postorder_iterator tmp = *this;
                    current = queue.front();
                    queue.pop();
                    return tmp;
                }

                bool operator==(const iterator& rhs) const{
                    return current == rhs.getCurrent();
                }
                bool operator==(const postorder_iterator& rhs) const{
                    return current == rhs.getCurrent();
                }
                bool operator==(const inorder_iterator& rhs) const{
                    return current == rhs.getCurrent();
                }
                bool operator==(const preorder_iterator& rhs) const{
                    return current == rhs.getCurrent();
                }

                bool operator!=(const postorder_iterator& rhs) const {
			        return current != rhs.getCurrent();
		        }

        }; // end of class iterator



        // ------------------- iteration functions -----------------------//
        inorder_iterator begin_inorder() { 
		    return inorder_iterator{root};
	    }
	
	    inorder_iterator end_inorder() {
		    return inorder_iterator{nullptr};
	    }

        preorder_iterator begin_preorder() { 
		    return preorder_iterator{root};
	    }
	
	    preorder_iterator end_preorder() {
		    return preorder_iterator{nullptr};
	    }

        postorder_iterator begin_postorder() { 
		    return postorder_iterator{root};
	    }
	
	    postorder_iterator end_postorder() {
		    return postorder_iterator{nullptr};
	    }
        // essential for iterate 
        iterator begin() const { 
		    return iterator{root};
	    }
	
	    iterator end() const {
		    return iterator{nullptr};
	    }

    
        friend std::ostream& operator<<(std::ostream &out, const BinaryTree<T> &bt)
        {   
            for(const T& element: bt){
                out<< element<< ", ";
            }
            
            return out;
        }
    };
}