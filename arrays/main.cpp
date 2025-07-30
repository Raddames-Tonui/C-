#include <iostream>
using namespace std;


// Function that takes array as argument
void arrayAsArgument(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}

void testArrayAsArgument() {
    // int* arr2 = new int[10]();
    // char* character = new char[9]();


    int arr[] = {2,1,4,1,423,2};
    int n = sizeof(arr) / sizeof(arr[0]);

    arrayAsArgument(arr, n);
}


/**------MULTI DIMENSIONAL ARRAYS --------*/

/** ------2D Array-------
 * The size in bytes can be calculated by multiplying the number of elements by size of each element or we can just use sizeof operator.
 * int arr[2][4] = {{0, 1, 2, 3}, {4, 5, 6, 7}};
 */
void twomultiDimensionalArray() {
    // declaring and initializing a 2D array
    // with 3 rows and 2 columns
    int arr[3][2] = {   {11,2},
                        {37,48},
                        {4,2}
                    };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++ ) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    // with 3 rows and 4 columns
    int matrix[3][4] = {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12}
    };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nSize of array: "<<sizeof(matrix)<< " bytes" << endl;

    cout <<matrix[2][4] << endl;
}

void passing2DArray(int* arr, int x, int y) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            cout << *(arr + i *y + j) << " ";
        }
        cout << endl;
    }
}
void testPassing2DArray() {
    int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
    passing2DArray(&arr[0][0], 2, 3); // passing a pointer to the first element
}
/** ------  3D Array ------------
 *  depth, row, and column
* int arr[2][2][3] = {
    {{0, 1, 2}, {3, 4, 5}},
    {{6, 7, 8}, {9, 10, 11}}
};
 */

void threeMultiDimensionalArray() {
    int arr[2][2][3] = {
        {{0, 1, 2}, {3, 4, 5}},
        {{6, 7, 8}, {9, 10, 11}}
    };

    // Accessing elements
    // cout << arr[0][1][3] << endl;
    // cout << arr[1][2][1] << endl;

    // Traverse 3D Array
    for (int i =0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 3; k++) {
                cout << arr[i][j][k] << " ";
            }
            cout << endl;
        }
    }
    // cout << "\nSize of array: "<<sizeof(arr)<< " bytes" << endl;
}


void passing3DArray(int* arr, int x, int y, int z) {
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            for (int k = 0; k < z; k++)
                cout << arr[i * y * z + j * z + k] << " ";
}

void testPassing3DArray() {
    int arr[2][3][4] = {
        {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}},
        {{13, 14, 15, 16}, {17, 18, 19, 20}, {21, 22, 23, 24}}
    };

    passing3DArray(&arr[0][0][0], 2, 3, 4);
}

int main() {
    // testArrayAsArgument();
    // twomultiDimensionalArray();
    // threeMultiDimensionalArray();

    testPassing2DArray();
    // testPassing3DArray();
    return 0;
}