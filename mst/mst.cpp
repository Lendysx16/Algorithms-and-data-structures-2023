#include <iostream>
#include <fstream>
#include "my_vector.h"
#include "simple_dsu.h"
#include "tops_edge.h"
int main(int argc, char** argv) {
    if(argc < 2){
        std::cerr << "Specify the input file name";
        return 1;
    }
    std::ifstream input = std::ifstream(argv[1]);
    if(!input){
        std::cerr << "Input file with name " << argv[1] << " not found";
        return 2;
    }
    size_t num_of_tops;
    size_t num_of_edges;
    input >> num_of_tops >> num_of_edges;
    my::DSU graph_set = my::DSU(num_of_tops);
    my::vector<top_edges> graph_edges = my::vector<top_edges>(num_of_edges);
    for(size_t i = 0; i < num_of_edges; ++i){
        top_edges tmp;
        input >> tmp.top1  >> tmp.top2 >> tmp.weight;
        graph_edges.append(tmp);
    }
    input.close();
    graph_edges.sort();
//    for(size_t i = 0; i < graph_edges.get_size(); ++i){
//        std::cout << graph_edges[i].weight << '\t';
//    }
    int res = 0;
    for(size_t i = 0; i < num_of_edges; ++i){
        auto tmp = graph_edges[i];
        int fst = tmp.top1;
        int snd = tmp.top2;
        int weight = tmp.weight;
        if(graph_set.get(fst) != graph_set.get(snd)){
            res += weight;
            graph_set.union_dsu(fst, snd);
        }
    }


std::cout << res;
}
