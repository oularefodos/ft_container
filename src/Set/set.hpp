#ifndef SET_HPP
#define SET_HPP
#include "../RedBlackTree/Red_black_tree.hpp"
#include "../Utils/utils.hpp"
#include "../Iterator/Iterator_traits.hpp"
#include "../Iterator/RBT_iterator.hpp"


namespace ft {
    template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> > 
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
            Alloc _alloc;
            RedBlackTree<T, Comp> _tree;
        public:
            typedef T mapped_type;
            typedef Compare key_compare;
            typedef Comp value_compare;
            typedef T value_type;
            typedef T key_type;
            typedef Alloc allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef RedBlackTree_iterator<value_type> iterator;
            typedef const RedBlackTree_iterator<value_type> const_iterator;
            typedef const Revers_Rbt_iterator<value_type> const_reverse_iterator;
            typedef Revers_Rbt_iterator<value_type> reverse_iterator;
            typedef ptrdiff_t difference_type;
            typedef size_t size_type;
        public:
        // constructor
            explicit set (const key_compare& comp = key_compare(), 
            const allocator_type& alloc = allocator_type()) {
                _alloc = alloc;
                _comp = comp;
            }

            template <class InputIterator>  
            set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type())
            {
                this->_comp = Comp();
                while (first != last) {
                    _tree.insert(*first);
                    first++;
                }
                _alloc = alloc;
                _comp = comp;
            }

            set(set const& lhs) {
                for(iterator i = lhs.begin(); i != lhs.end(); i++)
                    insert(*i);
                this->_comp = lhs._comp;
                this->_alloc = lhs._alloc;
            }
            ~set() {}

            set& operator= (set& x) {
                _tree.deleteAll();
                for(iterator i = x.begin(); i != x.end(); i++)
                    insert(*i);
                this->_comp = x._comp;
                this->_alloc = x._alloc;
                return *this; 
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
        void insert (InputIterator first, InputIterator last,
        typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
            while (first != last) {
                _tree.insert(*first);
                first++;
            }
        }

        void erase (iterator position) {
            key_type  i = *position;
            erase(i);
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
            Node<value_type>* ret = _tree.search(val);
            return (iterator(ret, _tree.end()));
        } 

        void clear() {
            _tree.deleteAll();
        }

        void swap (set& x) {
            set temp = *this;
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
            iterator v = _tree.getRoot() ? iterator(_tree.max()->rigth, _tree.end()) : iterator(NULL, _tree.end());
            return v;
        }

        const_iterator end() const {
            iterator v = _tree.getRoot() ? const_iterator(_tree.max()->rigth, _tree.end()) : const_iterator(NULL, _tree.end());
            return v;
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

        size_t size() const {
            return _tree.size();
        }

        size_t max_size() const {
            return _alloc.max_size();
        }

        // allocator 
        allocator_type get_allocator() const {
            return _tree.getAllocator();
        }

        // Operations 
        iterator find (const key_type& k) {
            Node<value_type>* ret = _tree.search(k);
            if (ret && !ret->isNull) {
                return iterator(ret, _tree.end());
            }
            return end();
        }
        
        const_iterator find (const key_type& k) const {
            Node<value_type>* ret = _tree.search(k);
            if (ret && !ret->isNull) {
                return const_iterator(ret, _tree.end());
            }
            return end();
        }

        size_t count (const key_type& k) {
            return find(k) != end() ? 1 : 0;
        }

        iterator lower_bound (const key_type& k) {
            Node<value_type>* ret = _tree.search(k);
            if (ret && !ret->isNull) {
                return iterator(ret, _tree.end());
            }
            else if (ret->parrent)
            {
                if (ret != ret->parrent->left)
                    return (++iterator(ret->parrent, _tree.end()));
                ret = ret->parrent;
                return (iterator(ret, _tree.end()));
            }
            else
                return end();
        }

        const_iterator lower_bound (const key_type& k) const{
            Node<value_type>* ret = _tree.search(k);
            if (ret && !ret->isNull) {
                return const_iterator(ret, _tree.end());
            }
            else if (ret->parrent)
            {
                if (ret != ret->parrent->left)
                    return (++const_iterator(ret->parrent, _tree.end()));
                ret = ret->parrent;
                return (const_iterator(ret, _tree.end()));
            }
            else
                return end();
        }

        iterator upper_bound (const key_type& k) {
           Node<value_type> *node = _tree.search(k);
            if (!node->isNull)
                return (++iterator(node, _tree.end()));
            else if (node->parrent) {
                if (node != node->parrent->left)
                    return (++iterator(node->parrent, _tree.end()));
                node = node->parrent;
                return (iterator(node, _tree.end()));
            }
            else
                return end();
        }

        const_iterator upper_bound (const key_type& k) const{
            Node<value_type> *node = _tree.search(k);
            if (!node->isNull)
                return (++const_iterator(node, _tree.end()));
            else if (node->parrent) {
                if (node != node->parrent->left)
                    return (++const_iterator(node->parrent, _tree.end()));
                node = node->parrent;
                return (const_iterator(node, _tree.end()));
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