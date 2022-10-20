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
    T value;
};

template <typename T>
class RedBlackTree {
    private:
        Noeud<T> *tree;
        std::allocator<Noeud<T> > alloc;
        void init(Noeud<T>* parrent, Noeud<T>* noeud)
        {
            noeud->color = BLACK;
            noeud->parrent = parrent;
            noeud->value = 0;
            noeud->left = NULL;
            noeud->rigth = NULL;
        }
        Noeud<T>* new_noeud() {
            Noeud<T>* ret = alloc.allocate(1);
            return (ret);
        }

    public:
        RedBlackTree() { tree = NULL;}
        void leftRotate(Noeud<T>* noeud) {
            Noeud<T>* rigth = noeud->rigth;
            if (!rigth)
                return ;
            if (noeud == noeud->parrent->left)
                noeud->parrent->left = rigth;
            else 
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
            if (!left)
                return ;
            if (noeud == noeud->parrent->left)
                noeud->parrent->left = left;
            else 
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

        void recolor(Noeud<T>* noeud)
        {
            noeud->color == BLACK ? (noeud->color = RED) : (noeud->color = BLACK);
        }

        void insert(T const& value) {
            if (!tree)
            {
                this->tree = this->new_noeud();
                this->init(NULL, this->tree);
                this->tree->value = value;
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
                    if (temp == NULL)
                    {
                        temp = new_noeud();
                        this->init(temp_parrent, temp);
                        temp->value = value;
                        if (!n)
                            temp_parrent->rigth = temp;
                        else
                            temp_parrent->left = temp;
                        break;
                    }
                }
            }
        }


        void display(int n)
        {
            while (n--)
                std::cout <<" ";
            std::cout << tree->value << std::endl;
            std::cout << tree->rigth->value << std::endl;
            std::cout << tree->left->value << std::endl;
        }

};
#endif
