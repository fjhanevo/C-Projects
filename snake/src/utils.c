#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

#define MAX_INPUT 128
#define MAX_WIDTH 116
#define MAX_HEIGHT 60
#define MIN_SIZE 2


static int get_valid_int(const char *msg, int max)
/* helper function for get_size to get valid input for height and width */
{
    char buf[MAX_INPUT];
    char *end;
    long val;

    while (1) {
        printf("%s", msg);
        if (!fgets(buf, sizeof(buf), stdin)) exit(1);

        val = strtol(buf, &end, 10);
        if (end == buf || (*end != '\n' && *end != '\0')) {
            printf("Invalid number!\n\n");
            continue;
        }
        if (val < MIN_SIZE || val > max) {
            printf("Value must be between %d and %d\n\n", MIN_SIZE, max);
            continue;
        }
        return (int)val;
    }
}

void get_size(int *width, int *height) 
{
    *width = get_valid_int("Please type in border width: ", MAX_WIDTH); 
    *height = get_valid_int("Please type in border height: ", MAX_HEIGHT);
}
