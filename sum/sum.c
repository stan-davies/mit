#include "sum.h"

#include <stdlib.h>
#include <stdio.h>

#include "util/util.h"


// #define CL_BLACK       0       
#define CL_RED         1       
#define CL_GREEN       2       
#define CL_ORANGE      3       
//#define CL_BLUE        4       
//#define CL_PURPLE      5       
//#define CL_CYAN        6       
//#define CL_L_GRAY      7       
//#define CL_D_GRAY      8       
#define CL_L_RED       9       
#define CL_L_GREEN     10
#define CL_YELLOW      11
// #define CL_L_BLUE      12
// #define CL_L_PURPLE    13
// #define CL_L_CYAN      14
#define CL_WHITE       15


static void colourise(
        int             col
);

void sum(
        int             period
) {
        float t = rweek(0);

        printf("So far this week you have spent ");

        if (t <= 40.f) {
                colourise(CL_GREEN);
        } else if (t <= 70.f) {
                colourise(CL_L_GREEN);
        } else if (t <= 100.f) {
                colourise(CL_YELLOW);
        } else {
                colourise(CL_L_RED);
        }

        printf("£%.2f", t);

        colourise(CL_WHITE);
        printf(".\n");
}

static void colourise(
        int             col
) {
        if (CL_WHITE == col) {
                printf("\033[0m");
                return;
        }

        printf("\033[%d;3%dm", col / 8, col % 8);
}
