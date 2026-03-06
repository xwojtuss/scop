cmake_minimum_required(VERSION 3.16)

project(scop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
  message(STATUS "Using ccache: ${CCACHE_PROGRAM}")
else()
  message(STATUS "ccache not found, compiling without compiler cache")
endif()

find_program(MOLD_PROGRAM mold)
if(MOLD_PROGRAM)
  add_link_options(-fuse-ld=mold)
  message(STATUS "Using mold linker: ${MOLD_PROGRAM}")
else()
  message(STATUS "mold not found, using default linker")
endif()

file(GLOB_RECURSE SCOP_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/srcs/*.cpp"
)

add_executable(scop ${SCOP_SOURCES})

target_compile_definitions(scop PRIVATE GLM_FORCE_CTOR_INIT)

target_compile_options(scop PRIVATE -Wall -Wextra -Werror -O0 -g)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(scop PRIVATE -Wno-error=maybe-uninitialized)
endif()

file(GLOB SRC_INCLUDE_DIR_CANDIDATES LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/srcs/*")
set(SRC_INCLUDE_DIRS)
foreach(CANDIDATE IN LISTS SRC_INCLUDE_DIR_CANDIDATES)
  if(IS_DIRECTORY "${CANDIDATE}")
    list(APPEND SRC_INCLUDE_DIRS "${CANDIDATE}")
  endif()
endforeach()

target_include_directories(scop PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/srcs"
  ${SRC_INCLUDE_DIRS}
)

include(FetchContent)

find_package(Vulkan REQUIRED)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG   7b6aead9fb88b3623e3b3725ebb42670cbe4c579
)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG   0af55ccecd98d4e5a8d1fad7de25ba429d60e863
)

FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(glm)

target_link_libraries(scop PRIVATE
  Vulkan::Vulkan
  glfw
  glm::glm
)

find_program(GLSLANG_VALIDATOR glslangValidator)
if(NOT GLSLANG_VALIDATOR)
  message(FATAL_ERROR "glslangValidator not found. Install it to compile shaders.")
endif()

file(GLOB FRAG_SHADERS "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.frag")
file(GLOB VERT_SHADERS "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.vert")
set(SHADER_SOURCES ${FRAG_SHADERS} ${VERT_SHADERS})
set(SHADER_OUTPUTS)

foreach(SHADER_FILE IN LISTS SHADER_SOURCES)
  set(SPV_FILE "${SHADER_FILE}.spv")
  add_custom_command(
    OUTPUT "${SPV_FILE}"
    COMMAND "${GLSLANG_VALIDATOR}" -V -s "${SHADER_FILE}" -o "${SPV_FILE}"
    DEPENDS "${SHADER_FILE}"
    COMMENT "Compiling shader ${SHADER_FILE}"
    VERBATIM
  )
  list(APPEND SHADER_OUTPUTS "${SPV_FILE}")
endforeach()

add_custom_target(shaders ALL DEPENDS ${SHADER_OUTPUTS})
add_dependencies(scop shaders)

add_custom_target(generate_docs
  COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/docs/doxygen/generateDoxygen.sh"
  COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/docs/plantuml/generatePlantuml.sh"
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
  COMMENT "Generating documentation"
)
