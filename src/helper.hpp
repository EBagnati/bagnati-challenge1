#ifndef HELPER_HPP
#define HELPER_HPP

// Here I enclose some helper functions and some aliases that I will use in my code

#include <vector>
#include <iostream> // To print error messages
#include <cmath>    // To compute sqrt for the norm
#include <functional> // To include function wrappers

// I will use std::vector<double> to represent vectorial quantities and points in the space Rn
using Point = std::vector<double>;

// R_function will represent a function from R^n to R (e.g. the function f to minimize)
using R_Function = std::function<double(Point)>;

// Rn_function will represent a function from R^n to R^n (e.g. the gradient)
using Rn_Function = std::function<Point(Point)>;

// Enumerator to choose which strategy to use to update alpha_k
enum Strategy {EXPONENTIAL, INVERSE, ARMIJO};

// Function to compute the norm of a vector
double vector_norm(const std::vector<double>& p);

// Overload operator '-' to compute difference between Points
Point operator-(const Point& p1, const Point& p2);

// Overload operator '*' to compute scalar * vector product
Point operator*(double s, const Point& v);

// Function to print a vector
void print_vector(const std::vector<double>& v, const std::string& name);

// Function to compute the gradient by finite differences
Rn_Function numerical_gradient(const R_Function& f, const double h);

// FUNZIONI VECCHIE DA CANCELLARE
/*
// Function to compute the difference of two vectors (a - b)
std::vector<double> vector_diff(const std::vector<double>& a, const std::vector<double>& b);

// Function to compute scalar * vector product
std::vector<double> scalar_vector_prod(double s, const std::vector<double>& v);
*/

#endif