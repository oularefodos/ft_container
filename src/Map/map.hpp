#ifndef Map_HPP
#define Map_HPP
#include "../RedBlackTree/Red_black_tree.hpp"
#include "../Utils/utils.hpp"
#include "../Iterator/Iterator_traits.hpp"

namespace ft {
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > > 
    class map
    {
        protected:
            class Comp{
                private:
                    Compare _comp;
                public:
                    Comp(Compare _com = Compare()) {
                        _comp = _com;
                    };
                    bool operator()( const ft::pair<const Key,T>& lhs, const ft::pair<const Key,T>& rhs ) const{
                        return _comp(lhs.first, rhs.first);
                    }
            };
            Comp _comp;
            RedBlackTree<ft::pair<const Key,T>, Comp> _tree;
        public:
            typedef Key key_type;
            typedef T mapped_type;
            typedef Compare key_compare;
            typedef Comp value_compare;
            typedef ft::pair<const key_type, mapped_type> value_type;
            typedef Alloc allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef RedBlackTree_iterator<value_type> iterator;
            typedef RedBlackTree_iterator<const value_type> const_iterator;
            typedef Revers_Rbt_iterator<const value_type> const_reverse_iterator;
            typedef Revers_Rbt_iterator<value_type> reverse_iterator;
            // typedef typename iterator_traits<iterator>::difference_type difference_type;
        public:
        // constructor
            map() {
                this->_comp = Comp();
            }
            map(iterator first, iterator last) {
                this->_comp = Comp();
                while (first != last) {
                    _tree.insert(*first);
                    first++;
                }
            }
            map(const map& lhs) : _tree(lhs._tree) {
                this->_comp = lhs._comp;
                this->Comp = lhs.Comp;
            }
            ~map() {}

            map& operator= (const map& x) {
                this->_tree = x._tree;
                this->_comp = x._comp;
                this->Comp = x.Comp;
            }

        // to delete
        void print() {
            _tree.printTree();
        }

        bool test() {
            return _tree.testRedBlack();
        }


        // Modifiers
        ft::pair<iterator, bool> insert(const value_type& val) {
            Node<value_type> *ret = _tree.search(val);
            bool n = false;
            if (!ret || ret->isNull) {
                _tree.insert(val);
                n = true;
            }
            return ft::pair<iterator, bool> (iterator(ret, _tree.end()), n);
        }

        template <class InputIterator> 
        void insert (InputIterator first, InputIterator last) {
            while (first != last) {
                _tree.insert(*first);
                first++;
            }
        }

        void erase (iterator position) {
            _tree.deleteNode(*(position).first);
        }

        size_t erase (const key_type& k) {
            _tree.deleteNode(ft::pair<Key, T> (k, T()));
            return (1);
        } 

        void erase (iterator first, iterator last) {
            while (first != last) {
                _tree.deleteNode(*first);
                first++;
            }
        }

        iterator insert (iterator position, const value_type& val) {
            (void)position;
            _tree.insert(val);
        } 

        void clear() {
            _tree.deleteAll();
        }

        void swap (map& x) {
            map temp = x;
            *this = x;
            x = temp;
        }

        // iterator 
        iterator begin() {
            return _tree.getRoot() ? iterator(_tree.min(), _tree.end()) : end();
        }

        const_iterator begin() const {
            return _tree.getRoot() ? const_iterator(_tree.min(), _tree.end()) : end();
        }

        iterator end() {
            return iterator(_tree.max()->rigth, _tree.end());
        }

        const_iterator end() const {
            return const_iterator(_tree.max()->rigth, _tree.end());
        }

        reverse_iterator rbegin() {
            iterator iter(_tree.max(), _tree.end());
            return reverse_iterator(iter);
        }

        const_reverse_iterator rbegin() const {
            iterator iter(_tree.max(), _tree.end());
            return const_reverse_iterator(iter);
        }

        reverse_iterator rend() {
            iterator iter(_tree.min()->left, _tree.end());
            return reverse_iterator(iter);
        }

        const_reverse_iterator rend() const {
            iterator iter(_tree.min()->left, _tree.end());
            return const_reverse_iterator(iter);
        }

        // oberservers 

        key_compare key_comp() const {
            return key_compare();
        }

        value_compare value_comp() const {
            return value_compare();
        }

        // capacity
        bool empty() {
            return _tree.size() == 0;
        }

        size_t size() {
            return _tree.size();
        }

        size_t max_size() {
            return _tree.getAllocator().max_size();
        }

        // access element
        mapped_type& operator[] (const key_type& k) {
            Node<T> *ret = _tree.search(k);
            if (ret && !ret->isNull) {
                return ret->value.second;
            }
            return 0;
        }

        mapped_type& at (const key_type& k) {
            Node<T> *ret = _tree.search(k);
            if (!ret || ret->isNull)
                throw std::out_of_range("out of range");
            return ret->value.second;
        }

        const mapped_type& at (const key_type& k) const {
            Node<T> *ret = _tree.search(k);
            if (!ret || ret->isNull)
                throw std::out_of_range("out of range");
            return ret->value.second;
        }

        // allocator 
        allocator_type get_allocator() const {
            return _tree.getAllocator();
        }

        // Operations 
        iterator find (const key_type& k) {
            Node<value_type>* ret = _tree.search(ft::pair<key_type, T> (k, T()));
            if (ret && !ret->isNull) {
                return iterator(ret);
            }
            return end();
        }
        
        const_iterator find (const key_type& k) const {
            Node<value_type>* ret = _tree.search(ft::pair<key_type, T> (k, T()));
            if (ret && !ret->isNull) {
                return const_iterator(ret);
            }
            return end();
        }

        size_t count (const key_type& k) const {
            Node<value_type>* ret = _tree.search(ft::pair<key_type, T> (k, T()));
            if (ret && !ret->isNull) {
                return 1;
            }
            return 0;
        }

        iterator lower_bound (const key_type& k) {
            Node<value_type>* ret = _tree.search(ft::pair<key_type, T> (k, T()));
            if (ret && !ret->isNull) {
                return iterator(ret);
            }
            else if (ret && ret->isNull)
            {
                if (ret != _tree.max()->rigth)
                    ret = ret->parrent;
                return (++iterator(ret));
            }
            else
                return end();
        }

        const_iterator lower_bound (const key_type& k) const{
            Node<value_type>* ret = _tree.search(ft::pair<key_type, T> (k, T()));
            if (ret && !ret->isNull) {
                return const_iterator(ret);
            }
            else if (ret && ret->isNull)
            {
                if (ret != _tree.max()->rigth)
                    ret = ret->parrent;
                return (++const_iterator(ret));
            }
            else
                return end();
        }

        iterator upper_bound (const key_type& k) {
           Node<value_type> *node = _tree.search(ft::make_pair(k, T()));
            if (!node->isNull)
                return (++iterator(node));
            else if (node->parrent) {
                if (node != node->parrent->left)
                    return (++iterator(node->parrent));
                node = node->parrent;
                return (iterator(node));
            }
            else
                return end();
        }

        const_iterator upper_bound (const key_type& k) const{
            Node<value_type> *node = _tree.search(ft::make_pair(k, T()));
            if (!node->isNull)
                return (++const_iterator(node));
            else if (node->parrent) {
                if (node != node->parrent->left)
                    return (++const_iterator(node->parrent));
                node = node->parrent;
                return (const_iterator(node));
            }
            else
                return end();
        }

        ft::pair<iterator, iterator> equal_range (const key_type& k) {
            return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
        }

        ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const {
            return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
        }
    };

};

#endif