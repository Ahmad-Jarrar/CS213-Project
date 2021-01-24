#include <chrono>
#include <thread>
#include "../common.hpp"

using namespace boost::numeric::ublas;

matrix<int> matmul_naive (matrix<int> m, matrix<int> n) {

    if (m.size2() != n.size1()) {
        perror("m.size2() != n.size1()\n");
        perror("Cannot multiply!");
        exit(1);
    }
    matrix<int> mn(m.size1(), n.size2());

    // No need. Matrix is automatically initialized to zero
    // initialize_matrix(mn, false, 0);

    for (size_t i = 0; i < m.size1(); i++)
    {
        for (size_t j = 0; j < n.size2(); j++)
        {
            for (size_t k = 0; k < m.size2(); k++)
            {
                mn(i,j) += m(i,k) * n(k,j);
            }
            
        }
        
    }
    return mn;
}
// https://gist.github.com/nadavrot/5b35d44e8ba3dd718e595e40184d03f0
matrix<int> matmul_naive_optimized (matrix<int> m, matrix<int> n) {

    if (m.size2() != n.size1()) {
        perror("m.size2() != n.size1()\n");
        perror("Cannot multiply!");
        exit(1);
    }
    matrix<int> mn(m.size1(), n.size2());

    // No need. Matrix is automatically initialized to zero
    // initialize_matrix(mn, false, 0);

    for (size_t i = 0; i < m.size1(); i++)
    {
        for (size_t k = 0; k < m.size2(); k++)
        {
            for (size_t j = 0; j < n.size2(); j++)
            {
                mn(i,j) += m(i,k) * n(k,j);
            }
            
        }
        
    }
    return mn;
}

void multiply_slice(matrix<int> mn, matrix<int> m, matrix<int> n, int i) {
    for (size_t k = 0; k < m.size2(); k++)
        for (size_t j = 0; j < n.size2(); j++)
            mn(i,j) += m(i,k) * n(k,j);
}

matrix<int> matmul_naive_optimized_threaded (matrix<int> m, matrix<int> n) {

    if (m.size2() != n.size1()) {
        perror("m.size2() != n.size1()\n");
        perror("Cannot multiply!");
        exit(1);
    }
    matrix<int> mn(m.size1(), n.size2());

    // No need. Matrix is automatically initialized to zero
    // initialize_matrix(mn, false, 0);
    std::thread threads[m.size1()];
    for (size_t i = 0; i < m.size1(); i++)
    {
        threads[i] = std::thread(multiply_slice, mn, m, n, i);
    }

    for (size_t i = 0; i < m.size1(); i++)
    {
        threads[i].join();
    }
    return mn;
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

    matrix<int> C;

    // Random matrix initialization and print matrix
    initialize_matrix(&A, true, 5);
    initialize_matrix(&B, true, 5);
    // print_matrix(A);
    // print_matrix(B);
    
    auto start = std::chrono::high_resolution_clock::now();
    C = matmul_naive(A, B);
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 

    std::cout << "Time taken Naive(microseconds): " << duration.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    C = matmul_naive_optimized(A, B);
    stop = std::chrono::high_resolution_clock::now();

    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 

    std::cout << "Time taken Naive Optimized(microseconds): " << duration.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    C = matmul_naive_optimized_threaded(A, B);
    stop = std::chrono::high_resolution_clock::now();

    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 

    std::cout << "Time taken Naive Optimized Threaded(microseconds): " << duration.count() << std::endl;

    // Print product
    // print_matrix(C);
}