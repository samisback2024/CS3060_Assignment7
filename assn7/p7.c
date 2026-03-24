#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void copy_requests(const int data[], int count, int req[]) {
    for (int i = 1; i < count; i++) {
        req[i - 1] = data[i];
    }
}

void sort_array(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int first_ge(const int arr[], int n, int value) {
    for (int i = 0; i < n; i++) {
        if (arr[i] >= value) {
            return i;
        }
    }
    return n;
}

int fcfs(const int data[], int count) {
    int total = 0;
    int current = data[0];

    for (int i = 1; i < count; i++) {
        total += abs(current - data[i]);
        current = data[i];
    }

    return total;
}

int sstf(const int data[], int count) {
    int total = 0;
    int current = data[0];
    int used[MAX_REQUESTS] = {0};
    int remaining = count - 1;

    while (remaining > 0) {
        int best_index = -1;
        int best_dist = 0;

        for (int i = 1; i < count; i++) {
            if (!used[i]) {
                int dist = abs(current - data[i]);
                if (best_index == -1 || dist < best_dist) {
                    best_index = i;
                    best_dist = dist;
                }
            }
        }

        total += best_dist;
        current = data[best_index];
        used[best_index] = 1;
        remaining--;
    }

    return total;
}

int look(const int data[], int count) {
    int req[MAX_REQUESTS];
    int n = count - 1;
    int total = 0;
    int current = data[0];

    copy_requests(data, count, req);
    sort_array(req, n);

    int split = first_ge(req, n, current);

    for (int i = split; i < n; i++) {
        total += abs(current - req[i]);
        current = req[i];
    }

    for (int i = split - 1; i >= 0; i--) {
        total += abs(current - req[i]);
        current = req[i];
    }

    return total;
}

int clook(const int data[], int count) {
    int req[MAX_REQUESTS];
    int n = count - 1;
    int total = 0;
    int current = data[0];

    copy_requests(data, count, req);
    sort_array(req, n);

    int split = first_ge(req, n, current);

    for (int i = split; i < n; i++) {
        total += abs(current - req[i]);
        current = req[i];
    }

    if (split > 0) {
        total += abs(current - req[0]);
        current = req[0];

        for (int i = 1; i < split; i++) {
            total += abs(current - req[i]);
            current = req[i];
        }
    }

    return total;
}

int main(void) {
    int data[MAX_REQUESTS];
    int count = 0;

    while (count < MAX_REQUESTS && scanf("%d", &data[count]) == 1) {
        count++;
    }

    if (count < 2) {
        fprintf(stderr, "Error: need at least a starting block and one request.\n");
        return 1;
    }

    printf("Assignment 7: Block Access Algorithm\n");
    printf("By: Sam\n\n");

    printf("FCFS Total Seek: %d\n", fcfs(data, count));
    printf("SSTF Total Seek: %d\n", sstf(data, count));
    printf("LOOK Total Seek: %d\n", look(data, count));
    printf("C-LOOK Total Seek: %d\n", clook(data, count));

    return 0;
}