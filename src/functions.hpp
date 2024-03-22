#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "helper.hpp"

// ====================================================================================================================
// In this file I enclose the function to be minimized, its gradient and a function to compute the gradient numerically
// ====================================================================================================================

// The function to be minimized
double fun(const Point& x);

// The exact gradient 
Point exact_grad(const Point& x);

// Function to compute the gradient by finite differences
Rn_Function numerical_gradient(const R_Function& f, const double h);


#endif