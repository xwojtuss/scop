COMPILER := c++
SHADER_COMPILER := glslangValidator -V
FLAGS := -Wall -Wextra -Werror -std=c++17 -O3 -g
LINKFLAGS := -Lftm -lvulkan -lglfw -lX11 -lXxf86vm -lXrandr -lXi -lftmath

NAME := scop

LIB_NAME := ftm/libftmath.a

SRCS := srcs/main.cpp ${wildcard srcs/*/*.cpp} ${wildcard srcs/*/*/*.cpp} ${wildcard srcs/*/*/*/*.cpp}
HEADER_SRCS := ${wildcard srcs/*/*.hpp} ${wildcard srcs/*/*/*.hpp} ${wildcard srcs/*/*/*/*.hpp} \
			${wildcard srcs/*/*.tpp} ${wildcard srcs/*/*/*.tpp} ${wildcard srcs/*/*/*/*.tpp}

FRAG_SHADERS := $(wildcard shaders/*.frag)
VERT_SHADERS := $(wildcard shaders/*.vert)

OBJS := ${SRCS:.cpp=.o}
SHADER_OBJS := $(FRAG_SHADERS:.frag=.frag.spv) $(VERT_SHADERS:.vert=.vert.spv)

HEADERS := ${addprefix -I, ${wildcard srcs/*/}} -Iftm

all: ${NAME}

${NAME}: ${LIB_NAME} ${HEADER_SRCS} ${OBJS} ${SHADER_OBJS}
	${COMPILER} ${FLAGS} ${HEADERS} ${OBJS} -o $@ ${LINKFLAGS}

%.o: %.cpp
	${COMPILER} ${FLAGS} ${HEADERS} -c $^ -o $@

${LIB_NAME}:
	${MAKE} -C ftm

shaders: ${SHADER_OBJS}

%.frag.spv: %.frag
	${SHADER_COMPILER} $< -o $@

%.vert.spv: %.vert
	${SHADER_COMPILER} $< -o $@

clean:
	rm -f ${OBJS} ${SHADER_OBJS}
	${MAKE} -C ftm clean

fclean: clean
	rm -f ${NAME}
	${MAKE} -C ftm fclean

re: fclean all

.PHONY: all clean fclean re submodules