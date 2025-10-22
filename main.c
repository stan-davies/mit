#include <stdio.h>
#include <time.h>

#include "cli/cli.h"

int main(
        int             argc    ,
        char          **argv
) {
        cli_act(argc, argv);
        return 1;
}
