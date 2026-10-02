#include "rec.h"

#include <stdio.h>
#include <stdlib.h>

#include "util/util.h"

static void print_wr(
        char           *rec
);

static void print_sr(
        char           *rec
);

void rec(
        int             s
) {
        char *rec = s ? rspecr() : rweekr(0);
        if (!rec) {
                printf("  Could not read requested records.\n");
        }

        if (s) {
                print_sr(rec);
        } else {
                print_wr(rec);
        }

        free(rec);
        rec = NULL;
}

static void print_wr(
        char           *rec
) {
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
}

static void print_sr(
        char           *rec
) {
        int i = 0;
        char c;

        printf("  Expense records for current savings period:\n\n  in\t\tout\n  ");
        int new = TRUE;
        while ((c = rec[i++])) {
                if ('-' == c) {
                        // Undecided on blue (94) or yellow (93).
                        printf("\t\t\033[94m£");
                        new = FALSE;
                } else if (new) {
                        printf("\033[92m£%c", c);
                        new = FALSE;
                } else if ('\n' == c) {
                        printf("\033[0m\n  ");
                        new = TRUE;
                } else {
                        printf("%c", c);
                }
        }
}
