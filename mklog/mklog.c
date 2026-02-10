#include "mklog.h"

#include <stdio.h>
#include <stdlib.h>

#include "util/util.h"
#include "cli/cli.h"
#include "sum/sum.h"

static void mk_sv(
        void
);

void mk_log(
        float           quant
) {
        int w = rcurr();
        
        char *fname = calloc(8, sizeof(char));
        sprintf(fname, LOGS_PATH "/%d", w);

        FILE *f = fopen(fname, "a");
        if (!f) {
                printf("Error: Log file not found.\n");
                return;
        }

        fprintf(f, "%.2f\n", quant);

        fclose(f);

        free(fname);
        fname = NULL;
}

void up_wk(
        void
) {
        mk_sv();

        int c = rcurr();

        FILE *f = fopen(CURR_PATH, "w");
        if (!f) {
                return;
        }

        fprintf(f, "%d", c + 1);
        fclose(f);
}

static void mk_sv(
        void
) {
        float t = 100.f - rweek(0);

        if (t <= 0.f) {
                printf("  No savings this week.\n");
                return;
        }

        printf("  Savings of £%.2f this week.\n", t);

        adj_sv(t);

        sum_sv();
}

void adj_sv(
        float           quant
) {
        float s = rspec() + quant;

        FILE *f = fopen(SAVE_PATH, "w");
        if (!f) {
                return;
        }

        fprintf(f, "%.2f", s);
        fclose(f);
}
