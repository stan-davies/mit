#include <stdio.h>
#include <locale.h>

#include "cli/cli.h"

int main(
        int             argc    ,
        char          **argv
) {
        setlocale(LC_ALL, "");  // For printing fancy characters properly.

        cli_act(argc, argv);
        return 1;
}
