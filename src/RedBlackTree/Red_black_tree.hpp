#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

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
        void init(Noeud<T>* parrent, Noeud<T>* noeud)
        {
            noeud->color = 0;
            noeud->parrent = parrent;
            noeud->value = 0;
            noeud->left = NULL;
            noeud->rigth = NULL;
        }

    public:
        RedBlackTree() { tree = new Noeud<T>;}
        void leftRotate(Noeud<T>* noeud) {
            Noeud<T>* rigth = noeud->rigth;
            if (!rigth)
                return ;
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
            left->parrent = noeud->parrent;
            noeud->parrent = left;
            noeud->left = left->rigth;
            if (left->rigth)
                left->rigth->parrent = noeud;
            left->rigth = noeud;
            if (left->parrent == NULL)
                this->tree = left;
        }

};
#endif
