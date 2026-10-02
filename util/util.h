#ifndef UTIL_H
#define UTIL_H

#define TRUE            1
#define FALSE           0

#include "paths.h"

int rcurr(
        void
);

float rweek(
        int             offset
);

char *rweekr(           // Reads weeks raw, i.e. text in file. Caller must free.
        int             offset
);

float rspec(
        void
);

char *rspecr(           // Reads special raw, i.e. text in file. Caller must free.
        void
);

#endif
