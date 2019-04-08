#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

template <typename T>
class Matrix;

template <typename T>
class MatrixIterator {
private:
    Matrix<T>& matr;
    size_t row, column;
public:
    MatrixIterator(Matrix<T>& m, size_t i, size_t j) : matr(m), row(i), column(j) {}

    bool operator == (MatrixIterator other) const {
        return row == other.row && column == other.column;
    }

    bool operator != (MatrixIterator other) const {
        return !(*this == other);
    }

    T& operator * () {
        return matr[row][column];
    }

    MatrixIterator& operator++ () {
        ++column;
        if (column == matr.size().second) {
            ++row;
            column = 0;
        }
        return *this;
    }

    MatrixIterator operator++ (int) {
        auto tmp = *this;
        ++*this;
        return tmp;
    }
};

template <typename T>
class MatrixIteratorConst {
private:
    const Matrix<T>& matr;
    size_t row, column;
public:
    MatrixIteratorConst(const Matrix<T>& m, size_t i, size_t j) : matr(m), row(i), column(j) {}

    bool operator == (MatrixIteratorConst other) const {
        return row == other.row && column == other.column;
    }

    bool operator != (MatrixIteratorConst other) const {
        return !(*this == other);
    }

    const T& operator * () const {
        return matr[row][column];
    }

    MatrixIteratorConst& operator++ () {
        ++column;
        if (column == matr.size().second) {
            ++row;
            column = 0;
        }
        return *this;
    }

    MatrixIteratorConst operator++ (int) {
        auto tmp = *this;
        ++*this;
        return tmp;
    }
};

template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> matrix;
public:
    Matrix(const std::vector<std::vector<T>>& m) : matrix(m) {}

    std::pair<size_t, size_t> size() const {
        return {matrix.size(), matrix[0].size()};
    }

    const std::vector<T>& operator[] (size_t i) const {
        return matrix[i];
    }

    std::vector<T>& operator[] (size_t i) {
        return matrix[i];
    }

    Matrix<T>& operator += (const Matrix& m2) {
        for (size_t i = 0; i != matrix.size(); ++i) {
            for (size_t j = 0; j != matrix[0].size(); ++j) {
                matrix[i][j] += m2[i][j];
            }
        }
        return *this;
    }

    Matrix<T> operator + (const Matrix<T>& m2) const {
        Matrix<T> tmp(matrix);
        tmp += m2;
        return tmp;
    }

    template <typename S>
    Matrix<T>& operator *= (const S& scalar) {
        for (size_t i = 0; i != matrix.size(); ++i) {
            for (size_t j = 0; j != matrix[0].size(); ++j) {
                matrix[i][j] *= scalar;
            }
        }
        return *this;
    }

    template <typename S>
    Matrix<T>& operator *= (const Matrix<S>& other) {
        assert(matrix[0].size() == other.size().first);
        size_t m = matrix.size(), n = matrix[0].size(), p = other.size().second;
        std::vector<std::vector<T>> res(m);
        for (size_t i = 0; i != m; ++i) {
            res[i].resize(p);
            for (size_t j = 0; j != p; ++j) {
                for (size_t k = 0; k != n; ++k) {
                    res[i][j] += matrix[i][k] * other[k][j];
                }
            }
        }
        matrix = move(res);
        return *this;
    }

    template <typename S>
    Matrix<T> operator * (const S& scalar) const {
        Matrix<T> tmp(matrix);
        tmp *= scalar;
        return tmp;
    }

    template <typename S>
    Matrix<T> operator * (const Matrix<S>& other) const {
        assert(matrix[0].size() == other.size().first);
        size_t m = matrix.size(), n = matrix[0].size(), p = other.size().second;
        std::vector<std::vector<T>> res(m);
        for (size_t i = 0; i != m; ++i) {
            res[i].resize(p);
            for (size_t j = 0; j != p; ++j) {
                for (size_t k = 0; k != n; ++k) {
                    res[i][j] += matrix[i][k] * other[k][j];
                }
            }
        }
        Matrix tmp(res);
        return tmp;
    }

    Matrix<T>& transpose() {  // transpose (changes the argument)
        size_t m = matrix.size();
        size_t n = matrix[0].size();
        std::vector<std::vector<T>> tmp(n);
        for (size_t i = 0; i < n; ++i) {
            tmp[i].resize(m);
            for (size_t j = 0; j < m; ++j) {
                tmp[i][j] = matrix[j][i];
            }
        }
        matrix = move(tmp);
        return *this;
    }

    Matrix<T> transposed() const {  // transpose (doesnt change the argument, returns new matrix)
        Matrix res(matrix);
        res.transpose();
        return res;
    }

    MatrixIterator<T> begin() {
        return {*this, 0, 0};
    }

    MatrixIteratorConst<T> begin() const {
        return {*this, 0, 0};
    }

    MatrixIterator<T> end() {
        return {*this, matrix.size(), 0};
    }

    MatrixIteratorConst<T> end() const {
        return {*this, matrix.size(), 0};
    }
};

template <typename T>
std::ostream& operator << (std::ostream& out, const Matrix<T>& m) {  // prints matrix
    for (size_t i = 0; i != m.size().first; ++i) {
        for (size_t j = 0; j != m.size().second; ++j) {
            if (j + 1 != m.size().second)
                out << m[i][j] << "\t";
            else
                out << m[i][j];
        }
        if (i + 1 != m.size().first)
            out << "\n";
    }
    return out;
}
