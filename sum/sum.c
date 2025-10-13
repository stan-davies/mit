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
        int             period          ,
        float           total
);

void sum(
        int             period
) {
        if (PR_SPEC == period) {
                sum_sp();
                return;
        }

        float q;
        float t = 0.f;
        for (int w = period; w > 0; --w) {
                q = rweek(w - 1);
                printf("Week %d: ", period - w + 1);
                colourise(1, q);
                t += q;
        }

        if (1 == period) {      // No need to give period summary for single
                return;         // unit period.
        }

        printf("In total over this period you have spent ");
        colourise(period, t);
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
        int             period          ,
        float           total
) {
        int col = CL_L_RED;

        if (total <= 40.f * period) {
                col = CL_GREEN;
        } else if (total <= 70.f * period) {
                col = CL_L_GREEN;
        } else if (total <= 100.f * period) {
                col = CL_YELLOW;
        }
        
        printf("\033[%d;3%dm£%.2f\033[0m\n", col / 8, col % 8, total);
}
