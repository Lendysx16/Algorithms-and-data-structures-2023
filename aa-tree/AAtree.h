

#ifndef AA_TREE_AATREE_H
#define AA_TREE_AATREE_H

#include <iostream>

namespace my {
    template<typename T>
    class AAtree {
    private:
        struct Node {
            T value;
            size_t level = 1;
            Node *left = nullptr;
            Node *right = nullptr;

            Node() = default;

            Node(T value_, size_t level_, Node *left_, Node *right_) : value(value_), level(level_), left(left_),
                                                                       right(right_) {};


        };

        void decreaseLevel(Node *el);

        Node *root = nullptr;


        Node *skew(Node *el);

        Node *split(Node *el);

        Node *insertNode(Node *el, T value);

        void deconstruct(Node *el) {
            if (el == nullptr) { return; }
            if (el->right) {
                deconstruct(el->right);
            }
            if (el->left) {
                deconstruct(el->left);
            }
            delete el;
        };

        void copy_node(Node *src, Node *dst);

        Node *successor(Node *el);

        Node *predecessor(Node *el);

        Node *delete_node(Node *el, T value);

    public:
        bool is_empty() {
            return root == nullptr;
        }

        size_t balance() {
            if (!root) { return 0; }
            return root->level;
        }

        void remove(T value) {
            root = delete_node(root, value);

        }

        void insert(T value) {
            root = insertNode(root, value);
        }

        ~AAtree() {
            deconstruct(root);
            root = nullptr;
        }

        AAtree() {
            root = nullptr;
        }

        AAtree(const AAtree<T> &el) {
            root = new Node();
            copy_node(el.root, root);
        }

        bool find(T value) {
            Node *tmp = root;
            while (true) {
                if (tmp == nullptr) { return false; }
                if (tmp->value == value) { return true; }
                if (value > tmp->value) { tmp = tmp->right; }
                else {
                    tmp = tmp->left;
                }
            }
        };
    };


    template<typename T>
    typename AAtree<T>::Node *AAtree<T>::skew(Node *el) {
        if (el == nullptr) {
            return el;
        }
        if (el->left == nullptr) {
            return el;
        }
        if (el->left->level == el->level) {
            Node *tmp = el;
            el = el->left;
            Node *tmp_right = el->right;
            el->right = tmp;
            el->right->left = tmp_right;
            tmp_right = nullptr;
            tmp = nullptr;
            return el;
        }
        return el;
    }

    template<typename T>
    typename AAtree<T>::Node *AAtree<T>::split(AAtree::Node *el) {
        if (el == nullptr) { return el; }
        if (el->right == nullptr || el->right->right == nullptr) { return el; }
        if (el->level == el->right->right->level) {
            Node *tmp = el;
            el = el->right;
            el->level += 1;
            Node *left_tmp = el->left;
            el->left = tmp;
            el->left->right = left_tmp;
            left_tmp = nullptr;
            tmp = nullptr;
            return el;
        }
        return el;
    }

    template<typename T>
    typename AAtree<T>::Node *AAtree<T>::insertNode(AAtree::Node *el, T value) {
        if (root == nullptr) {
            root = new Node(value, 1, nullptr, nullptr);
            return root;
        }
        if (el == nullptr) {
            return new Node(value, 1, nullptr, nullptr);
        } 
        if (value < el->value) {
            el->left = insertNode(el->left, value);
        } else {
            el->right = insertNode(el->right, value);
        }
        el = skew(el);
        el = split(el);
        return el;
    }


    template<typename T>
    void AAtree<T>::copy_node(AAtree::Node *src, AAtree::Node *dst) {
        dst->value = src->value;
        if (src->left) {
            dst->left = new Node();
            copy_node(src->left, dst->left);
        }
        if (src->right) {
            dst->right = new Node();
            copy_node(src->right, dst->right);
        }
    }

    template<typename T>
    typename AAtree<T>::Node *AAtree<T>::successor(AAtree::Node *el) {
        el = el->right;
        while (el->left != nullptr) {
            el = el->left;
        }
        return el;
    }

    template<typename T>
    typename AAtree<T>::Node *AAtree<T>::predecessor(AAtree::Node *el) {
        el = el->left;
        while (el->right != nullptr) {
            el = el->right;
        }
        return el;
    }

    template<typename T>
    typename AAtree<T>::Node *AAtree<T>::delete_node(AAtree::Node *el, T value) {

        if (el && value > el->value ) {
            el->right = delete_node(el->right, value);
        }
        else if (el && value < el->value) {
            el->left = delete_node(el->left, value);
        }
        else if (el){
            if (el->left == nullptr && el->right == nullptr) {
                delete el;
                return nullptr;
            }
            if (el->left == nullptr) {
                Node *l = successor(el);
                el->value = l->value;
                el->right = delete_node(el->right, l->value);
                l = nullptr;

            } else {
                Node *l = predecessor(el);
                el->value = l->value;
                el->left = delete_node(el->left, l->value);
                l = nullptr;
            }
        }
         if(!el){
             return nullptr;
         }
        decreaseLevel(el);
        el = skew(el);
        if (el) {
            el->right = skew(el->right);
        }
        if (el->right) {
            el->right->right = skew(el->right->right);
        }
        el = split(el);
        if (el) {
            el->right = split(el->right);
        }
        return el;
    }

    template<typename T>
    void AAtree<T>::decreaseLevel(AAtree::Node *el) {
        size_t left_lvl = el->left != nullptr ? el->left->level : 0;
        size_t right_lvl = el->right != nullptr ? el->right->level : 0;
        size_t expected_lvl = std::min(left_lvl, right_lvl) + 1;
        if (el->level > expected_lvl) {
            el->level = expected_lvl;
            if (right_lvl != 0 && right_lvl > expected_lvl) {
                el->right->level = expected_lvl;
            }
        }
    }

}


#endif
