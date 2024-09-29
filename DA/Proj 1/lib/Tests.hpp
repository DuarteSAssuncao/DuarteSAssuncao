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
void test_edges(Graph& g);

//! Checks if the number of vertexes is correct
void test_vertexes(Graph& g);           

//! Checks if all cities are correct
void test_cities(Graph& g);

//! Checks if all reservoirs are correct
void test_reservoirs(Graph& g);

//! Displays information about flow vs. demand
void test_demand(Graph& g);

//! Displays information about flow vs. capacity
void test_capacity(Graph& g);

//! Displays information about flow vs. max delivery
void test_max_delivery(Graph &g);

//! Tests the removal of vertexes and its impact on the graph
void test_remove_vertexes(Graph& g);

//! Tests the removal of edges and its impact on the graph
void test_remove_edges(Graph& g);

//! Test how much the flow changes after a removal
void test_flow_after_remove(Graph g);

//! Calculates some statistics
void test_edge_statistics(Graph& g);

//! Executes all tests
void test_suite(Graph &g);

#endif // TESTS_HPP
