#include "helper.hpp"

double vector_norm(const Point& p)
{
    double norm = 0;

    for(size_t i = 0; i < p.size(); ++i)
    {
        norm += p[i] * p[i];
    }

    return std::sqrt(norm);
}

void print_vector(const std::vector<double>& v, const std::string& name)
{
    std::cout << name << " = [";
    for(size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i];
        if(i < v.size() - 1)
        {
            std::cout << ", ";
        }
        else
        {
            std::cout << "]" << std::endl;
        }
    }
}

Point operator-(const Point& p1, const Point& p2)
{
    Point diff;

    if(p1.size() != p2.size())
    {
        std::cerr << "ERROR: vectors have different size!" << std::endl;
        return diff;
    }

    // Since the size is known, preallocate space to be more efficient
    diff.resize(p1.size());
    for(size_t i = 0; i < p1.size(); ++i)
    {
        diff[i] = p1[i] - p2[i];
    }

    return diff;
}

Point scalar_vector_prod(double s, const Point& v)
{
    Point result;

    // Since the size is known, preallocate space to be more efficient
    result.resize(v.size());
    for(size_t i = 0; i < v.size(); ++i)
    {
        result[i] = s * v[i];
    }

    return result;
}

