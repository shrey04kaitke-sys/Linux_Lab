#include <iostream>
#include <vector>
using namespace std;

struct Process { int id, at, bt, ft, tat, wt; bool done; };

int main() {
    vector<Process> p = {{1,0,5,0,0,0,false}, {2,1,3,0,0,0,false},
                         {3,2,8,0,0,0,false}, {4,3,6,0,0,0,false}};
    int n = p.size(), finished = 0, time = 0;

    while (finished < n) {
        // pick the arrived, unfinished process with the smallest burst
        int pick = -1;
        for (int i = 0; i < n; i++)
            if (!p[i].done && p[i].at <= time &&
                (pick == -1 || p[i].bt < p[pick].bt))
                pick = i;

        if (pick == -1) { time++; continue; }   // CPU idle, nobody has arrived

        time += p[pick].bt;                     // run it to completion
        p[pick].ft  = time;
        p[pick].tat = p[pick].ft - p[pick].at;
        p[pick].wt  = p[pick].tat - p[pick].bt;
        p[pick].done = true;
        finished++;
    }

    cout << "SJF Non-Preemptive\nPID  AT  BT  FT  TAT  WT\n";
    for (auto& x : p)
        cout << "P" << x.id << "   " << x.at << "   " << x.bt << "   " << x.ft
             << "   " << x.tat << "    " << x.wt << endl;
    return 0;
}
