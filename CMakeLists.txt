cmake_minimum_required(VERSION 3.5.0)
project(rawiImage VERSION 0.1.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)

# Source files
file(GLOB SOURCES "src/*.c" "src/*.h")

# Add executable
add_executable(rawiPNG ${SOURCES})

# Link libraries (if needed)
# For example, if you are using stb_image and stb_image_write, no additional libraries are required.

# Ensure that stb_image and stb_image_write headers are included

# Add custom commands or tests if needed
enable_testing()
