#include <stdio.h>
#include <time.h>

#include "wspen/wspen.h"
#include "cli/cli.h"

static int day;

//void get_day();

int main(
        int             argc    ,
        char          **argv
) {
        cli_act(argc, argv);
}

//void get_day() {
//          time_t t = time(NULL);
//          struct tm datetime = *localtime(&t);
//          day = datetime.tm_wday + 1;
//}
