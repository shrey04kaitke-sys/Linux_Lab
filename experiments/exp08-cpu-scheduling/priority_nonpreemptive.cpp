#include <iostream>
#include <vector>
using namespace std;

struct Process { int id, at, bt, pr, ft, tat, wt; bool done; };

int main() {
    vector<Process> p = {{1,0,5,2,0,0,0,false}, {2,1,3,1,0,0,0,false},
                         {3,2,8,3,0,0,0,false}, {4,3,6,4,0,0,0,false}};
    int n = p.size(), finished = 0, time = 0;

    while (finished < n) {
        // pick the arrived, unfinished process with the best (lowest) priority number
        int pick = -1;
        for (int i = 0; i < n; i++)
            if (!p[i].done && p[i].at <= time &&
                (pick == -1 || p[i].pr < p[pick].pr))
                pick = i;

        if (pick == -1) { time++; continue; }   // CPU idle

        time += p[pick].bt;                     // run it to completion
        p[pick].ft  = time;
        p[pick].tat = p[pick].ft - p[pick].at;
        p[pick].wt  = p[pick].tat - p[pick].bt;
        p[pick].done = true;
        finished++;
    }

    cout << "Priority Non-Preemptive\nPID  AT  BT  FT  TAT  WT\n";
    for (auto& x : p)
        cout << "P" << x.id << "   " << x.at << "   " << x.bt << "   " << x.ft
             << "   " << x.tat << "    " << x.wt << endl;
    return 0;
}
