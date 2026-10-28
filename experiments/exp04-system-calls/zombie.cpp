#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        cout << "Child (PID " << getpid() << ") exiting now" << endl;
        exit(0);
    } else {
        cout << "Parent (PID " << getpid() << ") sleeping 20 seconds."
             << " Child " << pid << " is a ZOMBIE until I call wait()." << endl;
        sleep(20);
        wait(nullptr);                  // cleans up the zombie
        cout << "Parent: zombie removed" << endl;
    }
    return 0;
}
