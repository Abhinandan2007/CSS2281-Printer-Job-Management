#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_JOBS 100
#define NAME_LEN 80

typedef struct {
    int id;
    char document[NAME_LEN];
    char user[NAME_LEN];
    int pages;
} PrintJob;

typedef struct {
    PrintJob jobs[MAX_JOBS];
    int front;
    int count;
} PrintQueue;

static PrintJob completed[MAX_JOBS];
static int completedCount = 0;
static int nextJobID = 101;

int readInt(const char *prompt, int min, int max) {
    char line[100], extra;
    int value;

    while (1) {
        printf("%s", prompt);
        if (!fgets(line, sizeof(line), stdin)) {
            printf("\nInput ended.\n");
            exit(0);
        }
        if (sscanf(line, " %d %c", &value, &extra) == 1 &&
            value >= min && value <= max) {
            return value;
        }
        printf("Invalid input. Enter a number from %d to %d.\n", min, max);
    }
}

void readText(const char *prompt, char *dest, size_t size) {
    char line[256];
    size_t len;

    while (1) {
        printf("%s", prompt);
        if (!fgets(line, sizeof(line), stdin)) {
            printf("\nInput ended.\n");
            exit(0);
        }

        len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[--len] = '\0';
        } else {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
        }

        char *start = line;
        while (isspace((unsigned char)*start)) start++;

        len = strlen(start);
        while (len > 0 && isspace((unsigned char)start[len - 1])) {
            start[--len] = '\0';
        }

        if (len == 0) {
            printf("Input cannot be empty. Try again.\n");
            continue;
        }
        if (len >= size) {
            printf("Text is too long. Maximum allowed: %zu characters.\n",
                   size - 1);
            continue;
        }
        strcpy(dest, start);
        return;
    }
}

void initializeQueue(PrintQueue *q) {
    q->front = 0;
    q->count = 0;
}

int isEmpty(const PrintQueue *q) { return q->count == 0; }
int isFull(const PrintQueue *q) { return q->count == MAX_JOBS; }

PrintJob *jobAt(PrintQueue *q, int position) {
    return &q->jobs[(q->front + position) % MAX_JOBS];
}

void enqueue(PrintQueue *q, PrintJob job) {
    int rear = (q->front + q->count) % MAX_JOBS;
    q->jobs[rear] = job;
    q->count++;
}

PrintJob dequeue(PrintQueue *q) {
    PrintJob job = q->jobs[q->front];
    q->front = (q->front + 1) % MAX_JOBS;
    q->count--;
    return job;
}

void displayJob(PrintJob job) {
    printf("%-6d %-24s %-20s %5d\n",
           job.id, job.document, job.user, job.pages);
}

void addJob(PrintQueue *q) {
    PrintJob job;
    if (isFull(q)) {
        printf("\nQueue is full. Cannot add more jobs.\n");
        return;
    }

    job.id = nextJobID++;
    readText("Enter document name: ", job.document, sizeof(job.document));
    readText("Enter user name: ", job.user, sizeof(job.user));
    job.pages = readInt("Enter number of pages (1-10000): ", 1, 10000);
    enqueue(q, job);

    printf("\nJob submitted successfully!\nYour Job ID is: %d\n", job.id);
}

void displayQueue(PrintQueue *q) {
    if (isEmpty(q)) {
        printf("\nNo pending print jobs.\n");
        return;
    }

    printf("\n========== PENDING PRINT JOBS ==========\n");
    printf("%-6s %-24s %-20s %5s\n", "ID", "Document", "User", "Pages");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < q->count; i++) displayJob(*jobAt(q, i));
    printf("\nTotal pending jobs: %d\n", q->count);
}

void processNextJob(PrintQueue *q) {
    if (isEmpty(q)) {
        printf("\nNo jobs available to print.\n");
        return;
    }

    PrintJob job = dequeue(q);
    printf("\nPrinting job...\nJob ID       : %d\nDocument     : %s\n"
           "Submitted by : %s\nPages        : %d\n"
           "Status       : Completed successfully (simulation)\n",
           job.id, job.document, job.user, job.pages);

    if (completedCount < MAX_JOBS) {
        completed[completedCount++] = job;
    } else {
        printf("Warning: History is full; this job was not saved in history.\n");
    }
}

void cancelJob(PrintQueue *q) {
    int id = readInt("Enter Job ID to cancel: ", 1, 1000000000);
    PrintJob temp[MAX_JOBS];
    int newCount = 0, found = 0;

    for (int i = 0; i < q->count; i++) {
        PrintJob job = *jobAt(q, i);
        if (job.id == id) found = 1;
        else temp[newCount++] = job;
    }

    if (!found) {
        printf("\nJob ID %d was not found in the pending queue.\n", id);
        return;
    }

    q->front = 0;
    q->count = newCount;
    for (int i = 0; i < newCount; i++) q->jobs[i] = temp[i];
    printf("\nJob ID %d cancelled successfully.\n", id);
}

void searchJob(PrintQueue *q) {
    int id = readInt("Enter Job ID to search: ", 1, 1000000000);

    for (int i = 0; i < q->count; i++) {
        PrintJob job = *jobAt(q, i);
        if (job.id == id) {
            printf("\nJob found in pending queue:\n");
            printf("%-6s %-24s %-20s %5s\n", "ID", "Document", "User", "Pages");
            displayJob(job);
            return;
        }
    }

    for (int i = 0; i < completedCount; i++) {
        if (completed[i].id == id) {
            printf("\nJob found in completed history:\n");
            printf("%-6s %-24s %-20s %5s\n", "ID", "Document", "User", "Pages");
            displayJob(completed[i]);
            printf("Status: Completed\n");
            return;
        }
    }
    printf("\nJob ID %d was not found.\n", id);
}

void showNextJob(PrintQueue *q) {
    if (isEmpty(q)) {
        printf("\nNo next job. The queue is empty.\n");
        return;
    }
    printf("\nNext job to print:\n");
    printf("%-6s %-24s %-20s %5s\n", "ID", "Document", "User", "Pages");
    displayJob(*jobAt(q, 0));
}

void showPendingPages(PrintQueue *q) {
    long total = 0;
    for (int i = 0; i < q->count; i++) total += jobAt(q, i)->pages;
    printf("\nPending jobs: %d\nTotal pending pages: %ld\n", q->count, total);
}

void showHistory(void) {
    if (completedCount == 0) {
        printf("\nNo completed jobs yet.\n");
        return;
    }

    printf("\n========== COMPLETED JOB HISTORY ==========\n");
    printf("%-6s %-24s %-20s %5s\n", "ID", "Document", "User", "Pages");
    for (int i = 0; i < completedCount; i++) displayJob(completed[i]);
    printf("\nCompleted jobs stored: %d\n", completedCount);
}

int main(void) {
    PrintQueue queue;
    int choice;
    initializeQueue(&queue);

    printf("============================================\n");
    printf("     PRINTER JOB MANAGEMENT SYSTEM\n");
    printf("       CSS2281 - Data Structures\n");
    printf("============================================\n");

    do {
        printf("\n--------------- MAIN MENU ----------------\n");
        printf("1. Add a print job\n");
        printf("2. Display pending jobs\n");
        printf("3. Process next print job\n");
        printf("4. Cancel a pending job\n");
        printf("5. Search for a job\n");
        printf("6. Display next job\n");
        printf("7. Show total pending pages\n");
        printf("8. View completed job history\n");
        printf("0. Exit\n");
        printf("------------------------------------------\n");

        choice = readInt("Enter your choice: ", 0, 8);
        switch (choice) {
            case 1: addJob(&queue); break;
            case 2: displayQueue(&queue); break;
            case 3: processNextJob(&queue); break;
            case 4: cancelJob(&queue); break;
            case 5: searchJob(&queue); break;
            case 6: showNextJob(&queue); break;
            case 7: showPendingPages(&queue); break;
            case 8: showHistory(); break;
            case 0: printf("\nThank you for using the system.\n"); break;
        }
    } while (choice != 0);

    return 0;
}
