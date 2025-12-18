#include "mklog.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "util/util.h"
#include "cli/cli.h"
#include "sum/sum.h"

#define SUNDAY  0

static int proc = FALSE;                // Whether to proceed to new week.

static int get_wk(
        void
);

static void mk_sv(
        void
);

void mk_log(
        float           quant
) {
        int w = get_wk();
        
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

        if (proc) {
                up_wk();
        }
}

// Scrap this whole function, just use `rcurr`, check for Sunday in `cli.c`
// after the logging is all done with.
static int get_wk(
        void
) {
        time_t t = time(NULL);
        struct tm datetime = *localtime(&t);
        int day = datetime.tm_wday;             // Days since Sunday

        if (SUNDAY == day && rq_up_wk()) {
                proc = TRUE;
        }

        return rcurr();
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
