#include "mklog.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "util/util.h"

static int get_wk(
        int             offset
);


static void up_wk(
        int             w
);

void make_log(
        float           spen    ,
        int             offset
) {
        int w = get_wk(offset);
        
        char *fname = calloc(8, sizeof(char));
        sprintf(fname, "logs/%d", w);

        FILE *f = fopen(fname, "a");
        if (!f) {
                return;
        }

        fprintf(f, "%.2f\n", spen);

        fclose(f);

        free(fname);
        fname = NULL;
}

static int get_wk(
        int             offset
) {
        time_t t = time(NULL);
        struct tm datetime = *localtime(&t);
        int day = datetime.tm_wday + 1;

        int w = rd_wk();                

        if (day == 7) {
                up_wk(w);
        }

        if (day - offset < 0) {
                w--;
        }

        return w;
}


static void up_wk(
        int             w
) {
        FILE *f = fopen("logs/curr", "w");
        if (!f) {
                printf("Could not overwrite file 'logs/curr'.\n");
                return;
        }

        fprintf(f, "%d", w);

        fclose(f);
}
