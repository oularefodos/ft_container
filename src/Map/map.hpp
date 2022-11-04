#ifndef Map_HPP
#define Map_HPP
#include "../RedBlackTree/Red_black_tree.hpp"
#include "../Iterator/Iterator_traits.hpp"

namespace ft {
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > > 
    class map
    {
        private:
            typedef Key key_type;
            typedef T mapped_type;
            typedef std::pair<const key_type, mapped_type> value_type;
            typedef Alloc allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef RedBlackTree_iterator<value_type> iterator;
            typedef RedBlackTree_iterator<const value_type> const_iterator;
            // typedef typename iterator_traits<iterator>::difference_type difference_type;
            class Comp{
                private:
                    Compare _comp;
                public:
                    Comp(Compare _com = Compare()) {
                        _comp = _com;
                    };
                    bool operator()( const std::pair<const Key,T>& lhs, const std::pair<const Key,T>& rhs ) const{
                        return _comp(lhs.first, rhs.first);
                    }
            };
            RedBlackTree<std::pair<const Key,T>, Comp> _tree;
        public:
        // constructor
            map() {}
            map(iterator first, iterator last) {
                while (first != last) {
                    _tree.insert(*first);
                }
            }
            map(const map& lhs) : _tree(lhs._tree) {

            }
            ~map() {}

        // to delete
        void print() {
            _tree.printTree();
        }

        bool test() {
            return _tree.testRedBlack();
        }


        // Modifiers
        std::pair<iterator, bool> insert(const value_type& val) {
            Node<value_type> *ret = _tree.search(val);
            bool n = false;
            if (!ret || ret->isNull) {
                _tree.insert(val);
                n = true;
            }
            return std::pair<iterator, bool> (iterator(ret), n);
        }
    };

};

#endif