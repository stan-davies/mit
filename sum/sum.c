#include "sum.h"

#include <stdlib.h>
#include <stdio.h>

#include "util/util.h"

#define CL_GREEN        2
#define CL_L_GREEN      10
#define CL_ORANGE       11
#define CL_RED          9

static void colourise(
        int             period          ,
        float           total
);

void sum(
        int             period
) {
        if (PR_SPEC == period) {
                sum_sv();
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

void sum_sv(
        void
) {
        float s = rspec();
        printf("Total savings are currently £%.2f.\n", s);
}

static void colourise(
        int             period          ,
        float           total
) {
        int col = CL_RED;

        if (total <= 40.f * period) {
                col = CL_GREEN;
        } else if (total <= 70.f * period) {
                col = CL_L_GREEN;
        } else if (total <= 100.f * period) {
                col = CL_ORANGE;
        }
        
        printf("\033[%d;3%dm£%.2f\033[0m\n", col / 8, col % 8, total);
}
