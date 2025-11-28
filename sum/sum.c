#include "sum.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "util/util.h"
#include "util/bounds.h"

#define CL_GREEN        2
#define CL_L_GREEN      10
#define CL_ORANGE       11
#define CL_RED          9

static void colourise(
        float           period          ,
        float           total           ,
        int             nline
);

static void ex_data(
        float           spent
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
                colourise(1.f, q, TRUE);
                t += q;
        }

        if (1 == period) {      // No need to give period summary for one week.
                                // Give daily average spend instead.
                ex_data(t);
                return;
        }

        printf("In total over this period you have spent ");
        colourise((float)period, t, TRUE);
}

void sum_sv(
        void
) {
        float s = rspec();
        printf("Total savings are currently £%.2f.\n", s);
}

static void colourise(
        float           period          ,
        float           total           ,
        int             nline
) {
        int col = CL_RED;

        if (total <= FIRST_B * period) {
                col = CL_GREEN;
        } else if (total <= (FIRST_B + B_WIDTH) * period) {
                col = CL_L_GREEN;
        } else if (total <= (FIRST_B + 2.f * B_WIDTH) * period) {
                col = CL_ORANGE;
        }
        
        printf("\033[%d;3%dm£%.2f\033[0m", col / 8, col % 8, total);
        
        if (nline) {
                printf("\n");
        }
}

static void ex_data(
        float           spent
) {
        time_t t = time(NULL);
        struct tm datetime = *localtime(&t);
        int day = datetime.tm_wday;             // Days since Sunday.
        day = 0 == day ? 7 : day;               // Correct for Sunday.

        printf("That is an average of ");
        colourise((float)day / 7.f, spent / day, FALSE);
        printf(" per day.\n");
        
        float cap = FIRST_B;
        while (spent > cap) {
                cap += B_WIDTH;
        }

        printf("To remain under the ");
        colourise((float)day / 7.f, cap, FALSE);
        printf(" limit this week, try to spend around £%.2f each day for the "
               "rest of the week, or £%.2f in total.\n",
                (cap - spent) / (7 - day), cap - spent);
}
