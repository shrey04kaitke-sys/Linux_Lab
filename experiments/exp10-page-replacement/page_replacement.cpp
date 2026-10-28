#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int FRAMES = 3;

// FIFO: evict the page that entered memory first
int fifo(const vector<int>& ref) {
    vector<int> frames;
    int faults = 0;
    for (int page : ref) {
        if (find(frames.begin(), frames.end(), page) != frames.end()) continue; // hit
        faults++;
        if ((int)frames.size() < FRAMES) frames.push_back(page);
        else { frames.erase(frames.begin()); frames.push_back(page); }
    }
    return faults;
}

// LRU: frames are kept ordered from least to most recently used
int lru(const vector<int>& ref) {
    vector<int> frames;
    int faults = 0;
    for (int page : ref) {
        auto it = find(frames.begin(), frames.end(), page);
        if (it != frames.end()) {            // hit: mark as most recently used
            frames.erase(it);
            frames.push_back(page);
            continue;
        }
        faults++;
        if ((int)frames.size() == FRAMES) frames.erase(frames.begin()); // evict least recent
        frames.push_back(page);
    }
    return faults;
}

// Optimal: evict the page whose next use is farthest in the future (or never)
int optimal(const vector<int>& ref) {
    vector<int> frames;
    int faults = 0, n = ref.size();
    for (int i = 0; i < n; i++) {
        int page = ref[i];
        if (find(frames.begin(), frames.end(), page) != frames.end()) continue; // hit
        faults++;
        if ((int)frames.size() < FRAMES) { frames.push_back(page); continue; }

        int victim = 0, farthest = -1;
        for (int k = 0; k < FRAMES; k++) {
            int nextUse = n;                 // n means "never used again"
            for (int j = i + 1; j < n; j++)
                if (ref[j] == frames[k]) { nextUse = j; break; }
            if (nextUse > farthest) { farthest = nextUse; victim = k; }
        }
        frames[victim] = page;
    }
    return faults;
}

int main() {
    vector<int> ref = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    cout << "Reference string: ";
    for (int p : ref) cout << p << " ";
    cout << "\nFrames: " << FRAMES << "\n\n";
    cout << "FIFO page faults:    " << fifo(ref) << endl;
    cout << "LRU page faults:     " << lru(ref) << endl;
    cout << "Optimal page faults: " << optimal(ref) << endl;
    return 0;
}
