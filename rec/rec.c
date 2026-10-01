#include "rec.h"

#include <stdio.h>
#include <stdlib.h>

#include "util/util.h"

void rec(
        void
) {
        char *rec = rweekr(0);
        if (!rec) {
                printf("  Could not read current week data.\n");
        }

        int i = 0;
        char c;

        printf("  Expense records for current week:\n\n  £");
        while ((c = rec[i++])) {
                if ('\n' == c) {
                        printf("\n  £");
                } else {
                        printf("%c", c);
                }
        }

        printf("\n");

        free(rec);
        rec = NULL;
}
