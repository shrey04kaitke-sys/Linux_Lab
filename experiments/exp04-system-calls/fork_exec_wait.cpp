#include <iostream>
#include <unistd.h>      // fork, getpid, getppid, execvp
#include <sys/wait.h>    // waitpid, WIFEXITED, WEXITSTATUS
#include <cstdlib>       // exit
using namespace std;

int main() {
    cout << "Parent started. PID = " << getpid() << endl;

    pid_t pid = fork();                 // makes a copy of this process
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // This code runs in the CHILD
        cout << "Child: PID = " << getpid()
             << ", parent PID = " << getppid() << endl;

        char *args[] = {(char *)"ls", (char *)"-l", nullptr};
        execvp("ls", args);             // replaces child with the ls program
        perror("execvp failed");        // only runs if execvp fails
        exit(1);
    } else {
        // This code runs in the PARENT
        int status = 0;
        pid_t done = waitpid(pid, &status, 0);   // wait for the child to finish
        cout << "Parent: child " << done << " finished" << endl;
        if (WIFEXITED(status))
            cout << "Child exit status: " << WEXITSTATUS(status) << endl;
    }
    return 0;
}
