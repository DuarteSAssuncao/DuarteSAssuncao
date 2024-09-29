/**
* @file Tests.hpp
* @brief Declaration of tests to check Graph integrity and correctness
* @author G17_5
* @date 30/03/2024
*/

#ifndef TESTS_HPP
#define TESTS_HPP

#include "Graph.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Macros.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cmath>

//! Checks if the number of edges is correct
void test_edges(Graph &g);

//! Checks if the number of vertexes is correct
void test_vertexes(Graph &g);

//! Tests the removal of vertexes and its impact on the graph
void test_remove_vertexes(Graph &g);

//! Tests the removal of edges and its impact on the graph
void test_remove_edges(Graph &g);

//! Executes all tests
void test_suite(Graph &g);

#endif // TESTS_HPP