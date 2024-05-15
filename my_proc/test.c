#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROC_FILENAME "/proc/my_proc"

#define BUFFER_SIZE 256

int main() {
    FILE *fp;
    char read_buffer[BUFFER_SIZE];
    char write_buffer[BUFFER_SIZE];

    // Write to /proc/my_proc
    printf("Enter message to write to /proc/my_proc: ");
    fgets(write_buffer, BUFFER_SIZE, stdin);

    fp = fopen(PROC_FILENAME, "w");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    if (fwrite(write_buffer, sizeof(char), strlen(write_buffer), fp) != strlen(write_buffer)) {
        perror("Error writing to file");
        exit(EXIT_FAILURE);
    }

    fclose(fp);

    // Read from /proc/my_proc
    fp = fopen(PROC_FILENAME, "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    printf("Contents of /proc/my_proc:\n");
    while (fgets(read_buffer, BUFFER_SIZE, fp)) {
        printf("%s", read_buffer);
    }

    fclose(fp);

    return 0;
}
