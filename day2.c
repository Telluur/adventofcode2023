#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Game {
    int gameNum, gamePower;
    bool violatesPartOne;
} game;


void parseLine(const char* line, game* game) {
    int gameNumber;
    int count;

    // Use sscanf to parse the line
    if (sscanf(line, "Game %d:", &gameNumber) == 1) {
        printf("Game %d:\n", gameNumber);
        game->gameNum = gameNumber;

        // Move the pointer after the colon
        const char* token = strchr(line, ':');
        if (token != NULL) {
            char color[10];
            int setCount = 0;
            int red = 0;
            int blue = 0;
            int green = 0;

            token++; // Step over the : char


            printf("  Set %d: ", setCount);

            // Parse sets
            int consumed = 0;
            while (sscanf(token, "%d %9[^,;\n] %n", &count, color, &consumed) == 2) {
                printf("%d %s", count, color);

                /*
                 * Part one violation check
                 */
                if (
                    (strncmp("red", color, 3) == 0 && count > 12) ||
                    (strncmp("green", color, 5) == 0 && count > 13) ||
                    (strncmp("blue", color, 4) == 0 && count > 14)
                ) {
                    printf("*"); // indicates violation
                    game->violatesPartOne = true;
                }

                printf(", ");

                /*
                 * Part two: minimum count check
                 */
                if (strncmp("red", color, 3) == 0 && count > red) {
                    red = count;
                } else if (strncmp("green", color, 5) == 0 && count > green) {
                    green = count;
                } else if (strncmp("blue", color, 4) == 0 && count > blue) {
                    blue = count;
                }


                /*
                 * Continue parsing; check next token
                 */
                token = token + consumed;
                if (*token == '\0') {
                    printf("\n");
                    break;
                }
                if (*token == ';') {
                    setCount++;
                    printf("\n  Set %d: ", setCount);
                }
                token++;
            }

            /*
             * Part two: done parsing, compute power
             */
            game->gamePower = red * green * blue;
        }
    }
}


int main() {
    char* line = NULL;
    size_t line_len = 0;

    // Open the file for reading
    FILE* file = fopen("../input/2/challenge.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }


    int sum = 0, power = 0;
    while (getline(&line, &line_len, file) != -1) {
        game* game_ptr = malloc(sizeof(game));
        game_ptr->gameNum = 0;
        game_ptr->gamePower = 0;
        game_ptr->violatesPartOne = false;

        parseLine(line, game_ptr);
        if (!game_ptr->violatesPartOne) {
            sum += game_ptr->gameNum;
        }
        power += game_ptr->gamePower;


        free(game_ptr);
    }

    printf("Part 1: Sum of games %d.\n", sum);
    printf("Part 2: Sum of power of games %d.\n", power);

    return 0;
}
