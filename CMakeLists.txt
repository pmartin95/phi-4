cmake_minimum_required(VERSION 3.10)

# Set your project name
project(Phi4Model)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(OBJ_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/obj)

# Include directories
include_directories(include)

# Enable testing
enable_testing()

# Can manually add the sources using the set command as follows:
# set(SOURCES src/main.cpp src/otherfile.cpp)

# Add Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

# Add executable
add_executable(Phi4Model ${SOURCES})

# Add executable for tests
file(GLOB TEST_SOURCES "tests/*.cpp" "src/lattice.cpp")
add_executable(runTests ${TEST_SOURCES})

# Set the location for library installation
install(TARGETS Phi4Model DESTINATION ${OBJ_OUTPUT_PATH})

# If you have any external libraries to include, you can use the following commands
# find_package(ExternalLib REQUIRED)
# target_link_libraries(Phi4Model ExternalLib)

# Link against Google Test and your project's library
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)