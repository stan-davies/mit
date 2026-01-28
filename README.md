Money Tracker. I can't remember why there is an 'i' in it.

Note that there is a not included `util/paths.h` which contains macros with
strings for certain absolute file paths to where log data is stored. This is of
course highly machine specific, so I should probably find some better solution
for that...

There was a strange error talking about heap corruption that I got when doing a
summary of a large number of weeks (18, for example) but it seems to have gone
away in that, whilst trying to test which numbers of weeks it would happen for,
it just stopped happening at all. Fine by me!
