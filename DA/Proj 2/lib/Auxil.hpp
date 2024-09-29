/**
 * @file Auxil.hpp
 * @brief Declaration of auxiliary functions for some algorithms
 * @author G17_5
 * @date 17/05/2024
*/

#ifndef AUXIL_HPP
#define AUXIL_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include "Vertex.hpp"

/**
 * @brief Computes string subsets using bit manipulation
 * @param const std::vector<Vertex*> set : set with all the vertexes
 * @param std::vector<std::string>& subsets : vector with all the subsets
 * @return void
 * @note Time Complexity: O(2^n*n), Space Complexity: O(2^n)
 */
void computeBitSubsets(
    const std::vector<Vertex*> set,
    std::vector<std::string>& subsets
);

/**
 * @brief Computes string subsets using recursion
 * @param const std::vector<Vertex*> set : set with all the vertexes
 * @param std::vector<std::string>& subsets : vector with all the subsets
 * @param std::string subset = "" : current subset
 * @param unsigned int n = 0 : how many recursive calls have been made so far
 * @return void
 * @note Time Complexity: O(2^n*n), Space Complexity: O(2^n)
 */
void computeStringSubsets(
    std::vector<Vertex*>& set,
    std::vector<std::string>& subsets,
    std::string subset = "",
    unsigned int n = 0
);

/**
 * @brief Computes subsets using recursion
 * @param std::vector<Vertex*>& set : set with all the vertexes
 * @param std::vector<std::vector<Vertex*>>& subsets : vector with all the subsets
 * @param std::vector<Vertex*> subset = {} : current subset
 * @param unsigned int n = 0 : how many recursive calls have been made so far
 * @return void
 * @note Time Complexity: O(2^n*n), Space Complexity: O(2^n)
 */
void computeSubsets(
    std::vector<Vertex*>& set, 
    std::vector<std::vector<Vertex*>>& subsets,
    std::vector<Vertex*> subset = {}, 
    unsigned int n = 0
);

/**
 * @brief Auxiliary DFS algorithm for the Triangle Inequality approach
 * @param Vertex* v : current Vertex
 * @param std::vector<Vertex*>& path : path obtained with the algorithm
 * @return void
 * @note Time Complexity: O(V + E), Space Complexity: O(V)
 */
void triangleInequalityDFS(Vertex* v, std::vector<Vertex*>& path);

/**
 * @brief Auxiliary DFS algorithm for the Backtracking approach
 * @param Vertex* v : current Vertex
 * @param size_t i : recursive calls missing to reach source again
 * @param double& min : the minimum length obtained so far
 * @param double length : the length of the path obtained so far
 * @param Vertex* src : where to end the path (and to begin)
 * @param std::vector<Vertex*> path : current path
 * @param std::vector<Vertex*>& minPath : the shortest path so far
 * @return void
 * @note Time Complexity: O(V + E), Space Complexity: O(V)
 */
void backtrackDFS(
        Vertex* v,
        size_t i,
        double& min, 
        double length, 
        Vertex* src,
        std::vector<Vertex*> path,
        std::vector<Vertex*>& minPath
);

#endif // AUXIL_HPP
