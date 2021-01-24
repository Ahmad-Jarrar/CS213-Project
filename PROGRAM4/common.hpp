#include <iostream>
#include <random>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/operation.hpp>
#include <boost/numeric/ublas/operation_blocked.hpp>

/*
    Takes input for dimentsions of matrix
*/
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

/*
    Prints out matrix (2d array)
*/
void print_matrix(boost::numeric::ublas::matrix<int> m) {
    for (unsigned i = 0; i < m.size1(); ++i)
    {
        for (unsigned j = 0; j < m.size2(); ++j)
            std::cout << m(i,j) << " ";
        std::cout << std::endl;
    }
}

/* 
    Initialize matrix according to the given arguments
    If random = false, initialize the matrix to given number
    If random = true, initialize matrix randomly with limit num
*/
void initialize_matrix(boost::numeric::ublas::matrix<int>* m, bool random=false, int num=0) {
    for (unsigned i = 0; i < (*m).size1(); ++i)
        for (unsigned j = 0; j < (*m).size2(); ++j)
            if (random)
                (*m)(i, j) = rand() % num;
            else
                (*m)(i, j) = num;
}