COMPILER := c++
CFLAGS := -Wall -Wextra -Werror -std=c++17 -O3 -I. -Iftm -g

LIB_NAME := libftmath.a

LIB_SRCS := ${wildcard srcs/*/*.cpp} ${wildcard srcs/*/*/*.cpp}

LIB_OBJECTS := ${LIB_SRCS:.cpp=.o}

all: ${LIB_NAME}

${LIB_NAME}: ${LIB_OBJECTS}
	ar rc ${LIB_NAME} ${LIB_OBJECTS}

%.o: %.cpp
	${COMPILER} ${CFLAGS} -c $^ -o $@

clean:
	rm -f ${LIB_OBJECTS}

fclean: clean
	rm -f ${LIB_NAME}

re: fclean all

.PHONY: all clean fclean re
