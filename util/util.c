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
        if (w <= 0) {
                return 0.f;
        }

        char *fname = calloc(64, sizeof(char));
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
                        if (j < 0 || j >= 8) {  // ?
                                printf("rweek cap out of bounds\n");
                        }
                        buf[j] = '\0';
                        total += atof(buf);
                        memset(buf, CHR_NULL, 8);
                        j = 0;
                        continue;
                }
                if (j < 0 || j >= 8) {          // ?
                        printf("rweek out of bounds\n");
                }
                buf[j++] = c;   // Notably nothing to prevent writing beyond capacity.
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
                if (i >= 8) {
                        printf("too many characters in special data");
                }
                buf[i++] = c;   // Longer than 8 characters... Probably not.
        }

        fclose(f);

        float total = atof(buf);
        free(buf);
        buf = NULL;

        return total;
}
