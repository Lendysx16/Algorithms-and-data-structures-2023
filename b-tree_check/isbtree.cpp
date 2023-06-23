#include <iostream>
#include "b_tree_check.h"


int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Specify input file name";
        return 1;
    }
    auto input = std::ifstream(argv[1]);
    if (!input) {
        std::cerr << "Can not open input file";
        return 2;
    }
    int N;
    int t;
    int root;
    bool flag = true;
    input >> N >> t >> root;
    auto **arr = new Node_ptr[N];
    Node_ptr root_node = nullptr;
    for (int i = 0; i < N; ++i) {
        arr[i] = nullptr;
    }
    for (int i = 0; i < N; ++i) {
        auto *tmp_node = my::b_tree::Node::read_node_from_file(input);
        if (tmp_node == nullptr) {
            flag = false;
            break;
        }
        if (tmp_node->address_of_node == root) {
            root_node = tmp_node;
        } else {
            if (tmp_node->number_of_values < t - 1 ||
                tmp_node->number_of_values > 2 * t - 1 ||
                (!tmp_node->is_leaf && (tmp_node->number_of_children < t || tmp_node->number_of_children > 2 * t))) {
                delete tmp_node;
                flag = false;
                break;
            }
        }
        arr[i] = tmp_node;
    }
    input.close();
    
    if (!flag) {
        std::cout << "no";
        for (auto i = 0; i < N; ++i) {
            delete arr[i];
        }
        delete[] arr;
        return 0;
    }
    int level = 0;
    if(root_node == nullptr){
        std::cout << "no";
        for (auto i = 0; i < N; ++i) {
            delete arr[i];
        }
        delete[] arr;
        return 0;
    }
    flag = check_root(arr, t, root_node, N);
    if (flag) {
        for (int i = 0; i < N; ++i) {
            if (arr[i]->is_leaf) {
                if (level == 0) {
                    level = arr[i]->level;
                }
                if (level != arr[i]->level) {
                    flag = false;
                    break;
                }
            }
        }
    }
    if (flag) {
        std::cout << "yes";
    } else {
        std::cout << "no";
    }

    for (auto i = 0; i < N; ++i) {
        delete arr[i];
    }
    delete[] arr;
    return 0;
}

