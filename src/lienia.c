#include <stdio.h>
#include <string.h>

#define VERSION_MAJOR 0
#define VERSION_MINOR 2
#define VERSION_PATCH 5

#define MAX_CELL 8
#define MIN_CELL 0

#define SUCCESS 0
#define FAILURE 1

#define P_OUT(A)     putchar(A)
#define P_IN(A)      A = getchar()
#define P_SET(A, B)  B = A
#define P_IF(A, B)   if (A) B
#define P_LOOP(A)    while (1) A
#define P_INC(A)     A++
#define P_DEC(A)     A--
#define P_END        0

short int p_arr[MAX_CELL] = {0, 0, 0, 0, 0, 0, 0, 0};
int p_num = 0;

int executeProgram(FILE *fp) {
    int c;
    while ((c = getc(fp)) != EOF) {
        switch (c) {
        case '!':
            P_OUT(p_arr[p_num]);
            break;
        case '?':
            P_IN(p_arr[p_num]);
            break;
        case ':':
            P_IF(p_arr[p_num], P_OUT(p_arr[p_num]));
            break;
        case '+':
            P_INC(p_arr[p_num]);
            break;
        case '-':
            P_DEC(p_arr[p_num]);
            break;
        case '>':
            if (p_num < MAX_CELL) {
                P_INC(p_num);
            } else {
                fprintf(stderr, "Error: stackowerflow of storage index.\n");
                return FAILURE;
            }
            break;
        case '<':
            if (p_num > MIN_CELL) {
                P_DEC(p_num);
            } else {
                fprintf(stderr, "Error: stackowerflow of storage index.\n");
                return FAILURE;
            }
            break;
        case '[':
            P_LOOP(P_OUT(p_arr[p_num]));
            break;
        case '=':
            P_SET(0, p_num);
            break;
        case '~':
            P_SET(0, p_arr[p_num]);
            break;
        case ';':
            return P_END;
            break;
        default:
            break;
        }
    }
    fprintf(stderr, "Error: terminating char ';' was not found.\n");
    return FAILURE;
}

int main(int argc, char *argv[]) {
    int status;
    status = FAILURE;
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename.lienia\n", argv[0]);
        return FAILURE;
    }

    if (!strcmp(argv[1], "-v")) {
        printf("%d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
        return SUCCESS;
    } else if (!strcmp(argv[1], "-h")) {
        printf("Usage: %s [-options] filename.lienia\n\nOptions:\n  -v\t\tDisplays interpreter version\n  -h\t\tDisplays help message\n", argv[0]);
        return SUCCESS;
    } else if (!strcmp(argv[1], "-std=22")) {
        ;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "File \"%s\" was not found\n", argv[1]);
        return FAILURE;
    }

    if (!executeProgram(fp)) {
        status = SUCCESS;
    }

    fclose(fp);
    return status;
}
