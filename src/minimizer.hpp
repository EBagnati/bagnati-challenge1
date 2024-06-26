#ifndef MINIMIZER_HPP
#define MINIMIZER_HPP

// ==================================================================================
// Functions to compute the minimum
// ==================================================================================
#include "helper.hpp"
#include "Parameters.hpp"

// Template function to compute the minimum by gradient method
template<int S> Point minimize_gradient(const R_Function& f, const Rn_Function& grad_f, const Parameters& parameters)
{
    unsigned k = 0;                 // Number of iterations
    Point x_k = parameters.x_0;     
    Point x_k_1;                    
    double alpha_k;     
    bool terminate = false;         // Checks stopping criteria

    while (!terminate)  
    {
        //Update alpha_k according to the chosen strategy
        if constexpr(S == EXPONENTIAL)
        {
            // Implement exponential decay
            alpha_k = parameters.alpha_0 * exp(-parameters.mu* k);
        }

        else if constexpr(S == INVERSE)
        {
            // Implement inverse decay
            alpha_k = parameters.alpha_0 / (1. + parameters.mu *k);
        }

        else if constexpr(S == ARMIJO)
        {
            // Implement Armijo Rule
            alpha_k = parameters.alpha_0;

            while((f(x_k) - f(x_k - scalar_vector_prod(alpha_k, grad_f(x_k)))) < parameters.sigma*alpha_k*pow(vector_norm(grad_f(x_k)), 2))
            {
                // The decrease condition is not satisfied -> divide alpha by 2
                alpha_k = alpha_k / 2.0;
            }

        }

        x_k_1 = x_k - scalar_vector_prod(alpha_k, grad_f(x_k));
        ++k;

        // Evaluate stopping criteria. If at least one of them is satisfied, 'terminate' becomes 'true' and I exit the loop
        terminate = vector_norm(x_k_1 - x_k) < parameters.epsilon_s || 
                    std::abs(f(x_k_1) - f(x_k)) < parameters.epsilon_r || 
                    k > parameters.kmax;
                    
        x_k = x_k_1;        
    } 
    
    if(k > parameters.kmax)
    {
        // Warning for the user if the method ended just because we reached the max number of iterations
        std::cout << "Ended after reaching max number of iterations. No convergence!!" << std::endl;
    }

    return x_k_1;
}


// Template function to compute the minimum by momentum method 
template<int S> Point minimize_momentum(const R_Function& f, const Rn_Function& grad_f, const Parameters& parameters)
{
    unsigned k = 0;                 // Number of iterations
    Point x_k = parameters.x_0;     
    Point x_k_1;                    
    double alpha_k_1;   
    bool terminate = false;         // Checks stopping criteria
    Point d_k = scalar_vector_prod(-parameters.alpha_0, grad_f(parameters.x_0));   // Initial value of d_0
    Point d_k_1;

    while (!terminate)
    {
        ++k;

        // Update solution
        x_k_1 = x_k + d_k;

        //Update alpha_k according to the chosen strategy
        if constexpr(S == EXPONENTIAL)
        {
            // Implement exponential decay
            alpha_k_1 = parameters.alpha_0 * exp(-parameters.mu* k);
        }

        else if constexpr(S == INVERSE)
        {
            // Implement inverse decay
            alpha_k_1 = parameters.alpha_0 / (1. + parameters.mu *k);
        }

        else if constexpr(S == ARMIJO)
        {
            // Now Armijo rule cannot be applied
            std::cerr << "ERROR: Armijo rule cannot be applied for momentum method" << std::endl;
            return Point();
        }

        // Update direction d_k:
        d_k_1 = scalar_vector_prod(parameters.eta, d_k) - scalar_vector_prod(alpha_k_1, grad_f(x_k_1));

         // Evaluate stopping criteria. If at least one of them is satisfied, 'terminate' becomes 'true' and I exit the loop
        terminate = vector_norm(x_k_1 - x_k) < parameters.epsilon_s || 
                    std::abs(f(x_k_1) - f(x_k)) < parameters.epsilon_r || 
                    k > parameters.kmax;
                    
        x_k = x_k_1;
        d_k = d_k_1;
    }
    
    if(k > parameters.kmax)
    {
        // Warning for the user if the method ended just because we reached the max number of iterations
        std::cout << "Ended after reaching max number of iterations. No convergence!!" << std::endl;
    }

    return x_k_1;
}


#endif