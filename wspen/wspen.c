#include "wspen.h"

#include <stdio.h>
#include <stdlib.h>

void spen(
        int             week    ,
        float           spen
) {
        char *fname = calloc(8, sizeof(char));
        sprintf(fname, "logs/%d", week);
        FILE *f = fopen(fname, "a");

        if (!f) {
                return;
        }

        fprintf(f, "%.2f\n", spen);

        free(fname);
        fname = NULL;
}
