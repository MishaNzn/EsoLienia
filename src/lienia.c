/* EsoLienia: an esoteric programing language inspired by Brainfuck

    Copyright (C) 2022, Lienish Software Organization

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "lienia.h"

unsigned char command[4194304];

unsigned char p_arr[MAX_CELL];
unsigned short p_num;

char stack[STACK_SIZE];
unsigned short currStack;
bool stackOpen;

void addStack(char commChar) {
    stack[currStack] = commChar;
    currStack++;
}

void clearStack() {
    for (int i = 0; i < STACK_SIZE; i++) {
        stack[i] = 0;
    }
}

void setupProgram() {
    p_num = 0;

    for (int i = 0; i < MAX_CELL; i++) {
        p_arr[i] = 0;
    }

    stackOpen = false;
    currStack = 0;
}

int readFile(const char *filename) {
    FILE *fp;

    int c;
    int count = 0;

    fp = fopen(filename, "r");

    if (fp == NULL) {
        return FAILURE;
    }

    while ((c = getc(fp)) != EOF) {
        command[count] = c;
        count++;
    }
    fclose(fp);
    return SUCCESS;
}

int executeProgram(unsigned char *command) {
    int count = 0;

    for (size_t i = 0; i < strlen(command); i++) {
        if (!stackOpen) {
            switch (command[i]) {
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
                    p_num = 0;
                }
                break;
            case '<':
                if (p_num > 0) {
                    P_DEC(p_num);
                } else {
                    p_num = MAX_CELL;
                }
                break;
            case '[':
                if (stackOpen) {
                    fprintf(stderr, "Error at char %d: loops can not be nested.\n", count);
                    return FAILURE;
                } else {
                    stackOpen = true;
                }
                break;
            case '=':
                P_SET(0, p_num);
                break;
            case '@':
                P_SET(MAX_CELL, p_num);
                break;
            case '$':
                P_SET(255, p_arr[p_num]);
                break;
            case '~':
                P_SET(0, p_arr[p_num]);
                break;
            case ']':
                if (stackOpen) {
                    stackOpen = false;
                } else {
                    fprintf(stderr, "Error at char %d: while loop does not exist (opening char '[' was found).\n", count);
                    return FAILURE;
                }
                break;
            case ';':
                P_END;
                break;
            }
        } else if (stackOpen) {
            if (command[i] != ']') {
                if (currStack >= STACK_SIZE) {
                    fprintf(stderr, "Error at char %d: overflow of loop stack.\n", count);
                } else {
                    addStack(command[i]);
                }
            } else {
                stackOpen = false;
                while (p_arr[p_num] != 0) {
                    executeProgram(stack);
                }
                clearStack();
            }
        }
        count++;
    }
    return FAILURE;
}

int main(int argc, char *argv[]) {
    int status;
    status = FAILURE;

    if (argc == 1) {
        fprintf(stderr, "Usage: %s [options] filename.lienia\n", argv[0]);
        return FAILURE;
    }

    if (!strcmp(argv[1], "-l")) {
        printf("EsoLienia Programing Language\n");
        printf("Copyright (C) 2022 Lienish Software Organisation\n\n");
        printf("This program comes with ABSOLUTELY NO WARRANTY;\n");
        printf("This is free software, and you are welcome to\n");
        printf("redistribute it under conditions of GNU General Public License.\n");
        return SUCCESS;
    }

    if (readFile(argv[argc - 1])) {
        fprintf(stderr, "File \"%s\" was not found\n", argv[1]);
        return FAILURE;
    }

    if (!executeProgram(command)) {
        status = SUCCESS;
    }

    return status;
}

