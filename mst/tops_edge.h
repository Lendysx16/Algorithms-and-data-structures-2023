//
// Created by Gleb Kurguzov on 14.05.2023.
//

#ifndef MST_TOPS_EDGE_H
#define MST_TOPS_EDGE_H

struct top_edges{
    int top1 = 0;
    int top2 = 0;
    int weight = 0;
};
bool operator< (const top_edges &el1, const top_edges &el2){
    return el1.weight < el2.weight;
}
#endif //MST_TOPS_EDGE_H
