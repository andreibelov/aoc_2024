cmake_minimum_required(VERSION 3.29)

set(CMAKE_C_STANDARD 17)

cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0075 NEW)
project(__PROJECT_NAME__ VERSION 0.1.0 LANGUAGES C CXX ASM)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_REQUIRED_LIBRARIES "-lbsd")

include_directories(include)

set(TARGET_EXE_NAME "${PROJECT_NAME}")

file(GLOB TARGET_HEADERS "src/*.h")
file(GLOB TARGET_SOURCES "src/*.c")

add_executable(${TARGET_EXE_NAME} ${TARGET_HEADERS} ${TARGET_SOURCES})

target_compile_options(${TARGET_EXE_NAME} PRIVATE ${COMMON_CFLAGS})
target_link_options(${TARGET_EXE_NAME} PRIVATE ${COMMON_LDFLAGS})
target_link_libraries(${TARGET_EXE_NAME} PRIVATE ${COMMON_LIBS})
target_include_directories(${TARGET_EXE_NAME}
		PRIVATE "${PROJECT_SOURCE_DIR}/include")

target_compile_definitions(${TARGET_EXE_NAME} PRIVATE
		INPUT_FILE_NAME="${CMAKE_CURRENT_SOURCE_DIR}/resources/inputReal"
)

set_target_properties(${TARGET_EXE_NAME} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
		OUTPUT_NAME "${PROJECT_NAME}")
