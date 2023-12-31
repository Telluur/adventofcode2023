#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parseString(const char* line) {
    const size_t remaining_line_size = strlen(line);
    if (remaining_line_size >= 3) {
        if (strncmp(line, "one", 3) == 0) {
            return 1;
        }
        if (strncmp(line, "two", 3) == 0) {
            return 2;
        }
        if (strncmp(line, "six", 3) == 0) {
            return 6;
        }
        if (remaining_line_size >= 4) {
            if (strncmp(line, "four", 4) == 0) {
                return 4;
            }
            if (strncmp(line, "five", 4) == 0) {
                return 5;
            }
            if (strncmp(line, "nine", 4) == 0) {
                return 9;
            }
            if (remaining_line_size >= 5) {
                if (strncmp(line, "three", 5) == 0) {
                    return 3;
                }
                if (strncmp(line, "seven", 5) == 0) {
                    return 7;
                }
                if (strncmp(line, "eight", 5) == 0) {
                    return 8;
                }
            }
        }
    }
    return -1;
}

int main() {
    char* line = NULL;
    size_t line_len = 0;
    int sum = 0;

    // Open the file for reading
    FILE* file = fopen("../input/1/challenge.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }


    /*
     * Read the file line by line
     */
    while (getline(&line, &line_len, file) != -1) {
        const char* char_ptr = line;
        int first = -1;
        int last = -1;


        /*
         * Iterate over characters using a while loop
         */
        while (*char_ptr != '\0') {
            /*
             * Check if the character is a digit, and parse accordingly
             */
            if (isdigit(*char_ptr)) {
                if (first == -1) {
                    first = *char_ptr - '0';
                }
                last = *char_ptr - '0';
            } else {
                /*
                 * Check if the remaining string starts with a written number, and parse accordingly.
                 */
                const int val = parseString(char_ptr);
                if (val != -1) {
                    if (first == -1) {
                        first = val;
                    }
                    last = val;
                }
            }
            /*
             * Move the pointer to the next character
             */
            char_ptr++;
        }


        const int combined = 10 * first + last;
        printf("First: %d, last: %d, combined: %d | %s", first, last, combined, line);

        sum += combined;
    }

    /*
     * Close the file
     */
    fclose(file);

    /*
     * Free the dynamically allocated memory
     */
    free(line);

    printf("Total sum: %d", sum);
    return 0;
}
