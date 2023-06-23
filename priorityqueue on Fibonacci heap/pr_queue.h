
#ifndef PR_QUEUE_PR_QUEUE_H
#define PR_QUEUE_PR_QUEUE_H

#include <iostream>

namespace my {

    struct Node {
        int value = 0;
        Node *parent = nullptr;
        Node *child = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;
        int degree = 0;
        bool mark = false;
    };


    class pr_queue {
    private:
        Node *min = nullptr;
        size_t size = 0;

        void delete_mid(Node *mid);

        static void add_child(Node *addto, Node *el);

        static Node *merge_two_lists(Node *fst, Node *snd);

        static void delete_connections(Node *el);

        void merge(pr_queue &el);

        static void delete_parent(Node *el);

        Node *cut(Node *el) {
            if (el->right == el) {
                if (el->parent != nullptr) {
                    el->parent->child = nullptr;
                    --el->parent->degree;
                }
            } else {
                delete_connections(el);
                if (el->parent != nullptr) {
                    el->parent->child = el->right;
                    --el->parent->degree;
                }
            }
            el->right = el->left = el;
            el->mark = false;
            el = merge_two_lists(min, el);
            return el;
        }

    public:
        pr_queue() = default;

        void decrease_key(Node *el, int new_value);


        void consolidate();

        int extract_min();


        ~pr_queue() {
            delete_mid(min);
        }

        Node *insert(int key);


    };

    Node *pr_queue::insert(int key) {
        Node *ptr_to_new_node = new Node();
        ptr_to_new_node->value = key;
        size += 1;
        if (min == nullptr) {
            min = ptr_to_new_node;
            min->right = min;
            min->left = min;
            return min;
        }
        Node *tmp_right = min->right;
        min->right = ptr_to_new_node;
        ptr_to_new_node->right = tmp_right;
        ptr_to_new_node->left = min;
        tmp_right->left = ptr_to_new_node;
        if (ptr_to_new_node->value < min->value) {
            min = ptr_to_new_node;
        }
        return ptr_to_new_node;

    }

    Node *pr_queue::merge_two_lists(Node *fst, Node *snd) {
        if(fst == nullptr){
            return snd;
        }
        if(snd == nullptr) {
            return fst;
        }
        if (fst->value > snd->value) {
            std::swap(fst, snd);
        }
        Node *Lfst = fst->left;
        Node *Rsnd = snd->right;
        snd->right = fst;
        fst->left = snd;
        Lfst->right = Rsnd;
        Rsnd->left = Lfst;
        return fst;
    }

    void pr_queue::delete_mid(Node *mid) {
        if (mid != nullptr) {
            Node *tmp1 = mid;
            Node *tmp2 = nullptr;
            do {
                tmp2 = tmp1;
                tmp1 = tmp1->right;
                delete_mid(tmp2->child);
                delete tmp2;
            } while (tmp1 != mid);
        }
    }

    void pr_queue::merge(pr_queue &el) {

        if (el.min == nullptr) {
            return;
        }
        if (this->min == nullptr) {
            size = el.size;
            this->min = el.min;
        } else {
            merge_two_lists(min, el.min);
            if (el.min->value < min->value) {
                min = el.min;
            }
        }


    }

    void pr_queue::consolidate() {
        if (min == nullptr) {
            return;
        }
        if (min->right == min) {
            min = min->child;
        } else {
            delete_connections(min);
            if (min->child != nullptr) {
                merge_two_lists(min->right, min->child);
            }
        }
        if (min != nullptr) {
            min = min->right;
        }


        Node **arr = new Node *[(size >> 1) + 3];
        for (size_t i = 0; i < (size >> 1) + 3; ++i) {
            arr[i] = nullptr;
        }

        Node *tmp = min;
        while (true) {
            if(tmp == nullptr){
                throw std::bad_alloc();
            }
            if (arr[tmp->degree] != nullptr) {
                Node *t = arr[tmp->degree];
                if (t == tmp) {
                    break;
                }
                arr[tmp->degree] = nullptr;
                if (tmp->value < t->value) {
                    delete_connections(t);
                    add_child(tmp, t);
                } else {
                    delete_connections(t);
                    if (tmp->right == tmp) {
                        t->right = t->left = t;
                        add_child(t, tmp);
                        tmp = t;
                    } else {
                        tmp->left->right = t;
                        tmp->right->left = t;
                        t->right = tmp->right;
                        t->left = tmp->left;
                        add_child(t, tmp);
                        tmp = t;

                    }
                }
            } else {
                arr[tmp->degree] = tmp;
                tmp = tmp->right;
            }

        }
        Node *start = tmp;
        do {
            if (tmp->value <= min->value) {
                min = tmp;
            }
            tmp = tmp->right;
        } while (tmp != start);

        delete[] arr;
    }

    int pr_queue::extract_min() {

        if (size == 0) {
            throw std::out_of_range("no elements in queue");
        }
        --size;
        Node *to_delete = min;
        int min_value = to_delete->value;
        if (size != 0) {
            if (min->child != nullptr) {
                delete_parent(min->child);
            }
            consolidate();
        } else {
            min = nullptr;
        }
        delete to_delete;
        return min_value;

    }

    void pr_queue::add_child(Node *addto, Node *el) {
        el->right = el->left = el;
        el->parent = addto;
        ++addto->degree;
        if (addto->child == nullptr) {
            addto->child = el;
        } else {
            merge_two_lists(addto->child, el);
        }
    }

    void pr_queue::delete_connections(Node *el) {
        el->left->right = el->right;
        el->right->left = el->left;

    }

    void pr_queue::delete_parent(Node *el) {
        Node *start = el;
        do {
            el->parent = nullptr;
            el = el->right;
        } while (el != start);
    }

    void pr_queue::decrease_key(Node *el, int new_value) {
        el->value = new_value;
        if (el == min) { return; }
        if (el->parent != nullptr) {
            if (el->value < el->parent->value) {
                min = cut(el);
                Node *parent = el->parent;
                el->parent = nullptr;
                while (parent != nullptr && parent->mark) {
                    min = cut(parent);
                    el = parent;
                    parent = el->parent;
                    el->parent = nullptr;
                }
                if (parent != nullptr && parent->parent != nullptr) {
                    parent->mark = true;
                }

            }
        } else {
            if (min != nullptr && el->value < min->value) {
                min = el;
            }
        }
    }

}
#endif
