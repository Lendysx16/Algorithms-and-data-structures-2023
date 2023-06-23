#ifndef B_TREE_CHECKER_B_TREE_NODE_H
#define B_TREE_CHECKER_B_TREE_NODE_H

#include <fstream>
#include <iostream>

int read_num_from_charptr(const char *str, int idx, int end_idx) {
  int res = 0;
  for (int i = idx; i < end_idx; ++i) {
    res *= 10;
    res += str[i] - '0';
  }
  return res;
}

bool is_array_sorted(const int *arr, int size) {
  if (arr == nullptr) {
    return false;
  }
  for (int i = 0; i < size - 1; ++i) {
    if (arr[i] > arr[i + 1]) {
      return false;
    }
  }
  return true;
}

namespace my {
namespace b_tree {
struct Node {
  int *values = nullptr;
  int *children_node_address = nullptr;
  int number_of_values = 0;
  int number_of_children = 0;
  int address_of_node = 0;
  bool is_leaf = false;
  int level = 0;

  Node(bool is_leaf_, int num_chil, int num_val, int *val, int *chil, int addr)
      : is_leaf(is_leaf_),
        number_of_children(num_chil),
        number_of_values(num_val),
        values(val),
        children_node_address(chil),
        address_of_node(addr) {}

  Node() = default;

  ~Node() {
    delete[] values;
    delete[] children_node_address;
  }

  static Node *read_node_from_file(std::ifstream &input) {
    Node *res = new Node();
    char buffer[256] = "";
    input >> buffer;
    if (buffer[0] == 'l') {
      res->is_leaf = true;
    }
    input >> buffer;
    int cnt = 0;
    while (buffer[cnt] != '\0') {
      ++cnt;
    }
    res->address_of_node = read_num_from_charptr(buffer, 2, cnt);
    input >> buffer;
    cnt = 0;
    while (buffer[cnt] != ':') {
      ++cnt;
    }
    res->number_of_values = read_num_from_charptr(buffer, 1, cnt);
    res->values = new int[res->number_of_values];
    for (int i = 0; i < res->number_of_values; ++i) {
      input >> res->values[i];
    }
    if (!is_array_sorted(res->values, res->number_of_values)) {
      delete res;
      return nullptr;
    }
    input >> buffer;
    if (!res->is_leaf) {
      input >> buffer;
      cnt = 0;
      while (buffer[cnt] != ':') {
        ++cnt;
      }
      res->number_of_children = read_num_from_charptr(buffer, 1, cnt);
      res->children_node_address = new int[res->number_of_children];
      for (int i = 0; i < res->number_of_children; ++i) {
        input >> res->children_node_address[i];
      }
      input >> buffer;
    } else {
      if (input.peek() != '\n') {
        delete res;
        return nullptr;
      }
    }
    return res;
  }
};
}  // namespace b_tree
}  // namespace my

#endif
