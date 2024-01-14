//
// Created by Александр Тармаев on 12.10.2023.
//

#include "Graph.h"

Graph generate_3col_random_graph
(size_t num1, size_t num2, size_t num3, long double p) {
    Graph G(num1 + num2 + num3);
    for (size_t v1 = 0; v1 < num1; ++v1) {
        for (size_t v2 = num1; v2 < num1 + num2; ++v2) {
            G.add_edge_with_probability(v1, v2, p);
        }

        for (size_t v3 = num1 + num2; v3 < num1 + num2 + num3; ++v3) {
            G.add_edge_with_probability(v1, v3, p);
        }
    }

    for (size_t v2 = num1; v2 < num1 + num2; ++v2) {
        for (size_t v3 = num1 + num2; v3 < num1 + num2 + num3; ++v3) {
            G.add_edge_with_probability(v2, v3, p);
        }
    }

    return G;
}

std::vector<Graph> generate_cycles() {
    std::vector<size_t> v_nums = {4, 5, 10, 31};
    std::vector<Graph> ans;
    for (size_t v_num: v_nums) {
        Graph G(v_num);
        for (size_t i = 0; i < v_num; ++i) {
            size_t j_next = (i + 1) % v_num;
            G.add_edge(i, j_next);
        }
        ans.push_back(G);
    }

    return ans;
}

std::vector<Graph> generate_graphs() {
    std::vector<Graph> ans;
    auto cycles = generate_cycles();
    ans.insert(ans.end(), cycles.begin(), cycles.end());

    for (int i = 0; i < 5; ++i) {
        auto G = generate_3col_random_graph
                (1 + rand() % 10, 1 + rand() % 10, 1 + rand() % 10, 0.5);
        ans.push_back(G);
    }
    return ans;
}