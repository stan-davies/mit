Money Tracker. I can't remember why there is an 'i' in it.

Note that there is a not included `util/paths.h` which contains macros with
strings for certain absolute file paths to where log data is stored. This is of
course highly machine specific, so I should probably find some better solution
for that...

There was a strange error talking about heap corruption that I got when doing a
summary of a large number of weeks (18, for example) but it seems to have gone
away in that, whilst trying to test which numbers of weeks it would happen for,
it just stopped happening at all. Fine by me!

I got it again, when doing `mit sum -a`. It is the same heap corruption that
has plagued several of my recent projects. Very confusing indeed.

Got to be some kind of going beyond boundaries.

It's back to not doing the error.

Might have solved by realising that I was putting a very long path into an 8
character long buffer (and somehow it was usually working!?). Continue testing.
