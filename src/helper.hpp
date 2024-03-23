#ifndef HELPER_HPP
#define HELPER_HPP

// ==================================================================================
// Here I enclose some helper functions and some aliases that I will use in my code
// ==================================================================================

// LIBRARIES
// ==================================================================================
#include <vector>       // To work with std::vector
#include <iostream>     // To print error messages
#include <cmath>        // To compute sqrt for the norm
#include <functional>   // To include function wrappers


// ALIASES
// ==================================================================================

// I will use std::vector<double> to represent vectorial quantities and points in the space Rn
using Point = std::vector<double>;
// R_function will represent a function from R^n to R (e.g. the function f to minimize)
using R_Function = std::function<double(Point)>;
// Rn_function will represent a function from R^n to R^n (e.g. the gradient)
using Rn_Function = std::function<Point(Point)>;


// ENUMERATOR
// ==================================================================================

// Enumerator to choose which strategy to use when updating alpha_k
enum Strategy {EXPONENTIAL, INVERSE, ARMIJO};


// HELPER FUNCTIONS
// ==================================================================================

// Function to compute the norm of a vector/a Point
double vector_norm(const Point& p);

// Overload operator '-' to compute difference between Points (p1 - p2)
Point operator-(const Point& p1, const Point& p2);

// Function to compute scalar * vector product
Point scalar_vector_prod(double s, const Point& v);

// Function to print a vector ('name' is the name we want to display when printing the vector)
void print_vector(const std::vector<double>& v, const std::string& name);



#endif