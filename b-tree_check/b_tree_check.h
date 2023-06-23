#ifndef B_TREE_CHECKER_B_TREE_CHECK_H
#define B_TREE_CHECKER_B_TREE_CHECK_H


#include "b_tree_node.h"
#include <iostream>
typedef my::b_tree::Node* Node_ptr;

int idx_of_node(Node_ptr *arr, int size_of_arr, int addr);
bool check_root(Node_ptr *arr, int t, Node_ptr root, int size_of_arr);
bool check_child(Node_ptr *arr, Node_ptr node_to_check, int left, int right, bool is_left_closed, bool is_right_closed, int height, int size_of_arr);
bool check_interval(Node_ptr node_to_check, int left, int right, bool is_left_closed, bool is_right_closed);





bool check_root(Node_ptr *arr, int t, Node_ptr root, int size_of_arr){
    bool flag = root->number_of_children > 1 &&
                root->number_of_children < 2 * t + 1;
    if(root->is_leaf){
        flag = true;
    }
    if (!flag) {
        return false;
    }
    int height = 0;

    for (int i = 0; i < root->number_of_children; ++i) {
        int idx_of_child = idx_of_node(arr, size_of_arr, root->children_node_address[i]);
        if(idx_of_child == -1){
          return false;
        }
        Node_ptr child = arr[idx_of_child];
        if (i == 0) {
            flag = check_child(arr, child, 0, root->values[0], false, true, height, size_of_arr);
        } else if (i == root->number_of_children - 1) {
            flag = check_child(arr, child, root->values[i - 1], 0, true, false, height, size_of_arr);
        } else {
            flag = check_child(arr, child, root->values[i - 1], root->values[i], true, true, height, size_of_arr);
        }
        if(!flag){
            return false;
        }
    }
    return flag;
}


bool check_interval(Node_ptr node_to_check, int left, int right, bool is_left_closed, bool is_right_closed) {
    for (int i = 0; i < node_to_check->number_of_values; ++i) {
        if (is_left_closed) {
            if (node_to_check->values[i] <= left) {
                return false;
            }
        }
        if (is_right_closed) {
            if (node_to_check->values[i] >= right) {
                return false;
            }
        }
    }
    return true;
}

bool check_child(Node_ptr *arr, Node_ptr node_to_check, int left, int right, bool is_left_closed, bool is_right_closed, int height, int size_of_arr){
    if(node_to_check == nullptr){
        return false;
    }
    ++height;
    node_to_check->level = height;
    if(node_to_check->is_leaf){
        return check_interval(node_to_check, left, right, is_left_closed, is_right_closed);
    }
    bool flag = check_interval(node_to_check, left, right, is_left_closed, is_right_closed);
    if(!flag){
        return false;
    }
    for(int i = 0; i < node_to_check->number_of_children; ++i){
        int idx_of_child = idx_of_node(arr, size_of_arr, node_to_check->children_node_address[i]);
        if(idx_of_child == -1){
            return false;
        }
        Node_ptr child = arr[idx_of_child];
        if(i == 0){
            flag = check_child(arr, child, left, node_to_check->values[0], is_left_closed, true, height, size_of_arr);
        } else if(i == node_to_check->number_of_children - 1){
            flag = check_child(arr, child, node_to_check->values[i - 1], right, true, is_right_closed, height, size_of_arr);
        } else {
            flag = check_child(arr, child, node_to_check->values[i - 1], node_to_check->values[i], true, true, height, size_of_arr);
        }
        if(!flag){
            return false;
        }
    }
    return flag;
}

int idx_of_node(Node_ptr *arr, int size_of_arr, int addr){
    for (int i = 0; i < size_of_arr; ++i) {
        if (arr[i]->address_of_node == addr) {
            return i;
        }
    }
    return -1;
}

#endif
