#include "mklog.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "util/util.h"

#define SUNDAY  1

static int get_wk(
        int             offset
);

static void up_wk(
        int             w
);

static void mk_sv(
        void
);

void make_log(
        float           quant   ,
        int             offset
) {
        int w = get_wk(offset);
        
        char *fname = calloc(8, sizeof(char));
        sprintf(fname, "logs/%d", w);

        FILE *f = fopen(fname, "a");
        if (!f) {
                return;
        }

        fprintf(f, "%.2f\n", quant);

        fclose(f);

        free(fname);
        fname = NULL;
}

void make_log_sp(
        float           quant
) {
        FILE *f = fopen("logs/save", "r+");
        if (NULL == f) {
                return;
        }

        char *buf = calloc(8, sizeof(char));
        char c;
        int i = 0;
        while (EOF != (c = fgetc(f))) {
                buf[i++] = c;
        }

        rewind(f);

        float s = atof(buf) - quant;
        free(buf);
        buf = NULL;

        fprintf(f, "%.2f", s);
        fclose(f);
}

static int get_wk(
        int             offset
) {
        time_t t = time(NULL);
        struct tm datetime = *localtime(&t);
        int day = datetime.tm_wday + 1;

        int w = rd_wk();

        if (0 == offset && SUNDAY == day) {
                printf("Today is Sunday. Moving to new week.\n");
                mk_sv();
                up_wk(w);
        }

        if (day - offset <= 0) {
                w--;
        }

        return w;
}


static void up_wk(
        int             w
) {
        FILE *f = fopen("logs/curr", "w");
        if (!f) {
                printf("Could not overwrite file 'logs/curr'.\n");
                return;
        }

        fprintf(f, "%d", w + 1);

        fclose(f);
}

static void mk_sv(
        void
) {
        float t = rweek(0);

        FILE *f = fopen("logs/save", "r+");
        if (!f) {
                return;
        }

        char *buf = calloc(8, sizeof(char));
        char c;
        int i = 0;
        while (EOF != (c = fgetc(f))) {
                buf[i++] = c;
        }

        if (t >= 100.f) {
                printf("No savings this week.\n");
        } else {
                t = (100.f - t) + atof(buf);
        }

        free(buf);
        buf = NULL;

        rewind(f);
        fprintf(f, "%.2f", t);

        fclose(f);
}
