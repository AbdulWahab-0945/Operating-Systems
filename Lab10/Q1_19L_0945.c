#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int laps_completed = 0;
int laps_requested;
int lap_time;
int stopwatch_active = 1;

void print_total_time() {
    printf("\nStopwatch stopped.\nTotal time: %d seconds\n", laps_completed * lap_time);
    exit(0);
}

void handle_child_death() {
    printf("\nLap %d completed.\n", laps_completed + 1);
    laps_completed++;
    if (laps_completed >= laps_requested) {
        stopwatch_active = 0;
    } else {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        }
        if (pid == 0) {
            sleep(lap_time);
            exit(0);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <Enter number of laps> <enter time of laps in seconds.>\n", argv[0]);
        exit(1);
    }
    laps_requested = atoi(argv[1]);
    lap_time = atoi(argv[2]);

    struct sigaction sa;
    sa.sa_handler = handle_child_death;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) { // child
        sleep(lap_time);
        exit(0);
    }

    while (stopwatch_active) {
        pause();
    }

    print_total_time();
}

