/**
* @file Tests.cpp
* @brief Definition of tests to check graph integrity and to get some useful information
* @author G17_5
* @date 30/03/2024
*/

#include "../lib/Tests.hpp"

//! Time Complexity: O(V), Space Complexity: O(1)
void test_edges(Graph &g) {
    std::cout << "\n=============================================================================\n";
    std::cout << __func__ << '\n';
    std::cout << g.getVertexSet().size() << '\n';
}

//! Time Complexity: O(V), Space Complexity: O(1)
void test_vertexes(Graph &g) {
    std::cout << "\n=============================================================================\n";
    std::cout << __func__ << '\n';
    std::cout << g.getVertexSet().size() << '\n';
}

//! Time Complexity: O(V * E), Space Complexity: O(1)
void test_remove_vertexes(Graph &g) {
    std::cout << "\n=============================================================================\n";
    std::cout << __func__ << '\n';
    std::cout << g.getVertexSet().size() << '\n';
}

//! Time Complexity: O(V * E), Space Complexity: O(1)
void test_remove_edges(Graph &g) {
    std::cout << "\n=============================================================================\n";
    std::cout << __func__ << '\n';
    std::cout << g.getVertexSet().size() << '\n';
}

//! Time Complexity: O(V * E), Space Complexity: O(1)
void test_suite(Graph &g) {
    test_edges(g);
    test_vertexes(g);
    test_remove_vertexes(g);
    test_remove_edges(g);
}
