#include <iostream>
#include <vector>
using namespace std;

int main() {
    // id, arrival, burst, priority (lower = higher)
    vector<int> id = {1, 2, 3, 4};
    vector<int> at = {0, 1, 2, 3};
    vector<int> bt = {5, 3, 8, 6};
    vector<int> pr = {2, 1, 3, 4};
    int n = id.size();

    vector<int> rem = bt, ft(n), tat(n), wt(n);
    int time = 0, finished = 0;

    while (finished < n) {
        // pick the arrived, unfinished process with the best priority
        int pick = -1;
        for (int i = 0; i < n; i++)
            if (rem[i] > 0 && at[i] <= time &&
                (pick == -1 || pr[i] < pr[pick]))
                pick = i;

        if (pick == -1) { time++; continue; }   // CPU idle

        rem[pick]--;                            // run for one time unit
        time++;

        if (rem[pick] == 0) {                   // process just finished
            ft[pick]  = time;
            tat[pick] = ft[pick] - at[pick];
            wt[pick]  = tat[pick] - bt[pick];
            finished++;
        }
    }

    cout << "Priority Preemptive\nPID  AT  BT  FT  TAT  WT\n";
    for (int i = 0; i < n; i++)
        cout << "P" << id[i] << "   " << at[i] << "   " << bt[i] << "   "
             << ft[i] << "   " << tat[i] << "    " << wt[i] << endl;
    return 0;
}
