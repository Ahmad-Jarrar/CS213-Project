#include <iostream>
#include <random>
#include <chrono>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/operation.hpp>
#include <boost/numeric/ublas/operation_blocked.hpp>


using namespace boost::numeric::ublas;

void input (int* dim1, int* dim2) {
    std::cout << "Enter rows of matrix 1:";
    std::cin >> dim1[0];
    std::cout << "Enter columns of matrix 1:";
    std::cin >> dim1[1];
    std::cout << "Enter rows of matrix 2:";
    std::cin >> dim2[0];
    std::cout << "Enter columns of matrix 2:";
    std::cin >> dim2[1];
}
void print_matrix(matrix<int> m) {
    for (unsigned i = 0; i < m.size1(); ++i)
    {
        for (unsigned j = 0; j < m.size2(); ++j)
            std::cout << m(i,j) << " ";
        std::cout << std::endl;
    }
}

int main()
{
    int dim1[2], dim2[2];

    input(dim1, dim2);

    while (dim1[1] != dim2[0])
    {
        std::cout << "Dimensions Invalid! Matrices cannot be multiplied\n";
        input(dim1, dim2);
    }
    

    matrix<int> A(dim1[0], dim1[1]);
    matrix<int> B(dim2[0],dim2[1]);

    matrix<int> C(dim1[0],dim2[1]);

    // Random matrix initialization and print matrix
    for (unsigned i = 0; i < A.size1(); ++i)
        for (unsigned j = 0; j < A.size2(); ++j)
            A(i, j) = rand() % 10;

    for (unsigned i = 0; i < B.size1(); ++i)
        for (unsigned j = 0; j < B.size2(); ++j)
            B(i, j) = rand() % 10;

    auto start = std::chrono::high_resolution_clock::now();
    C = prod(A, B);
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 

    std::cout << "Time taken(microseconds): " << duration.count() << std::endl;

    // Print product
    // print_matrix(C);
}