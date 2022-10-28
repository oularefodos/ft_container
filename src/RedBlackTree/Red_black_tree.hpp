#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

 #define RED 1
 #define BLACK 0

template <typename T>
struct Noeud {
    int color;
    Noeud* left;
    Noeud* rigth;
    Noeud* parrent;
    bool    isNull;
    T value;
};

template <typename T>
class RedBlackTree_iterator {
    private:
        Noeud<T>* node;
        Noeud<T>* begin(Noeud<T>* root) {
            Noeud<T>* temp;
            temp = root;
            while (!temp->left->isNull)
                temp = temp->left;
            return (temp);
        }
        Noeud<T>* end(Noeud<T>* root) {
            Noeud<T>* temp;
            temp = root;
            while (!temp->rigth->isNull)
                temp = temp->rigth;
            return (temp);
        }
        Noeud<T>* getRoot(Noeud<T>* _node) {
            Noeud<T> *root = _node;
            while (root->parrent)
                root = root->parrent;
            return root;
        }
        Noeud<T>* max(Noeud<T>* _node) {
            Noeud<T>* m = getRoot(_node);
            while (!m->rigth->isNull)
                m = m->rigth;
            return m;
        }
        Noeud<T>* min(Noeud<T>* _node) {
            Noeud<T>* m = getRoot(_node);
            while (!m->left->isNull)
                m = m->left;
            return m;
        }
    public:
        RedBlackTree_iterator(Noeud<T> * _node) {node = _node;}
        RedBlackTree_iterator(RedBlackTree_iterator const& rhs) {
            this->node = rhs.node;
        }

        RedBlackTree_iterator& operator=(RedBlackTree_iterator const& rhs) {
            this->node = rhs.node;
            return *this;
        }

        Noeud<T>* operator->(){
            return this->node;
        }

        Noeud<const T>* operator->() const {
            return this->node;
        }

        RedBlackTree_iterator& operator++() {
            if (!node->isNull) {
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
            if (!node->isNull) {
                if (node->parrent == NULL)
                    node = end(node->left);
                if (min(node) == node)
                    node = node->left;
                else if (node->parrent && node == node->parrent->rigth && node->left->isNull)
                    node = node->parrent;
                else if (node->parrent && node == node->parrent->left && !node->left->isNull)
                    node = end(node->left);
                else if (node->parrent && node == node->parrent->rigth && !node->rigth->isNull)
                    node = node->left;
                else {
                    while (node->parrent == node->parrent->parrent->left)
                        node = node->parrent;
                    node = node->parrent->parrent;
                }
            }
            return *this;
        }

        RedBlackTree_iterator& operator++(int) {
            RedBlackTree_iterator temp(node);
            ++(*this);
            return temp;
        }

        RedBlackTree_iterator& operator--(int) {
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

template <typename T>
class RedBlackTree {
    private:
        Noeud<T> *root;
        size_t sz;
        std::allocator<Noeud<T> > alloc;
        typedef  RedBlackTree_iterator<T> iterator;
        void init(Noeud<T>* parrent, Noeud<T>* noeud, int _color, T _value)
        {
            noeud->color = _color;
            noeud->parrent = parrent;
            noeud->isNull = false;
            noeud->value = _value;
            noeud->left = alloc.allocate(1);
            noeud->left->isNull = true;
            noeud->left->parrent = noeud;
            noeud->left->color = BLACK;
            noeud->rigth = alloc.allocate(1);
            noeud->rigth->isNull = true;
            noeud->rigth->parrent = noeud;
            noeud->rigth->color = BLACK;
        }

        size_t _getBlackHeight(Noeud<T>*node) const {
                if (!node || node->isNull) return 0;
                size_t leftHeight = _getBlackHeight(node->left);
                return leftHeight + (node->color == BLACK);
            }

        bool _testRedBlack(Noeud<T>*node) const {
            if (!node || node->isNull) return true;
            if (node->color == RED) {
                if (node->left->color == RED || node->rigth->color == RED) {
                    std::cout << "Red\n";
                    return false;
                }
            }
            int leftBlackHeight = _getBlackHeight(node->left);
            int rightBlackHeight = _getBlackHeight(node->rigth);
            if (leftBlackHeight != rightBlackHeight) {
                std::cout << "Black\n";
                return false;
            }
            return _testRedBlack(node->left) && _testRedBlack(node->rigth);
        }

        Noeud<T>* delOne(Noeud<T>* node) {
            Noeud<T>* ret;
            ret = NULL;
            if (node->left->isNull && node->rigth->isNull)
            {
                if (node == node->parrent->left)
                    node->parrent->left = node->left;
                else
                    node->parrent->rigth = node->left;
                ret = NULL;
                alloc.deallocate(node->rigth, 1);
                alloc.deallocate(node, 1);
            }
            else if (node->left->isNull || node->rigth->isNull)
            {
                if (node->left->isNull)
                {
                    if (node == node->parrent->left)
                    {
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
                else {
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
            }
            return ret;
        }
        void seg() {std::cout << "*******SEGFAULT*******" << std::endl;}

    public:
        RedBlackTree() { root = NULL; sz = 0;}
        size_t size() {return this->sz;}
        void leftRotate(Noeud<T>* noeud) {
            Noeud<T>* rigth = noeud->rigth;
            if (rigth->isNull)
                return ;
            if (noeud->parrent && noeud == noeud->parrent->left)
                noeud->parrent->left = rigth;
            else if (noeud->parrent && noeud != noeud->parrent->left)
                noeud->parrent->rigth = rigth;
            rigth->parrent = noeud->parrent;
            noeud->parrent = rigth;
            noeud->rigth = rigth->left;
            if (rigth->left)
                rigth->left->parrent = noeud;
            rigth->left = noeud;
            if (rigth->parrent == NULL)
                this->root = rigth;
        }

        Noeud<T>* getRoot() {
            return root;
        }

        int testTree(Noeud<T>* temp) {
            int i = 0;
            int y = 0;
            int ret = 0;
            int v = 0;
            if (temp->isNull == false) {
                if (temp->color == RED) {
                    if (temp->left->color == RED || temp->rigth->color == RED) {
                        std::cout << "ERREUR dans l'abre" << std::endl;
                        exit(1);
                    }
                    else {
                        v = 1;
                    }
                }
                if (!temp->left->isNull)
                    i += testTree(temp->left);
                if (!temp->rigth->isNull)
                    y += testTree(temp->rigth);
                if (i == y && v == 1)
                    std::cout << "Success" << std::endl;
                else
                    std::cout << "Wrong" << std::endl;
                temp->color ? (ret = 0) : (ret = 1);
            }
            return (ret);
        }

        void rigthRotate (Noeud<T> *noeud) {
            Noeud<T>* left = noeud->left;
            if (left->isNull)
                return ;
            if (noeud->parrent && noeud == noeud->parrent->left)
                noeud->parrent->left = left;
            else if (noeud->parrent && noeud != noeud->parrent->left)
                noeud->parrent->rigth = left;
            left->parrent = noeud->parrent;
            noeud->parrent = left;
            noeud->left = left->rigth;
            if (left->rigth)
                left->rigth->parrent = noeud;
            left->rigth = noeud;
            if (left->parrent == NULL)
                this->root = left;
        }

        Noeud<T>* search(T const& value)
        {
            Noeud<T>* temp = this->root;
            while (!temp->isNull)
            {
                if (temp->value > value)
                    temp = temp->left;
                else if (temp->value < value)
                    temp = temp->rigth;
                else if (temp->value == value)
                    break;
            }
            return (temp);
        }

        void print() {
            iterator it(min());
            while (!it.ret())
            {
                std::cout << *it << std::endl;
                ++it;
            }
        }

        void insert(T const& value) {
            this->sz++;
            if (!root)
            {
                this->root = this->alloc.allocate(1);
                this->init(NULL, this->root, BLACK, value);
            }
            else {
                Noeud<T>* temp = root;
                Noeud<T>* temp_parrent;
                int n = 0;
                while (true)
                {
                    temp_parrent = temp;
                    if (temp->value < value)
                    {
                        temp = temp->rigth;
                        n = 0;
                    }
                    else if (temp->value > value)
                    {
                        temp = temp->left;
                        n = 1;
                    }
                    else if (temp->value == value)
                        break;
                    if (temp->isNull)
                    {
                        this->init(temp_parrent, temp, RED, value);
                        if (!n)
                            temp_parrent->rigth = temp;
                        else
                            temp_parrent->left = temp;
                        break;
                    }
                }
                InsertFix(temp);
            }
        }

        Noeud<T>* min() {
            Noeud<T>* temp;
            temp = root;
            while (!temp->left->isNull)
                temp = temp->left;
            return (temp);
        }

        Noeud<T>* max() {
            Noeud<T>* temp;
            temp = root;
            while (!temp->rigth->isNull)
                temp = temp->rigth;
            return (temp);
        }

        void display(int n, Noeud<T>* noeud, int m)
        {
            if (noeud->isNull)
                return ;
            int i = 0;
            while (i++ < n)
                std::cout <<"  ";
            if (m == 2)
                std::cout << "ROOT --->";
            if (!m)
                std::cout << "LEFT --->";
            if (m == 1)
                std::cout << "RIGTH --->";
            if (noeud->color == RED)
                std::cout << " color : RED | " ;
            else   
                std::cout << " color : BLACK | " ;
            
            std::cout << "Value : " << noeud->value << std::endl << std::endl;
            if (noeud->left)
            {
                display(n + 10, noeud->left, 0);
            }
            if (noeud->rigth)
                display(n + 10, noeud->rigth, 1);
        }

        void InsertFix(Noeud<T>* noeud) {
            Noeud<T>* u;
            while (noeud->parrent && noeud->parrent->color == RED) {
                if (noeud->parrent == noeud->parrent->parrent->rigth) {
                    u = noeud->parrent->parrent->left; // uncle
                    if (u->color == RED) // 3.1 
                    {
                        u->color = BLACK;
                        noeud->parrent->color = BLACK;
                        if (noeud->parrent->parrent != root)
                            noeud->parrent->parrent->color = RED;
                        noeud = noeud->parrent->parrent;
                    }
                    else {
                        if (noeud == noeud->parrent->left)
                        {
                            noeud = noeud->parrent;
                            rigthRotate(noeud);
                        }
                        noeud->parrent->color = BLACK;
                        noeud->parrent->parrent->color = RED;
                        leftRotate(noeud->parrent->parrent);
                    }                  
                }
                else {
                    u = noeud->parrent->parrent->rigth;
                    if (u->color == RED) {
                        u->color = BLACK;
                        noeud->parrent->color = BLACK;
                        if (noeud->parrent->parrent != root)
                            noeud->parrent->parrent->color = RED;
                        noeud = noeud->parrent->parrent;
                    }
                    else {
                        if (noeud == noeud->parrent->rigth)
                        {
                                noeud = noeud->parrent;
                                leftRotate(noeud); 
                        }
                        noeud->parrent->color = BLACK;
                        noeud->parrent->parrent->color = RED;
                        rigthRotate(noeud->parrent->parrent);
                    }
                }
                if (noeud == root)
                    break ;
            }
        }

        void deleteNode(T const& value) {
            Noeud<T>* node = search(value);
            Noeud<T>* temp;
            int to_delete_color;
            if (node->isNull) {
                std::cout << "this key not found" << std::endl;
                return ;
            }
            this->sz--;
            if (node->left->isNull || node->rigth->isNull)
            {
                to_delete_color = node->color;
                temp = this->delOne(node);
            }
            else {
                temp = node->rigth;
                while (!temp->left->isNull)
                    temp = temp->left;
                node->value = temp->value;
                to_delete_color = temp->color;
                temp = this->delOne(temp);
            }
            if (to_delete_color == BLACK && temp)
                deleteFix(temp);
        }

        void deleteFix(Noeud<T>* node) {
            Noeud<T> *s;
            while (node != root && node->color == BLACK) {
                if (node == node->parrent->left) {
                    s = node->parrent->rigth;
                    if (s->color == RED) {
                        s->color = BLACK;
                        node->parrent->color = RED;
                        leftRotate(node->parrent);
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
                            rigthRotate(s);
                            s = node->parrent->rigth;
                        }
                        s->color = node->parrent->color;
                        s->parrent->color = BLACK;
                        s->rigth->color = BLACK;
                        leftRotate(node->parrent);
                        node = root;
                    }
                } else {
                    s = node->parrent->left;
                    if (s->color == RED) {
                        s->color = BLACK;
                        node->parrent->color = RED;
                        rigthRotate(node->parrent);
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
                            leftRotate(s);
                            s = node->parrent->left;
                        }
                        s->color = node->parrent->color;
                        node->parrent->color = BLACK;
                        s->left->color = BLACK;
                        rigthRotate(node->parrent);
                        node = root;
                    }
                }
            }
            node->color = BLACK;
        }

        bool testRedBlack() const {
            return _testRedBlack(root);
        }

        void _printTree(const std::string &prefix, Noeud<T> *node, bool is_right) const {
                if (!node || node->isNull) return;
                std::cout << prefix;
                if (node->parrent)
                    std::cout << (is_right ? "├─ r:" : "└─ l:" );
                else
                    std::cout << "root:";

                std::cout << (node->color == RED ? "\033[0;31m" : "\033[0m") << node->value << "\033[0m" << std::endl; 
                _printTree( prefix + (is_right ? "│  " : "   "), node->rigth, true);
                _printTree( prefix + (is_right ? "│  " : "   "), node->left, false);
            }
        void printTree() const {
            _printTree("", root, false);
        }


};
#endif
