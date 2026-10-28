#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        sleep(5);                       // give the parent time to exit
        cout << "Child: my parent PID is now " << getppid()
             << " (the original parent " << "has exited, so I am an ORPHAN)" << endl;
    } else {
        cout << "Parent (PID " << getpid() << ") exiting. Child "
             << pid << " becomes an orphan." << endl;
    }
    return 0;
}
