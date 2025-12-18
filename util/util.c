#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        sprintf(fname, LOGS_PATH "/%d", w);

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
                if ('\n' == c) {
                        total += atof(buf);
                        memset(buf, CHR_NULL, 8);
                        j = 0;
                        continue;
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
