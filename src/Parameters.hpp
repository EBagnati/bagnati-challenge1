#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include <vector>
#include <string>
#include "helper.hpp"

using Point=std::vector<double>;

struct Parameters
{
    // Here I store all the parameters of my problem
    
    // Constructor to read parameters from a file
    Parameters(const std::string &filename);

    Point x_0;              // Initial guess
    double epsilon_r;       // Tolerance on residual
    double epsilon_s;       // Tolerance on step length
    double alpha_0;         // Initial value of learning rate alpha
    double mu;              // Parameter mu used in exponential and inverse decay
    double sigma;           // Parameter sigma used in Armijo rule
    unsigned kmax;          // Max number of iterations
    double h;               // Step length in central difference scheme to approximate the gradient
    
    // Method to print all parameters
    void print() const;
};

#endif