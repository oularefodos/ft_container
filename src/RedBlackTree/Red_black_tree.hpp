#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

 #define RED 1
 #define BLACK 0

template <typename T>
class Node {
    private:
        std::allocator<Node<T> > alloc;
    public:
        int color;
        Node* left;
        Node* rigth;
        Node* parrent;
        bool    isNull;
        T value;
    public:
        Node() {}
        Node(int const& _color, Node<T> * _parrent, T const& _value, std::allocator<Node<T> > _alloc) : value(_value) {
            alloc = _alloc;
            this->color = _color;
            this->parrent = _parrent;
            this->isNull = false;
            this->left = alloc.allocate(1);
            this->left->isNull = true;
            this->left->parrent = this;
            this->left->color = BLACK;
            this->rigth = alloc.allocate(1);
            this->rigth->isNull = true;
            this->rigth->parrent = this;
            this->rigth->color = BLACK;
        }
};

template <typename T>
class RedBlackTree_iterator {
    private:
        Node<T>* node;
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
        RedBlackTree_iterator(Node<T> * _node) {node = _node;}
        RedBlackTree_iterator(RedBlackTree_iterator const& rhs) {
            this->node = rhs.node;
        }

        RedBlackTree_iterator& operator=(RedBlackTree_iterator const& rhs) {
            this->node = rhs.node;
            return *this;
        }

        Node<T>* operator->(){
            return this->node;
        }

        Node<const T>* operator->() const {
            return this->node;
        }

        RedBlackTree_iterator& operator++() {
            if (node && !node->isNull) {
                if (node->parrent == NULL)
                    node = begin(node->rigth);
                else if (max(node) == node) 
                    node = node->rigth;
                else if (node->parrent && node == node->parrent->left && node->rigth->isNull)
                    node = node->parrent;
                else if (node->parrent && node == node->parrent->left && !node->rigth->isNull)
                    node = begin(node->rigth);
                else if (node->parrent && node == node->parrent->rigth && !node->rigth->isNull)
                    node = node->rigth;
                else {
                    while (node->parrent == node->parrent->parrent->rigth)
                        node = node->parrent;
                    if (node && node->parrent)
                        node = node->parrent->parrent;
                }
            }
            return *this;
        }

        RedBlackTree_iterator& operator--() {
            if (node && !node->isNull) {
                if (node->parrent == NULL)
                    node = end(node->left);
                else if (min(node) == node)
                    node = node->left;
                else if (node->parrent && node == node->parrent->rigth && node->left->isNull)
                    node = node->parrent;
                else if (node->parrent && node == node->parrent->rigth && !node->left->isNull)
                    node = end(node->left);
                else if (node->parrent && node == node->parrent->left && !node->left->isNull)
                    node = node->left;
                else {
                    while (node->parrent == node->parrent->parrent->left)
                        node = node->parrent;
                    node = node->parrent->parrent;
                }
            }
            return *this;
        }

        RedBlackTree_iterator operator++(int) {
            RedBlackTree_iterator temp(node);
            ++(*this);
            return temp;
        }

        RedBlackTree_iterator operator--(int) {
            RedBlackTree_iterator temp(node);
            --(*this);
            return temp;
        }

        bool ret() {
            return node->isNull;
        }

        T& operator*() {
            return node->value;
        }
};

template <typename T, class Compar>
class RedBlackTree {
    private:
        Node<T> *root;
        size_t sz;
        Compar _comp;
        std::allocator<Node<T> > alloc;
        typedef  RedBlackTree_iterator<T> iterator;
        void _init(Node<T>* parrent, Node<T>* node, int _color, T _value)
        {
            alloc.construct(node, Node<T>(_color, parrent, _value, alloc));
        }

        void _changePosition(Node<T>* s1, Node<T>* s2) {
            Node<T>* new_node;
            new_node = alloc.allocate(1);
            alloc.construct(new_node, Node<T>(s1->color, s1->parrent, s2->value, alloc));
            alloc.deallocate(new_node->left, 1);
            alloc.deallocate(new_node->rigth, 1);
            new_node->left = s1->left;
            new_node->rigth = s1->rigth;
            s1->left->parrent = new_node;
            s1->rigth->parrent = new_node;
            if (s1 == root)
                root = new_node;
            else if (s1 == s1->parrent->left)
                s1->parrent->left = new_node;
            else
                s1->parrent->rigth = new_node;
            alloc.destroy(s1);
            alloc.deallocate(s1, 1);
        }

        void _rigthRotate (Node<T> *node) {
            Node<T>* left = node->left;
            if (left->isNull)
                return ;
            if (node->parrent && node == node->parrent->left)
                node->parrent->left = left;
            else if (node->parrent && node != node->parrent->left)
                node->parrent->rigth = left;
            left->parrent = node->parrent;
            node->parrent = left;
            node->left = left->rigth;
            if (left->rigth)
                left->rigth->parrent = node;
            left->rigth = node;
            if (left->parrent == NULL)
                this->root = left;
        }

        void _leftRotate(Node<T>* node) {
            Node<T>* rigth = node->rigth;
            if (rigth->isNull)
                return ;
            if (node->parrent && node == node->parrent->left)
                node->parrent->left = rigth;
            else if (node->parrent && node != node->parrent->left)
                node->parrent->rigth = rigth;
            rigth->parrent = node->parrent;
            node->parrent = rigth;
            node->rigth = rigth->left;
            if (rigth->left)
                rigth->left->parrent = node;
            rigth->left = node;
            if (rigth->parrent == NULL)
                this->root = rigth;
        }

        void _InsertFix(Node<T>* node) {
            Node<T>* u;
            while (node->parrent && node->parrent->color == RED) {
                if (node->parrent == node->parrent->parrent->rigth) {
                    u = node->parrent->parrent->left; // uncle
                    if (u->color == RED) // 3.1 
                    {
                        u->color = BLACK;
                        node->parrent->color = BLACK;
                        node->parrent->parrent->color = RED;
                        node = node->parrent->parrent;
                    }
                    else {
                        if (node == node->parrent->left)
                        {
                            node = node->parrent;
                            _rigthRotate(node);
                        }
                        node->parrent->color = BLACK;
                        node->parrent->parrent->color = RED;
                        _leftRotate(node->parrent->parrent);
                    }                  
                }
                else {
                    u = node->parrent->parrent->rigth;
                    if (u->color == RED) {
                        u->color = BLACK;
                        node->parrent->color = BLACK;
                        node->parrent->parrent->color = RED;
                        node = node->parrent->parrent;
                    }
                    else {
                        if (node == node->parrent->rigth)
                        {
                                node = node->parrent;
                                _leftRotate(node); 
                        }
                        node->parrent->color = BLACK;
                        node->parrent->parrent->color = RED;
                        _rigthRotate(node->parrent->parrent);
                    }
                }
                if (node == root)
                    break ;
            }
            root->color = BLACK;

        }

         void _deleteFix(Node<T>* node) {
            Node<T> *s;
            while (node != root && node->color == BLACK) {
                if (node == node->parrent->left) {
                    s = node->parrent->rigth;
                    if (s->color == RED) {
                        s->color = BLACK;
                        node->parrent->color = RED;
                        _leftRotate(node->parrent);
                        s = node->parrent->rigth; 
                    }
                    if (s->left->color == BLACK && s->rigth->color == BLACK) {
                        s->color = RED;
                        node = node->parrent;
                    }
                    else {
                        if (s->rigth->color == BLACK) {
                            s->color = RED;
                            s->left->color = BLACK;
                            _rigthRotate(s);
                            s = node->parrent->rigth;
                        }
                        s->color = node->parrent->color;
                        s->parrent->color = BLACK;
                        s->rigth->color = BLACK;
                        _leftRotate(node->parrent);
                        node = root;
                    }
                } else {
                    s = node->parrent->left;
                    if (s->color == RED) {
                        s->color = BLACK;
                        node->parrent->color = RED;
                        _rigthRotate(node->parrent);
                        s = node->parrent->left;
                    }
                    if (s->left->color == BLACK && s->rigth->color == BLACK) {
                        s->color = RED;
                        node = node->parrent;
                    }
                    else {
                        if (s->left->color == BLACK) {
                            s->color = RED;
                            s->rigth->color = BLACK;
                            _leftRotate(s);
                            s = node->parrent->left;
                        }
                        s->color = node->parrent->color;
                        node->parrent->color = BLACK;
                        s->left->color = BLACK;
                        _rigthRotate(node->parrent);
                        node = root;
                    }
                }
            }
            node->color = BLACK;
        }
#if 1
        size_t _getBlackHeight(Node<T>*node) const {
                if (!node || node->isNull) return 0;
                size_t leftHeight = _getBlackHeight(node->left);
                return leftHeight + (node->color == BLACK);
            }

        bool _testRedBlack(Node<T>*node) const {
            if (!node || node->isNull) return true;
            if (node->color == RED) {
                if (node->left->color == RED || node->rigth->color == RED) {
                    std::cout << "Red\n";
                    return false;
                }
            }
            int leftBlackHeight = _getBlackHeight(node->left);
            int rigthBlackHeight = _getBlackHeight(node->rigth);
            if (leftBlackHeight != rigthBlackHeight) {
                std::cout << "Black\n";
                return false;
            }
            return _testRedBlack(node->left) && _testRedBlack(node->rigth);
        }
#endif
         Node<T>* _delete_utils(Node<T>* node) {
            Node<T>* ret;
            ret = NULL;
            if (node == root) {
                if (!node->rigth->isNull) {
                    root = node->rigth;
                    node->rigth->parrent = NULL;
                    ret = node->rigth;
                    alloc.deallocate(node->left, 1);
                    alloc.deallocate(node, 1);
                }
                else if (!node->left->isNull) {
                    root = node->left;
                    node->left->parrent = NULL;
                    ret = node->left;
                    alloc.deallocate(node->rigth, 1);
                    alloc.deallocate(node, 1);
                }
                else {
                    alloc.deallocate(node->left, 1);
                    alloc.deallocate(node->rigth, 1);
                    alloc.deallocate(node, 1);
                    root = NULL;
                    ret = NULL;
                }
            }
            else if (!node->left->isNull) {
                if (node == node->parrent->left) {
                    node->parrent->left = node->left;
                    node->left->parrent = node->parrent;
                }
                else {
                    node->parrent->rigth = node->left;
                    node->left->parrent = node->parrent;
                }
                ret = node->left;
                alloc.deallocate(node->rigth, 1);
                alloc.deallocate(node, 1);
            }
            else {
                if (node == node->parrent->left) {
                    node->parrent->left = node->rigth;
                    node->rigth->parrent = node->parrent;
                }
                else {
                    node->parrent->rigth = node->rigth;
                    node->rigth->parrent = node->parrent;
                }
                ret = node->rigth;
                alloc.deallocate(node->left, 1);
                alloc.deallocate(node, 1);
            }
            return ret;
        }

    public:

        RedBlackTree () { 
            _comp = Compar();
            root = NULL; 
            sz = 0;
        }

        RedBlackTree(RedBlackTree const& rhs) {
            _comp = Compar();
            this->node = rhs.node;
            this->sz = rhs.sz; 
        }

        ~RedBlackTree() {
            while (this->getRoot()) {
                this->deleteNode(this->getRoot()->value);
            }
        }

        size_t size() {
            return this->sz;
        }

        Node<T>* getRoot() {
            return root;
        }

        Node<T>* search(T const& value)
        {
            if (!root)
                return NULL;
            Node<T>* temp = this->root;
            while (!temp->isNull)
            {
                if (_comp(value, temp->value))
                    temp = temp->left;
                else if (_comp(temp->value, value))
                    temp = temp->rigth;
                else
                    break;
            }
            return (temp);
        }

        void insert(T const& value) {
            int i = 0;
            if (!root)
            {
                this->sz++;
                this->root = this->alloc.allocate(1);
                this->_init(NULL, this->root, BLACK, value);
            }
            else {
                Node<T>* temp = root;
                Node<T>* temp_parrent;
                int n = 0;
                while (true)
                {
                    temp_parrent = temp;
                    if (_comp(temp->value, value))
                    {
                        temp = temp->rigth;
                        n = 0;
                    }
                    else if (_comp(value, temp->value))
                    {
                        temp = temp->left;
                        n = 1;
                    }
                    else if (!_comp(value, temp->value) && !_comp(temp->value, value)) {
                        i = 1;
                        break;
                    }
                    if (temp->isNull)
                    {
                        this->sz++;
                        this->_init(temp_parrent, temp, RED, value);
                        if (!n)
                            temp_parrent->rigth = temp;
                        else
                            temp_parrent->left = temp;
                        break;
                    }
                }
                if (!i)
                    _InsertFix(temp);
            }
        }

        Node<T>* min() {
            Node<T>* temp;
            temp = root;
            while (!temp->left->isNull)
                temp = temp->left;
            return (temp);
        }

        Node<T>* max() {
            Node<T>* temp;
            temp = root;
            while (!temp->rigth->isNull)
                temp = temp->rigth;
            return (temp);
        }

        void deleteNode(T const& value) {
            Node<T>* node = search(value);
            Node<T>* temp;
            temp = NULL;
            int color_deleted;
            if (!node || node->isNull)
                return ;
            this->sz--;
            if (!node->left->isNull && !node->rigth->isNull) {
                temp = node->rigth;
                while (!temp->left->isNull)
                    temp = temp->left;
                _changePosition(node, temp);
                color_deleted = temp->color;
                temp = _delete_utils(temp);
            }
            else {
                color_deleted = node->color;
                temp = _delete_utils(node);
            }
            if (color_deleted == BLACK && temp)
                _deleteFix(temp);
        }

       
#if 1
        bool testRedBlack() const {
            return _testRedBlack(root);
        }

        void _printTree(const std::string &prefix, Node<T> *node, bool is_rigth) const {
                if (!node || node->isNull) return;
                std::cout << prefix;
                if (node->parrent)
                    std::cout << (is_rigth ? "├─ r:" : "└─ l:" );
                else
                    std::cout << "root:";

                std::cout << (node->color == RED ? "\033[0;31m" : "\033[0m") << node->value.first << "\033[0m" << std::endl; 
                _printTree( prefix + (is_rigth ? "│  " : "   "), node->rigth, true);
                _printTree( prefix + (is_rigth ? "│  " : "   "), node->left, false);
            }
        void printTree() const {
            _printTree("", root, false);
        }

        void print() {
            iterator it(min());
        }
#endif
        };
#endif
