COMPILER := c++
SHADER_COMPILER := glslc
FLAGS := -Wall -Wextra -Werror -std=c++17 -O3
LINKFLAGS := -lvulkan -lglfw -lX11 -lXxf86vm -lXrandr -lXi

NAME := scop

SRCS := srcs/main.cpp ${wildcard srcs/*/*.cpp} ${wildcard srcs/*/*/*.cpp} ${wildcard srcs/*/*/*/*.cpp}
FRAG_SHADERS := $(wildcard shaders/*.frag)
VERT_SHADERS := $(wildcard shaders/*.vert)

OBJS := ${SRCS:.cpp=.o}
SHADER_OBJS := $(FRAG_SHADERS:.frag=.frag.spv) $(VERT_SHADERS:.vert=.vert.spv)

HEADERS := ${addprefix -I, ${wildcard srcs/*/}}

all: ${NAME}

${NAME}: ${OBJS} ${SHADER_OBJS}
	${COMPILER} ${FLAGS} ${HEADERS} ${OBJS} -o $@ ${LINKFLAGS}

%.o: %.cpp
	${COMPILER} ${FLAGS} ${HEADERS} -c $^ -o $@

%.frag.spv: %.frag
	${SHADER_COMPILER} $< -o $@

%.vert.spv: %.vert
	${SHADER_COMPILER} $< -o $@

clean:
	rm -f ${OBJS} ${SHADER_OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re submodules