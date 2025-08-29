# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelov <abelov@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/27 00:53:11 by abelov            #+#    #+#              #
#    Updated: 2025/08/27 00:53:11 by abelov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cmake_minimum_required(VERSION 3.29)

set(CMAKE_C_STANDARD 17)

cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0075 NEW)
project(day14 VERSION 0.1.0 LANGUAGES C CXX ASM)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_REQUIRED_LIBRARIES "-lbsd")

message(STATUS "System name: ${CMAKE_SYSTEM_NAME}")
message(STATUS "System version: ${CMAKE_SYSTEM_VERSION}")
message(STATUS "Processor: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "CMAKE_SYSTEM_UNAME: ${CMAKE_SYSTEM_UNAME}")
message(STATUS "Kernel (target): ${CMAKE_SYSTEM_VERSION}")
message(STATUS "Kernel (host):   ${CMAKE_HOST_SYSTEM_VERSION}")

#find_path(LINUX_SRC_DIR
#		NAMES "include/linux/list.h"
#		PATHS
#			/usr/src/linux
#			/usr/src/linux-headers-${CMAKE_SYSTEM_VERSION}
#			/lib/modules/${CMAKE_SYSTEM_VERSION}/build
#		NO_DEFAULT_PATH)
#
#if(LINUX_SRC_DIR)
#	include_directories("${LINUX_SRC_DIR}/include")
#endif()

include_directories(include)

set(TARGET_EXE_NAME "${PROJECT_NAME}")

file(GLOB TARGET_HEADERS "src/*.h")
file(GLOB TARGET_SOURCES "src/*.c")

add_executable(${TARGET_EXE_NAME} ${TARGET_HEADERS} ${TARGET_SOURCES})

target_compile_options(${TARGET_EXE_NAME} PRIVATE ${COMMON_CFLAGS})
target_link_options(${TARGET_EXE_NAME} PRIVATE ${COMMON_LDFLAGS})
target_link_libraries(${TARGET_EXE_NAME} PRIVATE ${COMMON_LIBS} bsd)
target_include_directories(${TARGET_EXE_NAME}
		PRIVATE "${PROJECT_SOURCE_DIR}/include")

target_compile_definitions(${TARGET_EXE_NAME} PRIVATE
		INPUT_FILE_NAME="${CMAKE_CURRENT_SOURCE_DIR}/resources/inputReal"
		AREA_WIDTH=101
		AREA_HEIGHT=103
)

set_target_properties(${TARGET_EXE_NAME} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
		OUTPUT_NAME "${PROJECT_NAME}")
