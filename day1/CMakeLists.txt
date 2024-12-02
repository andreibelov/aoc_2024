# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelov <abelov@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/01 13:03:35 by abelov            #+#    #+#              #
#    Updated: 2024/12/01 13:03:35 by abelov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cmake_minimum_required(VERSION 3.29)

set(CMAKE_C_STANDARD 17)

cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0075 NEW)
project("day1" VERSION 0.1.0 LANGUAGES C CXX ASM)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_REQUIRED_LIBRARIES "-lbsd")

include_directories(include)

set(TARGET_EXE_NAME "${PROJECT_NAME}")

file(GLOB TARGET_HEADERS "src/*.h")
file(GLOB TARGET_SOURCES "src/*.c")

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package (Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)

add_executable(${TARGET_EXE_NAME} ${TARGET_HEADERS} ${TARGET_SOURCES})

target_include_directories(${TARGET_EXE_NAME} PRIVATE include src)
target_compile_options(${TARGET_EXE_NAME} PRIVATE ${COMMON_CFLAGS})
target_link_options(${TARGET_EXE_NAME} PRIVATE ${COMMON_LDFLAGS})
target_link_libraries(${TARGET_EXE_NAME} Threads::Threads PkgConfig::deps)

target_compile_definitions(${TARGET_EXE_NAME} PRIVATE
        INPUT_FILE_NAME="${CMAKE_CURRENT_SOURCE_DIR}/resources/input.txt"
)

set_target_properties(${TARGET_EXE_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        OUTPUT_NAME "${PROJECT_NAME}")
