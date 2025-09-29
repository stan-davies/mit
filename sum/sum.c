#include "sum.h"

#include <stdlib.h>
#include <stdio.h>

#include "util/util.h"

#define CH_LF   10
#define CH_NL   0

static float rweek(
        int             offset
);

void sum(
        int             period
) {
        float t = rweek(0);

        printf("So far this week you have spent £%.2f.\n", t);
}

static float rweek(
        int             offset
) {
        int w = rd_wk() - offset;

        char *fname = calloc(8, sizeof(char));
        sprintf(fname, "logs/%d", w);

        FILE *f = fopen(fname, "r");
        if (!f) {
                return -1;
        }

        float total = 0.f;
        char *buf = calloc(8, sizeof(char));
        char c;
        int j = 0;

        while (EOF != (c = fgetc(f))) {
                if (CH_LF == c) {
                        total += atof(buf);
                        for (int i = 0; i < 8; ++i) {
                                buf[i] = CH_NL;
                        }
                        j = 0;
                }
                buf[j++] = c;
        }

        free(buf);
        buf = NULL;

        fclose(f);

        free(fname);
        fname = NULL;
        
        return total;
}
