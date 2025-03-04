#include "core.h"
#include "MatrixBase.h"

using namespace yuki;

void testMatrixPadBasic(i32 const& padValue = 6, i32 const& padding = 2) {
    i32 r = 2, c = 2;
    Matrix<int> matrix(2, 2);
    matrix.at(0, 0) = 1;
    matrix.at(0, 1) = 2;
    matrix.at(1, 0) = 3;
    matrix.at(1, 1) = 4;
    
    matrix.pad(padding, padValue);
    
    assert(matrix.rows() == r + 2 * padding);
    assert(matrix.cols() == c + 2 * padding);
    assert(matrix.at(r + padding - 1, c + padding - 1) == 4);

    for (u64 r = 0; r < matrix.rows(); ++r) {
        for (u64 c = 0; c < matrix.cols(); ++c) {
            if ((r < padding && c < padding) ||
                (r > matrix.rows() - padding - 1 && c > matrix.cols() - padding - 1) ||
                (r < padding && c > matrix.cols() - padding - 1) ||
                (r > matrix.rows() - padding - 1 && c < padding)) {
                assert(matrix.at(r, c) == padValue);
            }
        } 
    }
}

void testMatrixPadZero() {
    Matrix<double> matrix(3, 3);
    matrix.pad(0, 0);
    
    for (u64 r = 0; r < 3; ++r) {
        for (u64 c = 0; c < 3; ++c) {
            assert(matrix.at(r, c) == 0);
        }
    }
}

int main() {
    testMatrixPadBasic();
    testMatrixPadZero(); 
}