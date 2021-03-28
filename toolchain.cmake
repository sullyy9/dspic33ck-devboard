set(CMAKE_SYSTEM_NAME       "Generic")
set(CMAKE_SYSTEM_PROCESSOR  "arm")

# Setup search paths
set(CMAKE_FIND_ROOT_PATH "C:/Program\ Files/Microchip/xc16/v1.61")
set(CMAKE_SYSTEM_INCLUDE_PATH /include)
set(CMAKE_SYSTEM_LIBRARY_PATH /lib)
set(CMAKE_SYSTEM_PROGRAM_PATH /bin)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Find the toolchain tools
find_program(CMAKE_AR               "xc16-ar")
find_program(CMAKE_ASM_COMPILER     "xc16-as")
find_program(CMAKE_C_COMPILER       "xc16-gcc")
find_program(CMAKE_LINKER           "xc16-ld")
find_program(CMAKE_BIN2HEX          "xc16-bin2hex")
find_program(CMAKE_OBJCOPY          "xc16-objcopy")
find_program(CMAKE_RANLIB           "xc16-ranlib")
find_program(CMAKE_STRIP            "xc16-strip")

# Set any include paths we need
set(STANDARD_LIBRARIES_DIRECTORY "${CMAKE_FIND_ROOT_PATH}/include")
set(GENERIC_LIBRARIES_DIRECTORY "${CMAKE_FIND_ROOT_PATH}/support/generic/h")
set(DEVICE_LIBRARIES_DIRECTORY "${CMAKE_FIND_ROOT_PATH}/support/dsPIC33C/h")
set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES
        ${STANDARD_LIBRARIES_DIRECTORY}
        ${GENERIC_LIBRARIES_DIRECTORY}
        ${DEVICE_LIBRARIES_DIRECTORY}
        )

# Disable compiler tests
set(CMAKE_C_COMPILER_ID_RUN 1)
set(CMAKE_C_COMPILER_FORCED TRUE)

# Manually set the compiler information
set(CMAKE_C_COMPILER_ID GNU)
set(MICROCHIP_C_COMPILER_ID XC16)
set(CMAKE_COMPILER_IS_GNUCC 1)
set(CMAKE_C_STANDARD 90)
