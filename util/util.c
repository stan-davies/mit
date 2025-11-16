#include "util.h"

#include <stdio.h>
#include <stdlib.h>

#define CH_LF   10
#define CH_NL   0

int rcurr(
        void
) {
        FILE *f = fopen(CURR_PATH, "r");
        if (!f) {
                return 1;
        }

        char *buf = calloc(8, sizeof(char));
        char c;
        int i = 0;
        while (EOF != (c = fgetc(f))) {
                buf[i++] = c;
        }

        fclose(f);

        return atoi(buf);
}

float rweek(
        int             offset
) {
        int w = rcurr() - offset;

        char *fname = calloc(8, sizeof(char));
        sprintf(fname, "%s/%d", LOGS_PATH, w);

        float total = 0.f;

        FILE *f = fopen(fname, "r");
        if (!f) {
                // If no file, give 0 spending for that week, i.e. total = 0.f
                goto exit;
        }

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

exit:
        free(fname);
        fname = NULL;
        
        return total;
}

float rspec(
        void
) {
        FILE *f = fopen(SAVE_PATH, "r");
        if (!f) {
                return 0.f;
        }

        char *buf = calloc(8, sizeof(char));
        char c;
        int i = 0;
        while (EOF != (c = fgetc(f))) {
                buf[i++] = c;
        }

        fclose(f);

        float total = atof(buf);
        free(buf);
        buf = NULL;

        return total;
}
