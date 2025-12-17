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

static void col_quant(
        float           period          ,
        float           total           ,
        int             nline
);

static void ex_data(
        float           spent
);

static void print_bar(
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
                printf("Week %d\t\t", period - w + 1);
                col_quant(1.f, q, FALSE);
                print_bar(q);
                t += q;
        }

        if (1 == period) {      // No need to give period summary for one week.
                                // Give daily average spend instead.
                if (t > 0.f) {
                        ex_data(t);
                }
                return;
        }

        printf("In total over this period you have spent ");
        col_quant((float)period, t, TRUE);
}

void sum_sv(
        void
) {
        float s = rspec();
        printf("Total savings are currently £%.2f.\n", s);
}

static void col_quant(
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

        printf("\nThat is an average of ");
        col_quant((float)day / 7.f, spent / day, FALSE);
        printf(" per day. ");
        
        float cap = FIRST_B;
        while (spent > cap) {
                cap += B_WIDTH;
        }

        printf("To remain under the ");
        col_quant(1.f, cap, FALSE);
        printf(" limit this week, try to spend under £%.2f each day for the "
               "rest of the week, or £%.2f in total.\n",
                (cap - spent) / (7 - day), cap - spent);
}

static void print_bar(
        float           total
) {
        int col, bxs = 0;
        for (;;) {
                if ((float)(++bxs * 5) >= total) {
                        break;
                }
        }

        printf("\t");
        for (int b = 1; b < bxs; ++b) {
                if (b < FIRST_B / 5) {
                        col = CL_GREEN;
                } else if (b < (FIRST_B + B_WIDTH) / 5) {
                        col = CL_L_GREEN;
                } else if (b < (FIRST_B + 2 * B_WIDTH) / 5) {
                        col = CL_ORANGE;
                } else {
                        col = CL_RED;
                }

// º (alt + 0)
// • (alt + 8)
// – (alt + -)
                printf("\033[%d;3%dm–\033[0m", col / 8, col % 8);
        }
        printf("\n");
}
