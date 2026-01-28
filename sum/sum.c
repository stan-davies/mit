#include "sum.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "util/util.h"
#include "util/bounds.h"

#define CL_B_1          12      // Bright blue.
#define CL_B_2          10      // Light green.
#define CL_B_3          11      // Orange/light yellow.
#define CL_B_4          9       // Light red.

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
        float q;                                        // Quantity.
        float t = 0.f;                                  // Total.
        int c = rcurr();                                // Current week.

        switch (period) {
        case PR_SPEC:
                sum_sv();
                return;
        case 1:
                printf("  This week's spending:\n\n");
                break;
        case PR_ALL:
                period = c;
                // No break.
        default:
                printf("  Spending over past %d weeks:\n\n", period);
                break;
        }

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
        float           period          ,       // 1 refers to 1 week.
        float           total
) {
        int col = CL_B_4;

        if (total <= FIRST_B * period) {
                col = CL_B_1;
        } else if (total <= (FIRST_B + B_WIDTH) * period) {
                col = CL_B_2;
        } else if (total <= (FIRST_B + 2.f * B_WIDTH) * period) {
                col = CL_B_3;
        }
        
        printf("\033[%d;%d%dm£%.2f\033[0m", col / 8, 3 + 6 * (col / 8), col % 8, total);
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
        col_quant(1.f / 7.f, spent / (n_wks * 7.f));
        printf("\n  weekly average\t");
        col_quant(1.f, spent / n_wks);
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
//                c = L'◦';
//                c = L'▀';
                c = L'━';

                if (b < FIRST_B / 5) {
                        col = CL_B_1;

                } else if (b < (FIRST_B + B_WIDTH) / 5) {
                        col = CL_B_2;
                } else if (b < (FIRST_B + 2 * B_WIDTH) / 5) {
                        col = CL_B_3;
                } else {
                        col = CL_B_4;
                }

                printf("\033[%d;%d%dm%lc\033[0m", col / 8, 3 + 6 * (col / 8), col % 8, c);
        }
        printf("\n");
}
