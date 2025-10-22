#include "util.h"

#include <stdio.h>
#include <stdlib.h>

#include "paths.h"

#define CH_LF   10
#define CH_NL   0

int rd_wk(
        void
) {
        FILE *f = fopen(CURR_PATH, "r");
        if (!f) {
                printf("Error: current week file not found.\n");
                return 1; // What is this?
        }

        char *cnt = calloc(8, sizeof(char));
        fread(cnt, sizeof(char), 8, f);

        fclose(f);

        return atoi(cnt);
}

float rweek(
        int             offset
) {
        int w = rd_wk() - offset;

        char *fname = calloc(8, sizeof(char));
        sprintf(fname, "%s/%d", LOGS_PATH, w);

        printf("Searching for '%s'.\n", fname);

        FILE *f = fopen(fname, "r");
        if (!f) {
                printf("File not found.\n");
                return 0.f; // If no file, give 0 spending for that week
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
