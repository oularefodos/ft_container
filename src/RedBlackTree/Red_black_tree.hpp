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
class RedBlackTree {
    private:
        Noeud<T> *tree;
        size_t sz;
        std::allocator<Noeud<T> > alloc;
        void init(Noeud<T>* parrent, Noeud<T>* noeud, int _color, T _value)
        {
            noeud->color = _color;
            noeud->parrent = parrent;
            noeud->isNull = false;
            noeud->value = _value;
            noeud->left = alloc.allocate(1);
            noeud->left->isNull = true;
            noeud->left->color = BLACK;
            noeud->rigth = alloc.allocate(1);
            noeud->rigth->isNull = true;
            noeud->rigth->color = BLACK;
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
        RedBlackTree() { tree = NULL; sz = 0;}
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
                this->tree = rigth;
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
                this->tree = left;
        }

        Noeud<T>* search(T const& value)
        {
            Noeud<T>* temp = this->tree;
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

        void insert(T const& value) {
            this->sz++;
            if (!tree)
            {
                this->tree = this->alloc.allocate(1);
                this->init(NULL, this->tree, BLACK, value);
            }
            else {
                Noeud<T>* temp = tree;
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

        Noeud<T>* getTree()
        {
            return tree;
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
            while (noeud->parrent->color == RED) {
                if (noeud->parrent == noeud->parrent->parrent->rigth) {
                    u = noeud->parrent->parrent->left; // uncle
                    if (u->color == RED) // 3.1 
                    {
                        u->color = BLACK;
                        noeud->parrent->color = BLACK;
                        if (noeud->parrent->parrent != tree)
                            noeud->parrent->parrent->color = RED;
                        noeud = noeud->parrent->parrent;
                    }
                    else {
                        if (noeud == noeud->parrent->left)
                        {
                            std::cout << noeud->parrent << std::endl;
                            if (noeud->parrent->parrent != tree) {
                                noeud = noeud->parrent;
                                rigthRotate(noeud);
                            }
                            else
                                rigthRotate(noeud->parrent);
                            std::cout << noeud->parrent << std::endl;
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
                        if (noeud->parrent->parrent != tree)
                            noeud->parrent->parrent->color = RED;
                        noeud = noeud->parrent->parrent;
                    }
                    else {
                        if (noeud == noeud->parrent->left)
                        {
                            if (noeud->parrent->parrent != tree)
                            {
                                noeud = noeud->parrent;
                                leftRotate(noeud); 
                            }
                            else
                                leftRotate(noeud->parrent);
                        }
                        noeud->parrent->color = BLACK;
                        noeud->parrent->parrent->color = RED;
                        rigthRotate(noeud->parrent->parrent);
                    }
                    
                }
                if (noeud == tree)
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
            while (node != tree) {
                if (node == node->parrent->rigth) {
                    s = node->parrent->rigth;
                    if (s->color == RED) {
                        s->color = BLACK;
                        node->parrent->color = RED;
                        leftRotate(node->parrent);
                        // s = node->parrent->rigth; 
                    }
                    if (s->left->color == BLACK && s->rigth->color == BLACK) {
                        s->color = RED;
                        node = node->parrent;
                    }
                    else {
                    }
                }
            }
        }

};
#endif
