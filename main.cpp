#include <iostream>
#include "generate_graphs.hpp"

int main() {
    // for predictability & repeatability
    std::srand((unsigned) time(nullptr));
    auto graphs = generate_graphs();
    for (auto graph: graphs) {
        graph.show_graph();
        graph.find_3col_paint();
        graph.show_colors();
    }
    return 0;
}
