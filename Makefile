CXX := c++
CCACHE := ${shell command -v ccache 2>/dev/null}
MOLD := ${shell command -v mold 2>/dev/null}

ifeq (${CCACHE},)
	COMPILER := ${CXX}
else
	COMPILER := ccache ${CXX}
endif

LINKER_FLAG :=
ifneq (${MOLD},)
	LINKER_FLAG := -fuse-ld=mold
endif

SHADER_COMPILER := glslangValidator -V -s
FLAGS := -Wall -Wextra -Werror -std=c++17 -O0 -g
LINKFLAGS := ${LINKER_FLAG} -lvulkan -lglfw

MAKEFLAGS += -j${shell nproc}

NAME := scop

SRCS := srcs/main.cpp ${wildcard srcs/*/*.cpp} ${wildcard srcs/*/*/*.cpp} ${wildcard srcs/*/*/*/*.cpp}
HEADER_SRCS := ${wildcard srcs/*/*.hpp} ${wildcard srcs/*/*/*.hpp} ${wildcard srcs/*/*/*/*.hpp} \
			${wildcard srcs/*/*.tpp} ${wildcard srcs/*/*/*.tpp} ${wildcard srcs/*/*/*/*.tpp}

FRAG_SHADERS := ${wildcard shaders/*.frag}
VERT_SHADERS := ${wildcard shaders/*.vert}

BUILD_DIR := build
OBJS := ${addprefix ${BUILD_DIR}/, ${SRCS:.cpp=.o}}
SHADER_OBJS := ${FRAG_SHADERS:.frag=.frag.spv} ${VERT_SHADERS:.vert=.vert.spv}

HEADERS := ${addprefix -I, ${wildcard srcs/*/}}

all: ${NAME}

${NAME}: ${HEADER_SRCS} ${OBJS} ${SHADER_OBJS}
	@echo "Linking ${NAME}"
	@${COMPILER} ${FLAGS} ${HEADERS} ${OBJS} -o $@ ${LINKFLAGS}

${BUILD_DIR}/%.o: %.cpp
	@mkdir -p ${@D}
	@echo "Compiling $<"
	@${COMPILER} ${FLAGS} ${HEADERS} -c $< -o $@

shaders: ${SHADER_OBJS}

docs: docs/doxygen/generateDoxygen.sh docs/plantuml/generatePlantuml.sh
	@echo "Generating documentation"
	@./docs/doxygen/generateDoxygen.sh
	@./docs/plantuml/generatePlantuml.sh

%.frag.spv: %.frag
	@${SHADER_COMPILER} $< -o $@

%.vert.spv: %.vert
	@${SHADER_COMPILER} $< -o $@

clean:
	@rm -f ${OBJS} ${SHADER_OBJS}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re shaders docs