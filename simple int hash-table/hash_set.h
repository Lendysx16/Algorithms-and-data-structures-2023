
#ifndef HASH_HASH_SET_H
#define HASH_HASH_SET_H
#include <iostream>
namespace my {
    class hash_set_int {
    private:
        struct Node {
            int value = 0;
            Node *next = nullptr;

            Node() = default;
        };

        Node **main_arr = nullptr;
        int size = 900;
        int a = 3;
        int b = 42;
        int p = 991;

        void free(Node *el) {
            if (el != nullptr && el->next != nullptr) {
                free(el->next);
            }
            delete el;
        }

        int get_hash(int el) const {
            return std::abs((a * el + b) % p % size);
        }
        Node* find_previous(int el){
            int hash = get_hash(el);
            Node* ptr = main_arr[hash];
            if(ptr == nullptr) {return nullptr;}
            if(ptr ->value == el){
                return ptr;
            }
            while (ptr->next != nullptr){
                if(ptr->next->value == el){
                    return ptr;
                }
                ptr = ptr->next;
            }
            return nullptr;
        }

    public:
        hash_set_int() {
            main_arr = new Node *[size];
            for (int i = 0; i < size; ++i) {
                main_arr[i] = nullptr;
            }
        }

        ~hash_set_int() {
            for (int i = 0; i < size; ++i) {
                free(main_arr[i]);
            }
            delete[] main_arr;
        }

        void add(int el) {
            int hash = get_hash(el);
            if (main_arr[hash] == nullptr) {
                main_arr[hash] = new Node;
                main_arr[hash]->value = el;
                main_arr[hash]->next = nullptr;
            } else {
                Node *ptr = main_arr[hash];
                while (ptr->next != nullptr) {
                    ptr = ptr->next;
                }
                ptr->next = new Node;
                ptr = ptr->next;
                ptr->value = el;
                ptr->next = nullptr;
            }
        }

        bool find_el(int el){
            auto *ptr = find_previous(el);
            return ptr != nullptr;
        }

        void remove(int el){
            auto *ptr = find_previous(el);
            if(ptr == nullptr){
                return;
            }
            if(ptr->value == el){
                int hash = get_hash(el);
                main_arr[hash] = ptr->next;
                ptr->next = nullptr;
                delete ptr;
                return;
            }
            auto *to_del = ptr->next;
            ptr->next = to_del->next;
            to_del->next = nullptr;
            delete to_del;
        }

    };
}
#endif
