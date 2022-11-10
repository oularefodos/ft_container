#ifndef STACK_HPP
#define STACK_HPP
#include "../Vector/Vector.hpp"

namespace ft {


    template <class T, class Container = ft::vector<T> >
    class stack
    {
        protected:
            Container container;
        public:
            typedef T           value_type;
            typedef Container   container_type;
            typedef size_t      size_type;
        public:

            explicit stack (const container_type& ctnr = container_type()) : container(ctnr) {}

            bool empty() const {
                return container.empty();
            }

            void pop() {
                container.pop_back();
            }

            void push (const value_type& val) {
                container.push_back(val);
            }

            size_type size() {
                return container.size();
            }

            value_type& top() {
                return container.back();
            }

            const value_type& top() const {
                return container.back();
            }
    };

    template <class T, class Container>
    bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return (lhs.container == rhs.container);
    }

    template <class T, class Container>
    bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return (lhs.container != rhs.container);
    }

    template <class T, class Container>
    bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return (lhs.container < rhs.container);
    }

    template <class T, class Container>
    bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return (lhs.container <= rhs.container);
    }

    template <class T, class Container>
    bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return (lhs.container > rhs.container);
    }

    template <class T, class Container>
    bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return (lhs.container >= rhs.container);
    }

}

#endif