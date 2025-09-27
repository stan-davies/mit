CMD = gcc
SRC = main.c wspen/wspen.c cli/cli.c
OBJ = $(SRC:.c=.o)
INC = -I .
# TAG = -D SYS_WINDOWS

all : ${OBJ}
	clear
	${CMD} $^ ${INC} -Wall -pedantic -Wextra -o out

${OBJ} : %.o: %.c
	clear
	${CMD} ${INC} -Wall -pedantic -Wextra -c $^ -o $@


clean :
	@find . -type f -name '*.o' -delete
	@rm prog
