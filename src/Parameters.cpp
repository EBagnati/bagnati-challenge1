#include "Parameters.hpp"
#include "GetPot"
#include <sstream>

Parameters::Parameters(const std::string& filename)
{
    GetPot file(filename.c_str());

    epsilon_r = file("eps_r", 1.e-6);
    epsilon_s = file("eps_s", 1.e-6);
    alpha_0 = file("alpha_0", 0.1);
    mu = file("mu", 0.1);
    sigma = file("sigma", 0.1);
    kmax = file("kmax", 100);
    h = file("h", 0.1);
    
    std::istringstream iss{file("x_0", "0 0")};
    double coord;
    while(iss >> coord)
    {
        x_0.push_back(coord);
    }
    
}

void Parameters::print() const
{
    std::cout << "==============================" << std::endl;
    std::cout << "PARAMETERS" << std::endl;
    std::cout << "==============================" << std::endl;
    
    std::cout << "alpha_0 = " << alpha_0 << std::endl;
    std::cout << "mu = " << mu << std::endl;
    std::cout << "sigma = " << sigma << std::endl;
    std::cout << "eps_r = " << epsilon_r << std::endl;
    std::cout << "eps_s = " << epsilon_s << std::endl;
    std::cout << "kmax = " << kmax << std::endl; 
    std::cout << "h = " << h << std::endl; 
    print_vector(x_0, "x_0");
}