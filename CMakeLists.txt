# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelov <abelov@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/01 12:58:44 by abelov            #+#    #+#              #
#    Updated: 2025/08/27 00:20:16 by abelov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cmake_minimum_required(VERSION 3.29)

include_directories(include)

set(CMAKE_C_COMPILER gcc-13)

project(aoc_2024 LANGUAGES C)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)

set(THREADS_PREFER_PTHREAD_FLAG ON)

set(COMMON_LIBS
		m
		Threads::Threads
		PkgConfig::deps
)

set(COMMON_LDFLAGS
		-g3 -gdwarf-3
        -fsanitize=address,undefined,bounds-strict
		-fsanitize=float-divide-by-zero,float-cast-overflow
		-fno-sanitize-recover
)
set(COMMON_CFLAGS
        -Wall -Wextra
        -Wwrite-strings -Wimplicit
        -Wno-error=unused-parameter
        -Wno-error=unused-variable
        -O0
        -masm=att
        -fno-exceptions
        -fno-omit-frame-pointer
        -fdwarf2-cfi-asm
        -fcf-protection=none
        -mmanual-endbr
        -g3 -gdwarf-3
        -fasynchronous-unwind-tables
		-fsanitize=address,undefined,bounds-strict
		-fsanitize=float-divide-by-zero,float-cast-overflow
		-fno-sanitize-recover
)

add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)
add_subdirectory(day4)
add_subdirectory(day5)
add_subdirectory(day6)
add_subdirectory(day7)
add_subdirectory(day8)
add_subdirectory(day9)
add_subdirectory(day10)
add_subdirectory(day11)
add_subdirectory(day12)
add_subdirectory(day13)
add_subdirectory(day14)
