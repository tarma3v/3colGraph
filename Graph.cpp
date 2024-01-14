//
// Created by Александр Тармаев on 12.10.2023.
//

#include <algorithm>
#include <iostream>
#include <set>
#include "Graph.h"

Graph::Graph(size_t v_num): v_num(v_num) {
    edges = std::vector<std::vector<bool>>
            (v_num, std::vector<bool>(v_num, false));
    v_color = std::vector<size_t>(v_num, 0);
}

Graph::Graph(size_t v_num, std::vector<std::vector<bool>> &edges):
    v_num(v_num),
    edges(edges) {}

Graph::Graph(size_t v_num, std::vector<std::vector<bool>> &edges, std::vector<size_t> &v_color):
    v_num(v_num),
    edges(edges),
    v_color(v_color) {}

size_t Graph::get_v_num() {
    return v_num;
}

std::vector<std::vector<bool>> Graph::get_edges() {
    return edges;
}

void Graph::add_edge(size_t i, size_t j) {
    if (i >= v_num || j >= v_num) {
        return;
    }
    edges[i][j] = true;
    edges[j][i] = true;
}

void Graph::add_edge_with_probability(size_t i, size_t j, long double p) {
    long double r = ((long double) rand() / (RAND_MAX));
    if (r <= p) {
        add_edge(i, j);
    }
}

void Graph::show_graph() {
    for (size_t i = 0; i < v_num; ++i) {
        for (size_t j = 0; j < v_num; ++j) {
            std::cout << edges[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void Graph::show_colors() {
    std::cout << "\n3-color paint for graph:\n";
     for (int i = 0; i < v_color.size(); ++i) {
         std::cout << i << " : " << v_color[i] << '\n';
     }
    std::cout << "\n<-----separator----->\n";
}

size_t Graph::find_non_colored_neighbors_degree(size_t vertex) {
    size_t cnt = 0;
    for (size_t neighbor = 0; neighbor < v_num; ++neighbor) {
        if (edges[vertex][neighbor] && v_color[neighbor] == 0) {
            ++cnt;
        }
    }
    return cnt;
}

// recursive function that colorizes root in one of two colors and
// starts from uncolored neighbors with different color
// (works in assumption that 3-coloring of graph exists)
void Graph::dfs_colorize(size_t root, size_t color, bool is_height_even) {
    v_color[root] = is_height_even ? color : color + 1;
    for (size_t neighbor = 0; neighbor < v_num; ++neighbor) {
        if (edges[root][neighbor] && v_color[neighbor] == 0) {
            dfs_colorize(neighbor, color, !is_height_even);
        }
    }
}

// paints in 2 colors all uncolored reachable vertexes of given vertex
void Graph::colorize_neighbors(size_t vertex) {
    size_t color = *std::max_element(v_color.begin(), v_color.end()) + 1;
    for (size_t neighbor = 0; neighbor < v_num; ++neighbor) {
        if (edges[vertex][neighbor] && v_color[neighbor] == 0) {
            dfs_colorize(neighbor, color, true);
        }
    }
}

std::vector<size_t> Graph::find_uncolored() {
    std::vector<size_t> uncolored;
    for (size_t vertex = 0; vertex < v_num; ++vertex) {
        if (v_color[vertex] == 0) {
            uncolored.push_back(vertex);
        }
    }
    return uncolored;
}

void Graph::color_uncolored_with_small_degree() {
    std::vector<size_t> uncolored = find_uncolored();
    size_t min_not_taken_color = *std::max_element(v_color.begin(), v_color.end()) + 1;
    for (size_t uncolored_vertex = 0; uncolored_vertex < uncolored.size(); ++uncolored_vertex) {
        std::set<size_t> taken_colors;
        for (size_t i = 0 ; i < uncolored.size(); ++i) {
            if (v_color[uncolored[i]] >= min_not_taken_color) {
                taken_colors.insert(v_color[uncolored[i]]);
            }
        }
        size_t color = min_not_taken_color;
        for (auto taken_color: taken_colors) {
            if (color == taken_color) {
                ++color;
            } else {
                break;
            }
        }
        v_color[uncolored[uncolored_vertex]] = color;
    }
}

void Graph::find_3col_paint() {
    // let's find a vertex with >= sqrt v_num degree
    for (size_t vertex = 0; vertex < v_num; ++vertex) {
        if (v_color[vertex] != 0) continue; // already colored
        size_t deg = find_non_colored_neighbors_degree(vertex);
        if (1LL * deg * deg >= 1LL * v_num) {
            colorize_neighbors(vertex);
        }
    }
    color_uncolored_with_small_degree();
}
