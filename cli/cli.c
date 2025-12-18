#define PR_SPEC -1
#include "cli.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "util/util.h"
#include "mklog/mklog.h"
#include "sum/sum.h"

#define MD_LOG  1
#define MD_SUM  2

#define TP_FLT  1
#define TP_INT  2

static struct {
        int             mode    ;

        float           quant   ;
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

static void print_ln(
        void
);


void cli_act(
        int             argc    ,
        char          **argv
) {
        if (1 == argc) {
                printf("Choose mode 'log' or 'sum'.\n");
                return;
        }

        if (0 == strcmp(argv[1], "log")) {
                params.mode = MD_LOG;
        } else if (0 == strcmp(argv[1], "sum")) {
                params.mode = MD_SUM;
        } else if (0 == strcmp(argv[1], "pwk")) {
                up_wk();                
                printf("Progressed week.\n");
                return;
        } else {
                printf("Choose mode 'log' or 'sum', or 'pwk'.\n");
                return;
        }

        // defaults
        params.quant = 0.f;
        params.period = 1;

        if (!get_args(argc, argv)) {
                return;
        }

        system("clear");
        print_ln();

        switch (params.mode) {
        case MD_LOG:
                if (PR_SPEC == params.period) {
                        adj_sv(-params.quant);
                        printf("  Spent savings\t\t£%.2f\n\n",
                                params.quant);
                        sum_sv();
                } else {
                        mk_log(params.quant);
                        printf("  Logged spending of\t£%.2f\n\n",
                                params.quant);
                        sum(1);
                }
                break;
        case MD_SUM:
                sum(params.period);
                break;
        }

        printf("\n");
        print_ln();
}

static int get_args(
        int             argc    ,
        char          **argv
) {
        char *optstr = calloc(8, sizeof(char));
        int ret = TRUE;
        int opt;
        float fv;

        switch (params.mode) {
        case MD_LOG:
                sprintf(optstr, ":q:s");
                break;
        case MD_SUM:
                sprintf(optstr, ":p:s");
                break;
        default:
                break;
        }

        opterr = 0;     // Don't add error messages.
        optind = 2;     // Start from after word command.
        while (-1 != (opt = getopt(argc, argv, optstr))) {
                switch (opt) {
                case 'q':
                        if (!get_num(TP_FLT, optarg, &params.quant)) {
                                printf("Found non-number value for 'q'.\n");
                                ret = FALSE;
                        }
                        break;
                case 's':
                        params.period = PR_SPEC;
                        break;
                case 'p':
                        if (!get_num(TP_INT, optarg, &fv)) {
                                printf("Found non-number value for 'p'.\n");
                                ret = FALSE;
                                break;
                        }
                        params.period = (int)fv;
                        break;
                case ':':
                        printf("No argument given for option '%c'.\n", optopt);
                        ret = FALSE;
                        break;
                case '?':
                default:
                        printf("Invalid option given at '%c'.\n", optopt);
                        ret = FALSE;
                        break;
                }
        }

        free(optstr);
        optstr = NULL;

        return ret;
}

static int get_num(
        int             type    ,
        char           *str     ,
        float          *num
) {
        char *c = str;
        int pt = FALSE;

        if ('-' == *c) {
                c++;
        }

        for (;;) {
                if (CHR_NULL == *c) {
                        break;
                } else if (*c >= '0' && *c <= '9') {
                        goto cont;
                } else if (*c == '.' && !pt && TP_FLT == type) {
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

        return TRUE;
}

int rq_up_wk(
        void
) {
        char rep;

        printf("  Today is Sunday, proceed to new week? y/n\n");
        scanf("%c", &rep);

        return 'y' == rep;
}

static void print_ln(
        void
) {
        printf("\033[90m"
               "––––––––––––––––––––––––––––––––––––––––––––––––––"
               "\033[0m\n\n");

}
