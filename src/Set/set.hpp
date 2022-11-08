#ifndef SET_HPP
#define SET_HPP
#include "../RedBlackTree/Red_black_tree.hpp"
#include "../Utils/utils.hpp"
#include "../Iterator/Iterator_traits.hpp"

namespace ft {
    template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
    class set
    {
        protected:
            class Comp{
                private:
                    Compare _comp;
                public:
                    Comp(Compare _com = Compare()) {
                        _comp = _com;
                    };
                    bool operator()( const T& lhs, const T& rhs ) const{
                        return _comp(lhs, rhs);
                    }
            };
            Comp _comp;
            RedBlackTree<T, Comp> _tree;
        public:
            typedef T key_type;
            typedef Compare key_compare;
            typedef Comp value_compare;
            typedef T value_type;
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
            set() {
                this->_comp = Comp();
            }
            set(iterator first, iterator last) {
                this->_comp = Comp();
                while (first != last) {
                    _tree.insert(*first);
                    first++;
                }
            }
            set(const set& lhs) : _tree(lhs._tree) {
                this->_comp = lhs._comp;
                this->Comp = lhs.Comp;
            }
            ~set() {}

            set& operator= (const set& x) {
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
            return ft::pair<iterator, bool> (iterator(ret), n);
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
            _tree.deleteNode(k);
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

        void swap (set& x) {
            set temp = x;
            *this = x;
            x = temp;
        }

        // iterator 
        iterator begin() {
            return iterator(_tree.min());
        }

        const_iterator begin() const {
            return const_iterator(_tree.min());
        }

        iterator end() {
            return iterator(_tree.max()->rigth);
        }

        const_iterator end() const {
            return const_iterator(_tree.max()->rigth);
        }

        reverse_iterator rbegin() {
            iterator iter(_tree.max());
            return reverse_iterator(iter);
        }

        const_reverse_iterator rbegin() const {
            iterator iter(_tree.max());
            return const_reverse_iterator(iter);
        }

        reverse_iterator rend() {
            iterator iter(_tree.min()->left);
            return reverse_iterator(iter);
        }

        const_reverse_iterator rend() const {
            iterator iter(_tree.min()->left);
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
        value_type& operator[] (const key_type& k) {
            Node<T> *ret = _tree.search(k);
            if (ret && !ret->isNull) {
                return ret->value.second;
            }
            return 0;
        }

        value_type& at (const key_type& k) {
            Node<T> *ret = _tree.search(k);
            if (!ret || ret->isNull)
                throw std::out_of_range("out of range");
            return ret->value.second;
        }

        const value_type& at (const key_type& k) const {
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
            Node<value_type>* ret = _tree.search(k);
            if (ret && !ret->isNull) {
                return iterator(ret);
            }
            return end();
        }
        
        const_iterator find (const key_type& k) const {
            Node<value_type>* ret = _tree.search(k);
            if (ret && !ret->isNull) {
                return const_iterator(ret);
            }
            return end();
        }

        size_t count (const key_type& k) const {
            Node<value_type>* ret = _tree.search(k);
            if (ret && !ret->isNull) {
                return 1;
            }
            return 0;
        }

        iterator lower_bound (const key_type& k) {
            Node<value_type>* ret = _tree.search(k);
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
            Node<value_type>* ret = _tree.search(k);
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
            Node<value_type> node = _tree.search(k);
            if (!node->isNull)
                return (++iterator(node));
            else if (node->isNull) {
                node = node->parrent;
                if (node != node->parrent->left)
                    return (++iterator(node));
                return (iterator(node));
            }
            else
                return end();
        }

        const_iterator upper_bound (const key_type& k) const{
            Node<value_type>* ret = _tree.search(k);
            if (ret) {
                if (ret->isNull && ret != _tree.max()->rigth)
                    ret = ret->parrent;
                return (++const_iterator(ret));
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