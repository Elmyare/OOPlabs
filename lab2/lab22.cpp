#include <iostream>
#include <time.h>
using namespace std;

int fill_random(int **matrix);
int print_matrix(int **matrix);

int main(){
    srand(time(0));
    int rows, coll, i = 0;
    
    rows = 1 + rand() % 10;

    int **mat = new int*[rows+1];
    mat[0] = new int[1];
    mat[0][0] = rows;
    for (int i = 1; i <= rows; i++) {
        coll = 1 + rand() % 10;
        mat[i] = new int[coll+1];
        mat[i][0] = coll;
    }
    cout << rows << endl;
    
    //
    fill_random(mat);
    print_matrix(mat);
    //

    for(i = 0; i <= rows; i++){
         delete[] mat[i];
    }
    delete[] mat;
    
    return 0;
}

int fill_random(int **matrix) {
    int rows = matrix[0][0];
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= matrix[i][0]; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
    return 0;
}

int print_matrix(int **matrix) {
    int rows = matrix[0][0];
    for (int i = 1; i <= rows; i++) {
        cout << matrix[i][0] << ": ";
        for (int j = 1; j <= matrix[i][0]; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

