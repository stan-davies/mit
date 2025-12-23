CMD = gcc
SRC = main.c cli/cli.c mklog/mklog.c sum/sum.c util/util.c
OBJ = $(SRC:.c=.o)
INC = -I .
OUT = mit

all : ${OBJ}
	${CMD} $^ ${INC} -Wall -pedantic -Wextra -o ${OUT}

${OBJ} : %.o: %.c
	${CMD} ${INC} -Wall -pedantic -Wextra -c $^ -o $@


clean :
	@find . -type f -name '*.o' -delete
	@rm ${OUT}
