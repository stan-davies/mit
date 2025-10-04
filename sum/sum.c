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
        float t;
        char *pr_str = calloc(8, sizeof(char));

        if (PR_WEEK == period) {
                t = rweek(0);
                sprintf(pr_str, "week");
        } else if (PR_MNTH == period) {
                t = rweek(0) + rweek(1) + rweek(2) + rweek(3);
                sprintf(pr_str, "month");
        }

        printf("So far this %s you have spent ", pr_str);

        if (t <= 40.f * period) {
                colourise(CL_GREEN);
        } else if (t <= 70.f * period) {
                colourise(CL_L_GREEN);
        } else if (t <= 100.f * period) {
                colourise(CL_YELLOW);
        } else {
                colourise(CL_L_RED);
        }

        printf("£%.2f", t);

        colourise(CL_WHITE);
        printf(".\n");
}

void sum_sp(
        void
) {
        FILE *f = fopen("logs/save", "r");
        if (!f) {
                return;
        }

        char *buf = calloc(8, sizeof(char));
        char c;
        int i = 0;
        while (EOF != (c = fgetc(f))) {
                buf[i++] = c;
        }

        fclose(f);

        float s = atof(buf);
        free(buf);
        buf = NULL;

        printf("Total savings are currently £%.2f.\n", s);
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
