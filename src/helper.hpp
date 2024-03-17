#ifndef HELPER_HPP
#define HELPER_HPP

// Here I enclose some helper functions and some aliases that I will use in my code

#include <vector>
#include <iostream> // To print error messages
#include <cmath>    // To compute sqrt for the norm

// I will use std::vector<double> to represent vectorial quantities and points in the space Rn
using Point = std::vector<double>;

// Enumerator to choose which strategy to use to update alpha_k
enum Strategy {EXPONENTIAL, INVERSE, ARMIJO};

// Function to compute the norm of a vector
double vector_norm(const std::vector<double>& p);

// Function to compute the difference of two vectors (a - b)
std::vector<double> vector_diff(const std::vector<double>& a, const std::vector<double>& b);

// Function to compute scalar * vector product
std::vector<double> scalar_vector_prod(double s, const std::vector<double>& v);

// Function to print a vector
void print_vector(const std::vector<double>& v, const std::string& name);

#endif