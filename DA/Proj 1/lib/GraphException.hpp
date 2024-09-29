/**
 * @file GraphException.hpp
 * @brief Declaration and definition of a custom class exception
 * @author G17_5
 * @date 30/03/2024
 */

#ifndef GRAPH_EXCEPTION_HPP
#define GRAPH_EXCEPTION_HPP

#include <stdexcept>

//!An exception just like std::runtime_error, it just allows isolating Graph exceptions from other exceptions
class GraphException : public std::runtime_error {
    using std::runtime_error::runtime_error; // copies constructors
};

#endif // GRAPH_EXCEPTION_HPP
