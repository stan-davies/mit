#include "cli.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "util.h"

#define MD_LOG  1
#define MD_SUM  2

#define PR_WEEK 1
#define PR_MNTH 2

#define TP_FLT  1
#define TP_INT  2

#define CH_ZER  48
#define CH_NIN  57
#define CH_PT   46
#define CH_NUL  0

static struct {
        int             mode    ;

        // for MD_LOG
        float           quant   ;
        int             offset  ;
        // for MD_SUM
        int             period  ;
} params;

static int get_args(
        int             argc    ,
        char          **argv
);


static int get_num(
        int             type    ,
        char           *str     ,
        float          *num
);


void cli_act(
        int             argc    ,
        char          **argv
) {
        if (1 == argc) {
                printf("usage\n");
                return;
        }

        if (0 == strcmp(argv[1], "log")) {
                params.mode = MD_LOG;
                printf("in mode log\n");
        } else if (0 == strcmp(argv[1], "sum")) {
                params.mode = MD_SUM;
                printf("in mode sum\n");
        } else {
                printf("usage\n");
                // 'usage'
                return;
        }

        // defaults
        params.quant = 0.f;
        params.offset = 0;
        params.period = PR_WEEK;


        if (!get_args(argc, argv)) {
                return;
        }

        // route to action
}

static int get_args(
        int             argc    ,
        char          **argv
) {
        char *optstr = calloc(8, sizeof(char));
        switch (params.mode) {
        case MD_LOG:
                sprintf(optstr, ":q:o:");
                break;
        case MD_SUM:
                sprintf(optstr, ":wm");
                break;
        default:
                break;
        }

        int opt;
        opterr = 0;     // don't add error messages
        optind = 2;     // start from after word command
        while (-1 != (opt = getopt(argc, argv, optstr))) {
                switch (opt) {
                case 'q':
                        if (!get_num(TP_FLT, optarg, &params.quant)) {
                                // usage
                                goto exit;
                        }
                        break;
                case 'o':
                        float tmpf;
                        if (!get_num(TP_INT, optarg, &tmpf)) {
                                // usage
                                goto exit;
                        }
                        params.offset = (int)tmpf;
                        break;
                case 'w':
                        params.period = PR_WEEK;
                        break;
                case 'm':
                        params.period = PR_MNTH;
                        break;
                case ':':
                        printf("No argument given for option '%c'.\n", optopt);
                        break;
                case '?':
                default:
                        printf("Invalid option given at '%c'.\n", optopt);
                        break;
                }
        }

exit:
        free(optstr);
        optstr = NULL;
}

static int get_num(
        int             type    ,
        char           *str     ,
        float          *num
) {
        char *c = str;
        int pt = FALSE;

        for (;;) {
                if (CH_NUL == *c) {
                        break;
                } else if (*c >= CH_ZER && *c <= CH_NIN) {
                        goto cont;
                } else if (*c == CH_PT && !pt && TP_FLT == type) {
                        pt = TRUE;
                        goto cont;
                } else {
                        c = NULL;
                        return FALSE;
                }

cont:
                c++;
        }

        c = NULL;
        *num = atof(str);
}
