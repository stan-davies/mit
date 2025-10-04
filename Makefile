CMD = gcc
SRC = main.c cli/cli.c mklog/mklog.c sum/sum.c util/util.c
OBJ = $(SRC:.c=.o)
INC = -I .

all : ${OBJ}
# 	clear
	${CMD} $^ ${INC} -Wall -pedantic -Wextra -o out

${OBJ} : %.o: %.c
#	clear
	${CMD} ${INC} -Wall -pedantic -Wextra -c $^ -o $@


clean :
	@find . -type f -name '*.o' -delete
	@rm out
