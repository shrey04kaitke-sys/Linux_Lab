#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n = 5, m = 3;                       // 5 processes, 3 resource types
    vector<vector<int>> alloc = {{0,1,0}, {2,0,0}, {3,0,2}, {2,1,1}, {0,0,2}};
    vector<vector<int>> max   = {{7,5,3}, {3,2,2}, {9,0,2}, {2,2,2}, {4,3,3}};
    vector<int> avail = {3, 3, 2};

    // Need = Max - Allocation
    vector<vector<int>> need(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    cout << "Need matrix:\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < m; j++) cout << need[i][j] << " ";
        cout << endl;
    }

    // Safety algorithm
    vector<int> work = avail;
    vector<bool> finish(n, false);
    vector<int> safeSeq;

    while ((int)safeSeq.size() < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (finish[i]) continue;
            bool canRun = true;
            for (int j = 0; j < m; j++)
                if (need[i][j] > work[j]) { canRun = false; break; }

            if (canRun) {
                // process i can finish, so it gives back what it holds
                for (int j = 0; j < m; j++) work[j] += alloc[i][j];
                finish[i] = true;
                safeSeq.push_back(i);
                found = true;
            }
        }
        if (!found) break;                  // no process can run: unsafe
    }

    if ((int)safeSeq.size() == n) {
        cout << "\nSYSTEM IS IN A SAFE STATE\nSafe sequence: ";
        for (int i = 0; i < n; i++)
            cout << "P" << safeSeq[i] << (i < n - 1 ? " -> " : "\n");
    } else {
        cout << "\nSYSTEM IS NOT IN A SAFE STATE (deadlock possible)\n";
    }
    return 0;
}
