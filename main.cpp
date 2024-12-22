#include <iostream>
#include <csignal>
#include <sys/wait.h>
#include "FuncA.h"         // Include FuncA header for calculations
#include "HTTP_Server.h"   // Include the HTTP server header

int CreateHTTPserver();

void sigchldHandler(int s) {
    std::cout << "Caught signal SIGCHLD\n";

    pid_t pid;
    int status;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status)) {
            std::cout << "\nChild process terminated\n";
        }
    }
}

void sigintHandler(int s) {
    std::cout << "Caught signal " << s << ". Starting graceful exit procedure\n";

    pid_t pid;
    int status;
    while ((pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            std::cout << "\nChild process terminated\n";
        }
    }

    if (pid == -1) {
        std::cout << "\nAll child processes terminated\n";
    }

    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {
    // Set up signal handlers
    signal(SIGCHLD, sigchldHandler);
    signal(SIGINT, sigintHandler);

    FuncA calc;
    double x = 1.0;
    int n = 10;
    std::cout << "FuncA result: " << calc.calculate(x, n) << std::endl;

    CreateHTTPserver();

    return 0;
}
