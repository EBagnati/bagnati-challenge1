#include "Parameters.hpp"
#include "helper.hpp"
#include <iostream>
#include "functions.hpp"
#include "minimizer.hpp"

int main()
{
    // Read and print parameters
    Parameters parameters("parameters.txt");
    parameters.print();

    // Store in a vector the exact and numerical gradients
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
    
    
    // Compute and print minimum with gradient method - armijo rule 
    std::cout << "==============================" << std::endl;
    std::cout << "GRADIENT METHOD - ARMIJO" << std::endl;
    std::cout << "==============================" << std::endl;
    Point minimum = minimize_gradient<ARMIJO>(fun, gradient_fun[choice], parameters);
    print_vector(minimum, "x_min");

    // Compute and print minimum with gradient method - exponential decay 
    std::cout << "==============================" << std::endl;
    std::cout << "GRADIENT METHOD -  EXPONENTIAL" << std::endl;
    std::cout << "==============================" << std::endl;
    minimum = minimize_gradient<EXPONENTIAL>(fun, gradient_fun[choice], parameters);
    print_vector(minimum, "x_min");

    // Compute and print minimum with gradient method - inverse decay 
    std::cout << "==============================" << std::endl;
    std::cout << "GRADIENT METHOD -  INVERSE" << std::endl;
    std::cout << "==============================" << std::endl;
    minimum = minimize_gradient<INVERSE>(fun, gradient_fun[choice], parameters);
    print_vector(minimum, "x_min");

    // Compute minimum with momentum method - exponential decay
    std::cout << "==============================" << std::endl;
    std::cout << "MOMENTUM METHOD - EXPONENTIAL" << std::endl;
    std::cout << "==============================" << std::endl;
    minimum = minimize_momentum<EXPONENTIAL>(fun, gradient_fun[choice], parameters);
    print_vector(minimum, "x_min");

    // Compute minimum with momentum method - inverse decay
    std::cout << "==============================" << std::endl;
    std::cout << "MOMENTUM METHOD - INVERSE" << std::endl;
    std::cout << "==============================" << std::endl;
    minimum = minimize_momentum<INVERSE>(fun, gradient_fun[choice], parameters);
    print_vector(minimum, "x_min");
 
    return 0;
}

