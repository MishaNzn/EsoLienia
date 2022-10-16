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

#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CELL    1000
#define STACK_SIZE  10000
#define SUCCESS     0
#define FAILURE     -1

#define P_OUT(A)     putc(A, stdout)
#define P_IN(A)      A = getchar()
#define P_SET(A, B)  B = A
#define P_IF(A, B)   if (A) B
#define P_INC(A)     A++
#define P_DEC(A)     A--
#define P_END        return SUCCESS
