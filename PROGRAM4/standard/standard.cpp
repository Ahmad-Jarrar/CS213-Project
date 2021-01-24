#include <iostream>
#include <random>
#include <chrono>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/operation.hpp>
#include <boost/numeric/ublas/operation_blocked.hpp>

#include "../common.hpp"

using namespace boost::numeric::ublas;

int main()
{
    int dim1[2], dim2[2];
    // Input valid Matrices
    input(dim1, dim2);
    while (dim1[1] != dim2[0])
    {
        std::cout << "Dimensions Invalid! Matrices cannot be multiplied\n";
        input(dim1, dim2);
    }

    matrix<int> A(dim1[0], dim1[1]);
    matrix<int> B(dim2[0],dim2[1]);

    matrix<int> C;

    // Random matrix initialization and print matrix
    initialize_matrix(&A, true, 10);
    initialize_matrix(&B, true, 10);
    // print_matrix(A);
    // print_matrix(B);

    // Test Standard Multiplication method in boost library
    auto start = std::chrono::high_resolution_clock::now();
    C = prod(A, B);
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 

    std::cout << "Elapsed time for Standard Approach: " << duration.count() <<
        " microseconds." << std::endl;

    // Print product
    // print_matrix(C);
}