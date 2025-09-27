#include "cli.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MD_LOG  1
#define MD_SUM  2

static void get_args(
        int             mode    ,
        int             argc    ,
        char          **argv
);


void cli_act(
        int             argc    ,
        char          **argv
) {
        if (1 == argc) {
                printf("usage\n");
                return;
        }

        int mode;
        if (0 == strcmp(argv[1], "log")) {
                mode = MD_LOG;
                printf("in mode log\n");
        } else if (0 == strcmp(argv[1], "sum")) {
                mode = MD_SUM;
                printf("in mode sum\n");
        } else {
                printf("usage\n");
                // 'usage'
                return;
        }
}

static void get_args(
        int             mode    ,
        int             argc    ,
        char          **argv
) {
        char *optstr = calloc(8, sizeof(char));
        switch (mode) {
        case MD_LOG:
                sprintf(optstr, ":q:o:");
                break;
        case MD_SUM:
                sprintf(optstr, ":wm");
                break;
        }
                        
        int opt;
        while(-1 != (opt = getopt(argc, argv, optstr))) {
                switch (opt) {
                case 'q':
                        // quantity in 'optarg'
                case 'o':
                        // offset
                case 'w':
                        // week
                case 'm':
                        // month
                case ':':
                        // no arg given for 'optopt'
                case '?':
                default:
                        // invalid option at 'optopt'
                }
        }

        free(optstr);
        optstr = NULL;
}
