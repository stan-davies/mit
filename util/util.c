#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static float sum_file(
        char           *fname
);

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
        if (w <= 0) {
                return 0.f;
        }

        char *fname = calloc(64, sizeof(char));
        sprintf(fname, LOGS_PATH "/%d", w);

        float total = sum_file(fname);

        free(fname);
        fname = NULL;
        
        return total;
}

float rspec(
        void
) {
        return sum_file(SAVE_PATH);
}

static float sum_file(
        char           *fname
) {
        FILE *f = fopen(fname, "r");
        if (!f) {
                return 0.f;
        }

        char *buf = calloc(16, sizeof(char));
        float total = 0.f;
        int i = 0;
        char c;

        while (EOF != (c = fgetc(f))) {
                if ('\n' == c) {
                        buf[i] = '\0';
                        total += atof(buf);
                        memset(buf, '\0', 16);
                        i = 0;
                        continue;
                }
                if (i >= 16) {
                        printf("Line too long, data corrupted in '%s'\n",
                                fname);
                        break;
                }

                buf[i++] = c;   
        }

        free(buf);
        buf = NULL;

        fclose(f);

        return total;
}
