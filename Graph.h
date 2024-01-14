//
// Created by Александр Тармаев on 12.10.2023.
//

#ifndef INC_3PAINT_GRAPH_H
#define INC_3PAINT_GRAPH_H

#include <vector>

class Graph {
public:
    explicit Graph(size_t v_num);
    Graph(size_t v_num, std::vector<std::vector<bool>>& edges);
    Graph(size_t v_num, std::vector<std::vector<bool>>& edges, std::vector<size_t>& v_color);

    size_t get_v_num();

    std::vector<std::vector<bool>> get_edges();

    void show_graph();
    void show_colors();

    void find_3col_paint();
    void add_edge(size_t i, size_t j);
    void add_edge_with_probability(size_t i, size_t j, long double p);

private:
    size_t v_num;
    std::vector<std::vector<bool>> edges;
    std::vector<size_t> v_color;

    size_t find_non_colored_neighbors_degree(size_t vertex);
    void colorize_neighbors(size_t vertex);
    void dfs_colorize(size_t root, size_t color, bool is_height_even);
    std::vector<size_t> find_uncolored();
    void color_uncolored_with_small_degree();
};


#endif //INC_3PAINT_GRAPH_H
