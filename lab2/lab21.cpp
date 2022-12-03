#include <iostream>
#include <time.h>
using namespace std;

#define N 6

int fill_random(int **mat);
int print_matrix(int **mat);
int get_right_diagonals(int **mat, int *arr);
int get_left_diagonals(int **mat, int *arr);
int print_arr(int *arr);
int get_spiral_corner(int **mat, int *arr);
int get_spiral_center(int **mat, int *arr);

int main() {
    int **matrix = new int*[N];
    int arr[N*N];

    for (int i = 0; i < N*N; i++) arr[i] = 0; // fill zero

    for (int i = 0; i < N; i++) {
        matrix[i] = new int[N];
    }
    //
    fill_random(matrix);
    print_matrix(matrix);
    cout << endl << "a) ";
    get_right_diagonals(matrix, arr);
    print_arr(arr);
    cout << "b) ";
    get_left_diagonals(matrix, arr);
    print_arr(arr);
    cout << "c) ";
    get_spiral_center(matrix, arr);
    print_arr(arr);
    cout << "d) ";
    get_spiral_corner(matrix, arr);
    print_arr(arr);
    //
    for (int i = 0; i < N; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int fill_random(int **mat) {
    for (int i = 0; i < N*N; i++) {
        mat[i/N][i%N] = rand() % 10;
    }
    return 0;
}

int print_matrix(int **mat) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

int get_right_diagonals(int **mat, int *arr) {
    int i;
    int j;
    //int j = N-1;
    int place = 0;
    for (j = N-1; j >= 0; j--) {
        i = 0;
        for (int w = j; w < N; w++) {
            arr[place] = mat[i][w];
            //cout << mat[i][w] << " ";
            i++;
            place++;
        }
        //cout << endl;
    }
    for (i = 1; i < N; i++) {
        j = 0;
        for (int w = i; w < N; w++) {
            arr[place] = mat[w][j];
            //cout << mat[w][j] << " ";
            j++;
            place++;
        }
        //cout << endl;
    }
    return 0;
}

int get_left_diagonals(int **mat, int *arr) {
    int i;
    int j;
    //int j = N-1;
    int place = 0;
    for (j = 0; j < N; j++) {
        i = 0;
        for (int w = j; w >= 0; w--) {
            arr[place] = mat[i][w];
            //cout << mat[i][w] << " ";
            i++;
            place++;
        }
        //cout << endl;
    }
    for (i = 1; i < N; i++) {
        j = N-1;
        for (int w = i; w < N; w++) {
            arr[place] = mat[w][j];
            //cout << mat[w][j] << " ";
            j--;
            place++;
        }
        //cout << endl;
    }
    return 0;
}

int print_arr(int *arr) {
    for (int i = 0; i < N*N; i++) cout << arr[i] << " ";
    cout << endl;
    return 0;
}

int get_spiral_center(int **mat, int *arr) {
    int t_arr[N*N];
    get_spiral_corner(mat, t_arr);
    for (int i = 0; i < N*N; i++) {
        arr[i] = t_arr[N*N-i-1];
    }
    return 0;
}

int get_spiral_corner(int **mat, int *arr) {
    int i = 0;
    int j = 0;
    for(int k = 0; k < N*N; k++) {
        arr[k] = mat[i][j];
        if (i <= j + 1 && i + j < N - 1)
            ++j;
        else if (i < j && i + j >= N - 1)
            ++i;
        else if (i >= j && i + j > N - 1)
            --j;
        else 
            --i;
    }
    return 0;
}