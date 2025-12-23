#include <locale.h>

#include "cli/cli.h"

int main(
        int             argc    ,
        char          **argv
) {
        setlocale(LC_CTYPE, "");       // Enables printing of fancy characters.

        cli_act(argc, argv);
        return 1;
}
