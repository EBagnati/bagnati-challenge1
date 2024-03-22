#include "functions.hpp"

double fun(const Point& x)
{
    // fun(x1, x2) = x1*x2 + 4*x1^4 + x2^2 + 3 * x1 
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

Rn_Function numerical_gradient(const R_Function& f, const double h)
{
    return [f,h] (const Point& x) {
        // Point to store the resulting gradient
        Point res(x.size());
        // Points x_h+1 and x_h-1 used in the centeral difference scheme 
        Point x_up;
        Point x_down;

        for(size_t i = 0; i < x.size(); ++i)
        {
            // At each iteration, increase (or decrease) just the i-th component of x_up (or x_down) by the step h
            x_up = x;
            x_down = x;
            x_up[i] += h;            
            x_down[i] -= h;

            // Central difference scheme for the i-th derivative
            res[i] = (f(x_up) - f(x_down)) / (2.0 * h);
        }
        return res;
    };
}
