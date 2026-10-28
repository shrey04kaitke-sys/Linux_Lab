#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process { int id, at, bt, ft, tat, wt; };

int main() {
    vector<Process> p = {{1,0,5,0,0,0}, {2,1,3,0,0,0}, {3,2,8,0,0,0}, {4,3,6,0,0,0}};

    // FCFS: run in order of arrival
    sort(p.begin(), p.end(), [](const Process& a, const Process& b){ return a.at < b.at; });

    int time = 0;
    for (auto& x : p) {
        if (time < x.at) time = x.at;   // CPU idle until the process arrives
        time += x.bt;
        x.ft = time;
        x.tat = x.ft - x.at;
        x.wt = x.tat - x.bt;
    }

    cout << "FCFS\nPID  AT  BT  FT  TAT  WT\n";
    for (auto& x : p)
        cout << "P" << x.id << "   " << x.at << "   " << x.bt << "   " << x.ft
             << "   " << x.tat << "    " << x.wt << endl;
    return 0;
}
