#include "sum.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "util/util.h"
#include "util/bounds.h"

#define CL_GREEN        2
#define CL_CYAN         14
#define CL_L_GREEN      10
#define CL_ORANGE       11
#define CL_RED          9

static void col_quant(
        float           period          ,
        float           total
);

static void dly_data(
        float           spent
);

static void wkly_data(
        float           spent           ,
        int             n_wks
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

        if (1 == period) {
                printf("  This week's spending:\n\n");
        } else {
                printf("  Spending over past %d weeks:\n\n", period);
        }

        float q;                                        // Quantity.
        float t = 0.f;                                  // Total.
        int c = rcurr();                                // Current week.
        for (int w = period; w > 0; --w) {              // Week offset.
                if (c - w < 0) {
                        continue;
                }
                q = rweek(w - 1);
                printf("  week %d\t\t", c - w + 1);
                col_quant(1.f, q);
                print_bar(q);
                t += q;
        }

        if (1 == period) {
                if (t > 0.f) {          // Start of new week.
                        dly_data(t);
                }
        } else {
                wkly_data(t, period);
        }
}

void sum_sv(
        void
) {
        float s = rspec();
        printf("  Savings\t\t£%.2f.\n", s);
}

static void col_quant(
        float           period          ,
        float           total
) {
        int col = CL_RED;

        if (total <= FIRST_B * period) {
                col = CL_CYAN;
        } else if (total <= (FIRST_B + B_WIDTH) * period) {
                col = CL_L_GREEN;
        } else if (total <= (FIRST_B + 2.f * B_WIDTH) * period) {
                col = CL_ORANGE;
        }
        
        printf("\033[%d;3%dm£%.2f\033[0m", col / 8, col % 8, total);
}

static void dly_data(
        float           spent
) {
        time_t t = time(NULL);
        struct tm datetime = *localtime(&t);
        int day = datetime.tm_wday;             // Days since Sunday.
        day = 0 == day ? 7 : day;               // Correct for Sunday.

        printf("\n  daily average\t\t");
        col_quant((float)day / 7.f, spent / day);
        
        float cap = FIRST_B;
        while (spent > cap) {
                cap += B_WIDTH;
        }

        printf("\n  of ");
        col_quant(1.f, cap);
        printf(" you have\n    per day\t\t£%.2f\n    in total\t\t£%.2f\n",
                (cap - spent) / (7 - day), cap - spent);
}

static void wkly_data(
        float           spent   ,
        int             n_wks
) {
        printf("\n  total\t\t\t");
        col_quant((float)n_wks, spent);
        printf("\n  daily average\t\t");
        col_quant(1.f, spent / (n_wks * 7.f));
        printf("\n  weekly average\t");
        col_quant(7.f, spent / n_wks);
        printf("\n");
}

static void print_bar(
        float           total
) {
        int col, bxs = 0;
        wchar_t c;
        for (;;) {
                if ((float)(++bxs * 5) >= total) {
                        break;
                }
        }

        printf("\t");
        for (int b = 1; b < bxs; ++b) {
//                c = L'•';
//                c = 0x2580;     // Top half.
                c = 0x2501;     // Thick vertical.

                if (b < FIRST_B / 5) {
                        col = 14;

//                        c = L'◦';
//                        c = 0x2500;     // Thin vertical.
//                        c = 0x2593;     // Dark box.
                } else if (b < (FIRST_B + B_WIDTH) / 5) {
                        col = CL_L_GREEN;

//                        c = 0x2501;     // Thick vertical.
//                        c = 0x2588;     // Filled box.
                } else if (b < (FIRST_B + 2 * B_WIDTH) / 5) {
                        col = CL_ORANGE;

//                        c = 0x2550;     // Double stroke vertical.
//                        c = 0x2588;     // Filled box.
                } else {
                        col = CL_RED;

//                        c = 0x2550;     // Double stroke vertical.
//                        c = 0x2588;     // Filled box.
                }

                printf("\033[%d;3%dm%lc\033[0m", col / 8, col % 8, c);
        }
        printf("\n");
}
