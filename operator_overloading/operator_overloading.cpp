
#include <iostream>
using namespace std;

class Matrix {
private:
    int rows, cols;
    double** data;

public:

    Matrix(int r, int c) : rows(r), cols(c) {
        data = new double*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new double[cols];
        }


        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = 0;
            }
        }
    }


    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = new double*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new double[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    ~Matrix(){
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }

    void display() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    // input values
    void fill() {
        cout << "Enter the elements for: "<< rows << " x "<< cols << " matrix: \n" << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cin >> data[i][j];
            }
        }
    }

    // cout << data[i][j]; ->  *(*(data + i) + j)

    // +
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            cout << "Error: Incompatible matrix sizes for addition.\n" << endl;
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // -
    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            cout << "Error: Incompatible matrix sizes for subtraction.\n" << endl;
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    // *
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            cout << "Error: Incompatible matrix sizes for multiplication.\n" << endl;
        }

        Matrix result(rows, other.cols);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }

        return result;
    }

    // >
   bool operator>(const Matrix& other) const {
        int thisSum = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                thisSum += data[i][j];
            }
        }

        int otherSum = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                otherSum += other.data[i][j];
            }
        }

        return thisSum > otherSum;
    }

    // <
    bool operator<(const Matrix& other)const {
        int thisSum = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                thisSum += data[i][j];
            }
        }

        int otherSum = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                otherSum += other.data[i][j];
            }
        }

        return thisSum < otherSum;
    }

};


int main() {
    Matrix A(2,2) , B(2,2);
    // A.fill();
    // B.fill();

    Matrix c = A*B;
    cout << "A * B = \n";
    c.display();

    // <  and   >
    Matrix D (2,6);

    if (D > A) {
        cout << "Greater than \n" << endl;
    } else if (D < A) {
        cout << "Less than \n"<< endl;
    }
    else {
        cout << "equal" << endl;
    }


}