#include "Parameters.hpp"
#include "GetPot"
#include <sstream>

Parameters::Parameters(const std::string& filename)
{
    GetPot file(filename.c_str());

    epsilon_r = file("eps_r", 0.);
    epsilon_s = file("eps_s", 0.);
    alpha_0 = file("alpha_0", 0.);
    mu = file("mu", 0.);
    sigma = file("sigma", 0.);
    kmax = file("kmax", 0);
    
    std::istringstream iss{file("x_0", "")};
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
    print_vector(x_0, "x_0");
}