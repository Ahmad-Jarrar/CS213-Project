#include <chrono>

#include "../common.hpp"

using namespace boost::numeric::ublas;

// add two matrices
void add(matrix<int> &matrixA, 
         matrix<int> &matrixB, 
         matrix<int> &matrixC, unsigned int mSize) {
    for (int i = 0; i < mSize; i++) {
        for (int j = 0; j < mSize; j++) {
            matrixC(i,j) = matrixA(i,j) + matrixB(i,j);
        }
    }
}

// subtract two matrices
void sub(matrix<int> &matrixA, 
        matrix<int> &matrixB, 
        matrix<int> &matrixC, unsigned int mSize) {
    for (int i = 0; i < mSize; i++) {
        for (int j = 0; j < mSize; j++) {
            matrixC(i,j) = matrixA(i,j) - matrixB(i,j);
        }
    }   
}
// recursive strassen matrix multiplier
void strassenR(matrix<int> &matrixA,
            matrix<int> &matrixB,
            matrix<int> &matrixC,
            unsigned int mSize) {

    // recursive base case
    if (mSize == 1) {
        matrixC(0,0) = matrixA(0,0) * matrixB(0,0);
        return;
    }
    else {
        int newMSize = mSize / 2;
        

        // initialize matrices
        matrix<int> matrixA11(newMSize, newMSize),
                            matrixA12(newMSize, newMSize),
                            matrixA21(newMSize, newMSize),
                            matrixA22(newMSize, newMSize),
                            matrixB11(newMSize, newMSize),
                            matrixB12(newMSize, newMSize),
                            matrixB21(newMSize, newMSize),
                            matrixB22(newMSize, newMSize),
                            matrixC11(newMSize, newMSize),
                            matrixC12(newMSize, newMSize),
                            matrixC21(newMSize, newMSize),
                            matrixC22(newMSize, newMSize),
                            s1(newMSize, newMSize),
                            s2(newMSize, newMSize),
                            s3(newMSize, newMSize),
                            s4(newMSize, newMSize),
                            s5(newMSize, newMSize),
                            s6(newMSize, newMSize),
                            s7(newMSize, newMSize),
                            s8(newMSize, newMSize),
                            s9(newMSize, newMSize),
                            s10(newMSize, newMSize),
                            p1(newMSize, newMSize),
                            p2(newMSize, newMSize),
                            p3(newMSize, newMSize),
                            p4(newMSize, newMSize),
                            p5(newMSize, newMSize),
                            p6(newMSize, newMSize),
                            p7(newMSize, newMSize),
                            tempMatrixA(newMSize, newMSize),
                            tempMatrixB(newMSize, newMSize);

        // divide matrices into 4 submatrices
        for (int i = 0; i < newMSize; i++) {
            for (int j = 0; j < newMSize; j++) {
                matrixA11(i,j) = matrixA(i,j);
                matrixA12(i,j) = matrixA(i,j + newMSize);
                matrixA21(i,j) = matrixA(i + newMSize,j);
                matrixA22(i,j) = matrixA(i + newMSize,j + newMSize);

                matrixB11(i,j) = matrixB(i,j);
                matrixB12(i,j) = matrixB(i,j + newMSize);
                matrixB21(i,j) = matrixB(i + newMSize,j);
                matrixB22(i,j) = matrixB(i + newMSize,j + newMSize);
            }
        }

        // s1 = b12 - b22
        sub(matrixB12, matrixB22, s1, newMSize);
        
        // s2 = a11 + a12
        add(matrixA11, matrixA12, s2, newMSize);

        // s3 = a21 + a22
        add(matrixA21, matrixA22, s3, newMSize);

        // s4 = b21 - b11
        sub(matrixB21, matrixB11, s4, newMSize);
        
        // s5 = a11 + a22
        add(matrixA11, matrixA22, s5, newMSize);
        
        // s6 = b11 + b22
        add(matrixB11, matrixB22, s6, newMSize);

        // s7 = a12 - a22
        sub(matrixA12, matrixA22, s7, newMSize);

        // s8 = b21 + b22
        add(matrixB21, matrixB22, s8, newMSize);

        // s9 = a11 - a21
        sub(matrixA11, matrixA21, s9, newMSize);

        // s10 = b11 + b12
        add(matrixB11, matrixB12, s10, newMSize);

        // p1 = a11 * s1
        strassenR(matrixA11, s1, p1, newMSize);

        // p2 = s2 * b22
        strassenR(s2, matrixB22, p2, newMSize);

        // p3 = s3 * b11
        strassenR(s3, matrixB11, p3, newMSize);

        // p4 = a22 * s4
        strassenR(matrixA22, s4, p4, newMSize);

        // p5 = s5 * s6
        strassenR(s5, s6, p5, newMSize); 

        // p6 = s7 * s8
        strassenR(s7, s8, p6, newMSize);

        // p7 = s9 * s10
        strassenR(s9, s10, p7, newMSize);

        // c11 = p5 + p4 - p2 + p6
        add(p5, p4, tempMatrixA, newMSize); // p5 + p4
        add(tempMatrixA, p6, tempMatrixB, newMSize); // (p5 + p4) + p6
        sub(tempMatrixB, p2, matrixC11, newMSize); // (p5 + p4 + p6) - p2

        // c12 = p1 + p2
        add(p1, p2, matrixC12, newMSize);

        // c21 = p3 + p4
        add(p3, p4, matrixC21, newMSize);

        // c22 = p5 + p1 - p3 + p7
        add(p5, p1, tempMatrixA, newMSize); // p5 + p1
        sub(tempMatrixA, p3, tempMatrixB, newMSize); // (p5 + p1) - p3
        sub(tempMatrixB, p7, matrixC22, newMSize); // (p5 + p1 - p3) - p7

        // group into matrixC
        for (int i = 0; i < newMSize ; i++) {
            for (int j = 0 ; j < newMSize ; j++) {
                matrixC(i,j) = matrixC11(i,j);
                matrixC(i,j + newMSize) = matrixC12(i,j);
                matrixC(i + newMSize,j) = matrixC21(i,j);
                matrixC(i + newMSize,j + newMSize) = matrixC22(i,j);
            }
        }
    }
}

// call recursive function
void strassen(matrix<int> &matrixA, 
              matrix<int> &matrixB, 
              matrix<int> &matrixC,
              unsigned int mSize) {
    strassenR(matrixA, matrixB, matrixC, mSize);
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
    initialize_matrix(&A, true, 10);
    initialize_matrix(&B, true, 10);
    // print_matrix(A);
    // print_matrix(B);

    auto start = std::chrono::high_resolution_clock::now();
    strassen(A, B, C, A.size1());
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 

    std::cout << "Time taken(microseconds): " << duration.count() << std::endl;

    // Print product
    // print_matrix(C);
}