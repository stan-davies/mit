#include "util.h"

#include <stdio.h>
#include <stdlib.h>

int rd_wk(
        void
) {
        FILE *f = fopen("logs/curr", "r");
        if (!f) {
                return 1;
        }

        char *cnt = calloc(8, sizeof(char));
        fread(cnt, sizeof(char), 8, f);

        fclose(f);

        return atoi(cnt);
}
