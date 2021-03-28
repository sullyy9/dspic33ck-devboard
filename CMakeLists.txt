set(CMAKE_TOOLCHAIN_FILE toolchain.cmake)
cmake_minimum_required(VERSION 3.17)
project(ryansullivan-quadcopter-motorcontroller C)

set(CMAKE_VERBOSE_MAKEFILE ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Set compiler flags
# -mcpu=33CK256MP508    Set the target device
set(CMAKE_C_FLAGS
        "-mcpu=33CK256MP508 -Wall")

# Set linker flags
set(CMAKE_EXE_LINKER_FLAGS
        "-Wl,--script=p33CK256MP508.gld,--report-mem")

# Set build specific flags
set(CMAKE_C_FLAGS_RELEASE "-O0")
set(CMAKE_C_FLAGS_DEBUG "-O0")

# Set the source files
file(GLOB_RECURSE USER_SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")

# Set output names
set(ELF_NAME "${PROJECT_NAME}.elf")
set(HEX_FILE ${PROJECT_SOURCE_DIR}/build/release/${PROJECT_NAME}.hex)

# Build and link the project
add_executable(${ELF_NAME}
        ${USER_SOURCES}
        )

# Construct a hex file from the elf file
add_custom_command(TARGET ${ELF_NAME} POST_BUILD
        COMMENT "Building ${HEX_FILE}"
        COMMAND ${CMAKE_BIN2HEX} ${PROJECT_SOURCE_DIR}/build/${ELF_NAME} -a
        )