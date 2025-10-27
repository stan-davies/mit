Money Tracker. I can't remember why there is an 'i' in it.

Note that there is a not included `paths.h` which contains macros with strings
for certain absolute file paths to where log data is stored. This is of course
highly machine specific, so I should probably find some better solution for
that...

---

The week progression does not work because `rcurr` is failing to read anything.
However, it works perfectly fine when called from `rweek`. I have no idea why
this is, especially since it has no input parameters.
