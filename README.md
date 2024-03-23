# Challenge 1 - Minimization of a multivariate function

This program can be used to compute the minimum of a multivariate function through the gradient method and the momentum method. More in detail:

- The parameters of the problem are listed in the text file `parameters.txt`. This is very convenient because they are all gathered in the same place and they can be easily modified by the user

- In the files `parameters.hpp` and `parameters.cpp` I have implemented a struct that reads the parameters from the text file using `GetPot`(if some of them are not found, I assign an admissible default value that allows the program to proceed). This struct is passed as argument to the function that calculates the minimum and also has a method to print all the values to check them

- In the file `minimizer.hpp` I have implemented two different template functions to compute the minimum with **gradient method** or **momentum method**.
They take as input the function to be minimized, its gradient and the parameters struct. The learning rate *alpha* can be updated in different ways, and we can choose at compile time which strategy to use changing the template parameter.

-  In the files `helper.hpp` and `helper.cpp` I have enclosed some aliases used in the code and some helper functions to work with *std::vectors* 

-  In the files `functions.hpp` and `functions.cpp` I have implemented the function to be minimized and its gradient. This can be the exact gradient or a numerical approximation made by finite differences. The user can choose at runtime which gradient to use by typing '0' or '1' in the command line, and this is handled very easily in the program using function wrappers

Writing `make` in the terminal we can compile the program and get the executable
