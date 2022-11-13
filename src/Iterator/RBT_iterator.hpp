#ifndef RBT_ITERATOR_HPP
#define RBT_ITERATOR_HPP
#include "../RedBlackTree/Red_black_tree.hpp"

template <typename T>
class RedBlackTree_iterator {
    private:
        Node<T>* node;
        Node<T>* _end;
        
        Node<T>* begin(Node<T>* root) {
            Node<T>* temp;
            temp = root;
            while (!temp->left->isNull)
                temp = temp->left;
            return (temp);
        }

        Node<T>* end(Node<T>* root) {
            Node<T>* temp;
            temp = root;
            if (temp->isNull)
                return temp;
            while (!temp->rigth->isNull)
                temp = temp->rigth;
            return (temp);
        }
        Node<T>* getRoot(Node<T>* _node) {
            Node<T> *root = _node;
            while (root->parrent)
                root = root->parrent;
            return root;
        }
        Node<T>* max(Node<T>* _node) {
            Node<T>* m = getRoot(_node);
            while (!m->rigth->isNull)
                m = m->rigth;
            return m;
        }
        Node<T>* min(Node<T>* _node) {
            Node<T>* m = getRoot(_node);
            while (!m->left->isNull)
                m = m->left;
            return m;
        }
    public:
        RedBlackTree_iterator() {};
        RedBlackTree_iterator(Node<T> * _node, Node<T> *end) {
            node = _node;
             _end = end;
        }
        RedBlackTree_iterator(RedBlackTree_iterator const& rhs) {
            this->node = rhs.node;
            this->_end = rhs._end;
        }

        RedBlackTree_iterator& operator=(RedBlackTree_iterator const& rhs) {
            this->node = rhs.node;
            this->_end = rhs._end;
            return *this;
        }

        Node<T>* operator->() {
            return (node == max(node)->rigth ? this->_end : (node == min(node)->left ? NULL : node));
        }

        Node<const T>* operator->() const {
            return (node == max(node)->rigth ? this->_end : (node == min(node)->left ? NULL : node));
        }

        RedBlackTree_iterator& operator++() {
            if(node == max(node)->rigth)
                node = NULL;
            else if (node == min(node)->left)
                node = node->parrent;
            else if (node && !node->isNull) {
                if (node->parrent == NULL)
                    node = begin(node->rigth);
                else if (max(node) == node) 
                    node = node->rigth;
                else if (!node->rigth->isNull)
                    node = begin(node->rigth);
                else if (node->rigth->isNull && node == node->parrent->left)
                    node = node->parrent;
                else {
                    while (node->parrent == node->parrent->parrent->rigth)
                        node = node->parrent;
                    node = node->parrent->parrent;
                }
            }
            return *this;
        }

        RedBlackTree_iterator& operator--() {
            if (node == min(node)->left)
                node = NULL;
            else if(node == max(node)->rigth)
                node = max(node);
            else if (node && !node->isNull) {
                if (node->parrent == NULL)
                    node = end(node->left);
                else if (min(node) == node)
                    node = node->left;
                else if (!node->left->isNull)
                    node = end(node->left);
                else if (node->left->isNull && node == node->parrent->rigth)
                    node = node->parrent;
                else {
                    while (node->parrent == node->parrent->parrent->left)
                        node = node->parrent;
                    node = node->parrent->parrent;
                }
            }
            return *this;
        }

        RedBlackTree_iterator operator++(int) {
            RedBlackTree_iterator temp(node, _end);
            ++(*this);
            return temp;
        }


        RedBlackTree_iterator operator--(int) {
            RedBlackTree_iterator temp(node, _end);
            --(*this);
            return temp;
        }

        bool operator== (RedBlackTree_iterator const& rhs) const{
            return node == rhs.node;
        }

        bool operator!= (RedBlackTree_iterator const& rhs) const {
            return node != rhs.node;
        }

        T& operator*() {
            Node<T> *ret = (node == max(node)->rigth ? this->_end : (node == min(node)->left ? NULL : node));
            return ret->value;
        }
};

template <typename T>
class Revers_Rbt_iterator {
    private:
        RedBlackTree_iterator<T> iterator;
    public:
        Revers_Rbt_iterator () {};
        Revers_Rbt_iterator(Revers_Rbt_iterator<T> const& rhs) {
            this->iterator = rhs.iterator;
        }
        Revers_Rbt_iterator(RedBlackTree_iterator<T> const& iter) {
            iterator = iter;
        } 
        Revers_Rbt_iterator operator=(Revers_Rbt_iterator<T> const& rhs) {
            this->iterator = rhs.iterator;
            return *this;
        }
        Revers_Rbt_iterator operator++() {
            --iterator;
            return *this;
        }
        Revers_Rbt_iterator operator++(int) {
            iterator--;
            return *this;
        }
        Revers_Rbt_iterator operator--() {
            ++iterator;
            return *this;
        }
        Revers_Rbt_iterator operator--(int) {
            iterator++;
            return *this;
        }

        T& operator*() {
            return *iterator;
        }
        
        Revers_Rbt_iterator operator->() {
            return iterator;
        }

        Revers_Rbt_iterator operator==(Revers_Rbt_iterator const& x) {
            return iterator == x.iterator;
        }

        Revers_Rbt_iterator operator!=(Revers_Rbt_iterator const& x) {
            return iterator != x.iterator;
        }
};

#endif