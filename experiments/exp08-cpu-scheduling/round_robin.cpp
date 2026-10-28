#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    // id, arrival, burst
    vector<int> id = {1, 2, 3, 4};
    vector<int> at = {0, 1, 2, 3};
    vector<int> bt = {5, 3, 8, 6};
    int n = id.size();
    int quantum = 2;

    vector<int> rem = bt, ft(n), tat(n), wt(n);
    vector<bool> inQueue(n, false);
    queue<int> q;
    int time = 0, finished = 0;

    // add processes that have arrived at time 0
    for (int i = 0; i < n; i++)
        if (at[i] <= time) { q.push(i); inQueue[i] = true; }

    while (finished < n) {
        if (q.empty()) {                       // CPU idle, wait for next arrival
            time++;
            for (int i = 0; i < n; i++)
                if (!inQueue[i] && rem[i] > 0 && at[i] <= time) {
                    q.push(i); inQueue[i] = true;
                }
            continue;
        }

        int cur = q.front(); q.pop();
        int run = min(quantum, rem[cur]);      // run up to one quantum

        // during this slice, add newly arrived processes to the queue
        for (int t = 0; t < run; t++) {
            time++;
            for (int i = 0; i < n; i++)
                if (!inQueue[i] && rem[i] > 0 && at[i] <= time && i != cur) {
                    q.push(i); inQueue[i] = true;
                }
        }

        rem[cur] -= run;
        if (rem[cur] == 0) {                   // finished
            ft[cur]  = time;
            tat[cur] = ft[cur] - at[cur];
            wt[cur]  = tat[cur] - bt[cur];
            finished++;
        } else {
            q.push(cur);                       // not done, back of the queue
        }
    }

    cout << "Round Robin (quantum = " << quantum << ")\nPID  AT  BT  FT  TAT  WT\n";
    for (int i = 0; i < n; i++)
        cout << "P" << id[i] << "   " << at[i] << "   " << bt[i] << "   "
             << ft[i] << "   " << tat[i] << "    " << wt[i] << endl;
    return 0;
}
