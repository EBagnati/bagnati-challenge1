#include "Parameters.hpp"
#include "helper.hpp"
#include <iostream>
#include <functional>


double fun(const Point& x);
Point exact_grad(const Point& x);

template<int S> Point minimize(const R_Function& f, const Rn_Function& grad_f, const Parameters& parameters);

int main()
{
    // Read and print parameters
    Parameters parameters("parameters.txt");
    parameters.print();

    // Define function wrapper for exact and numerical gradient
    std::vector<Rn_Function> gradient_fun;
    gradient_fun.push_back(exact_grad);
    gradient_fun.push_back(numerical_gradient(fun, parameters.h));

    // Let the user choose between exact and numerical gradient
    std::cout << "\nWould you like to use exact gradient (0) or numerical gradient (1)?" << std::endl;
    unsigned choice = 0;
    std::cin >> choice;

    if(choice != 0 && choice != 1)
    {
        // Invalid input
        std::cerr << "Invalid input. Using exact gradient as default" << std::endl;
        choice = 0;
    }
    
    
    // Compute minimum
    Point minimum = minimize<ARMIJO>(fun, gradient_fun[choice], parameters);

    // Print the solution
    std::cout << "==============================" << std::endl;
    std::cout << "SOLUTION ARMIJO" << std::endl;
    std::cout << "==============================" << std::endl;
    print_vector(minimum, "x_min");

    // Compute minimum
    minimum = minimize<EXPONENTIAL>(fun, gradient_fun[choice], parameters);

    // Print the solution
    std::cout << "==============================" << std::endl;
    std::cout << "SOLUTION EXPONENTIAL" << std::endl;
    std::cout << "==============================" << std::endl;
    print_vector(minimum, "x_min");

    // Compute minimum
    minimum = minimize<INVERSE>(fun, gradient_fun[choice], parameters);

    // Print the solution
    std::cout << "==============================" << std::endl;
    std::cout << "SOLUTION INVERSE" << std::endl;
    std::cout << "==============================" << std::endl;
    print_vector(minimum, "x_min");
 
    return 0;
}


double fun(const Point& x)
{
    double x1 = x[0];
    double x2 = x[1];

    return x1*x2 + 4.0*pow(x1,4) + pow(x2,2) + 3.0*x1;
}

Point exact_grad(const Point& x)
{
    Point grad(2);
    double x1 = x[0];
    double x2 = x[1];

    grad[0] = x2 + 16.0*pow(x1,3) + 3.0;
    grad[1] = x1 + 2.0*x2;

    return grad;
}


template<int S> Point minimize(const R_Function& f, const Rn_Function& grad_f, const Parameters& parameters)
{
    unsigned k = 0;                 // Number of iterations
    Point x_k = parameters.x_0;     
    Point x_k_1;                    
    double alpha_k;     
    bool terminate = false;         // Checks stopping criteria

    while (!terminate)  
    {
        ++k;

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

            while((f(x_k) - f(x_k - (alpha_k * grad_f(x_k)))) < parameters.sigma*alpha_k*pow(vector_norm(grad_f(x_k)), 2))
            {
                // The decrease condition is not satisfied -> divide alpha by 2
                alpha_k = alpha_k / 2.0;
            }

        }

        x_k_1 = x_k - (alpha_k * grad_f(x_k));

        // Evaluate stopping criteria. If at least one of them is satisfied, 'terminate' becomes 'true' and I exit the loop
        terminate = vector_norm(x_k_1 - x_k) < parameters.epsilon_s || std::abs(f(x_k_1) - f(x_k)) < parameters.epsilon_r || k > parameters.kmax;
        x_k = x_k_1;
    } 
    
    if(k > parameters.kmax)
    {
        std::cerr << "Ended after reaching max number of iterations. No convergence!!" << std::endl;
    }

    return x_k_1;
}

