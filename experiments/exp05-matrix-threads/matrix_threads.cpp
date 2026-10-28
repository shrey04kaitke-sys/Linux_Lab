#include <iostream>
#include <vector>
#include <pthread.h>      // thread functions: pthread_create, pthread_join
using namespace std;

const int N = 3;                       // 3x3 matrices
vector<vector<int>> A, B, C;           // A x B = C

struct RowRange {                      // which rows one thread should do
    int start, end;
};

// Each thread runs this function
void* multiplyRows(void* arg) {
    RowRange* r = (RowRange*)arg;
    for (int i = r->start; i < r->end; i++)
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    return nullptr;
}

int main() {
    A = {{1,2,3}, {4,5,6}, {7,8,9}};
    B = {{9,8,7}, {6,5,4}, {3,2,1}};
    C.assign(N, vector<int>(N, 0));

    pthread_t threads[N];
    RowRange ranges[N];

    // Create one thread per row
    for (int t = 0; t < N; t++) {
        ranges[t] = {t, t + 1};
        pthread_create(&threads[t], nullptr, multiplyRows, &ranges[t]);
    }

    // Wait for all threads to finish
    for (int t = 0; t < N; t++)
        pthread_join(threads[t], nullptr);

    cout << "Result matrix C:" << endl;
    for (auto& row : C) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }
    return 0;
}
